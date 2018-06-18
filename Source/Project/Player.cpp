#include "Player.h"
#include <algorithm>

#include "GameEntity.h"

#include "BulletManager.h"
#include "GameLevelParam.h"

#include "PlayerActor.h"
#include "PlayerInput.h"
#include "PlayerEntry.h"
#include "PlayerStateManager.h"
#include "PlayerManager.h"
#include "Star.h"

#include "VehicleTable.h"
#include "GameLayer.h"

#include "ScoreConstatns.h"
#include "GameDirector.h"
#include "PlayerResult.h"

static const T_UINT16 HP_MAX = 150;

Player::Player(const PlayerEntry& entry)
  : id_(entry.id)
  , is_human_(entry.entry_kind == PlayerEntry::PLAYER_ENTRY_PLAYER)
  , status_(new PlayerStatus(entry))
  , state_(new PlayerStateManager())
  , bullet_emitter_(new BulletEmitterManager(this))
  , landed_star_(nullptr)
  , velocity_(0.0f, 0.0f, 0.0f)
  , damaged_velocity_(0.0f, 0.0f, 0.0f)
  , hp_(HP_MAX)
  , max_hp_(HP_MAX)
  , is_dead_(false)
{
  this->actor_ = new PlayerActor();
  this->actor_->ChangeAnimalData(entry.animal_data);
  this->actor_->ChangePlayerId(entry.id);
  this->AddChild(this->actor_);

  this->GetInVehicle(entry.vehicle_data);

  this->ChangeState(STATE_FLYING);
  this->result_ = GameDirector::GetPlayerResultList()->GetResultById(this->id_);
}

Player::~Player()
{
  delete this->bullet_emitter_;
  delete this->state_;
  delete this->status_;
  delete this->actor_;
}

void Player::GameLevelReflection()
{
  if (GameLevelParam::GetInstance().IsStatusLevelsDirty())
  {
    this->status_->OnStatusChanged();
  }
}

void Player::ResolveInput(const PlayerInput& input, const PlayerManager& manager)
{
  if (!this->damaged_velocity_.IsZero())
  {
    this->damaged_velocity_ *= 0.95f;
    this->velocity_ = this->damaged_velocity_;
    T_FLOAT v = this->damaged_velocity_.Length();
    this->GetTransform()->RotateX(0.1f);
    if (v < 0.01f)
    {
      this->damaged_velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
    }
    return;
  }
  this->state_->ResolveInput(this, input);
}

void Player::BulletUpdateProcess()
{
  this->bullet_emitter_->Update();
}

void Player::TransformUpdate()
{
  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + this->velocity_);
}

void Player::ResetVelocity()
{
  this->damaged_velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
  this->velocity_ = TVec3f(0.0f, 0.0f, 0.0f);
}

void Player::SetVelocity(const TVec3f& velocity)
{
  this->velocity_ = velocity;
}

void Player::AddVelocity(const TVec3f& velocity)
{
  this->velocity_ += velocity;
  T_FLOAT length = this->velocity_.Length();
  if (length != 0.0f)
  {
    this->velocity_ = this->velocity_ * std::min(this->GetStatus().GetMaxSpeed(), length) / length;
  }
}

void Player::AddDamagedVelocity(const TVec3f& velocity)
{
  this->damaged_velocity_ += velocity;
}

bool Player::AddDamage(T_UINT16 damage)
{
  Asset::Sound::DAMAGE.Play();
  this->hp_ = std::max(0, (T_INT32)this->hp_ - (T_INT32)damage);
  if (!this->is_dead_ && this->hp_ == 0)
  {
    this->Death();
    return true;
  }
  return false;
}

void Player::AddScore(T_UINT32 score)
{
  this->result_->point += score;
}

void Player::SubScore(T_UINT32 score)
{
  this->result_->point = std::max(0, (T_INT32)(this->result_->point - score));
}

T_UINT32 Player::DivideScore()
{
  T_UINT32 d = this->result_->point / 2;
  this->result_->point -= d;
  return d;
}

bool Player::CollisionToOther(Player* other)
{
  if (!this->HitCheck(other))
  {
    return false;
  }
  const T_FLOAT self_scale = this->GetColliderRadius();
  const T_FLOAT other_scale = other->GetColliderRadius();
  if (self_scale != other_scale)
  {
    Player* winner = self_scale > other_scale ? this : other;
    Player* loser = self_scale < other_scale ? this : other;
    TVec3f distance = loser->GetTransform()->GetWorldPosition() - winner->GetTransform()->GetWorldPosition();
    T_FLOAT m = winner->GetColliderRadius() - loser->GetColliderRadius();
    loser->AddDamagedVelocity(distance.Normalized() * m);
    loser->AddDamage(m * 10.0f);
  }
  else
  {
    T_FLOAT R = self_scale + other_scale;
    TVec3f distance = this->GetTransform()->GetWorldPosition() - other->GetTransform()->GetWorldPosition();
    TVec3f vec = distance.Normalized();
    this->GetTransform()->SetPosition(other->GetTransform()->GetPosition() + vec * R);
    other->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + vec * -R);
    this->velocity_ += this->velocity_ * -std::max(0.0f, std::min(1.0f, TVec3f::InnerProduct(-this->velocity_.Normalized(), vec))) * 0.5f;
    other->velocity_ += other->velocity_ * -std::max(0.0f, std::min(1.0f, TVec3f::InnerProduct(-other->velocity_.Normalized(), -vec))) * 0.5f;
  }
  return true;
}

bool Player::CollisionToStar(Star* star)
{
  const T_UINT32 hited_count = this->bullet_emitter_->CollisionToStar(star);

  const TVec3f player_pos = this->GetTransform()->GetPosition();
  const T_FLOAT player_radius = this->GetColliderRadius();
  const TVec3f star_pos = star->GetTransform()->GetPosition();
  const T_FLOAT star_radius = star->GetTransform()->GetScaleMax() * star->GetColliderRadius();
  const TVec3f distance = player_pos - star_pos;
  const T_FLOAT R = player_radius + star_radius;
  //const T_FLOAT GR = R + star->GetTransform()->GetScaleMax() * 2.0f;
  //if (distance.LengthSquare() < GR * GR)
  //{
    bool hited = star->HitCheck(this);
    if (hited)
    {
      TVec3f vec = distance.Normalized();
      this->GetTransform()->SetPosition(star_pos + vec * R);
      this->Landing(star, vec);

      this->velocity_ += this->velocity_ * -std::max(0.0f, std::min(1.0f, TVec3f::InnerProduct(-this->velocity_.Normalized(), vec))) * 0.5f;

      return true;
    }
    this->TakeOff();

    //T_FLOAT R2 = GR * GR;
    //T_FLOAT r1 = star->GetTransform()->GetScaleMax();
    //T_FLOAT r2 = this->GetTransform()->GetScaleMax();
    //T_FLOAT m1 = 4.0f / 3.0f * MathConstants::PI * r1 * r1 * r1;
    //T_FLOAT m2 = 4.0f / 3.0f * MathConstants::PI * r2 * r2 * r2;
    //T_FLOAT G = GameLevelParam::GetInstance().GetStarLevel(StarManager::GRAVITY);

    //TVec3f g = distance.Normalized() * G * m1 * m2 / R2;
    //this->AddVelocity(-g);
    //return true;
  //}

  return false;
}

void Player::Landing(Star* star, const TVec3f& vec)
{
  this->landed_star_ = star;
  star->SetMaster(this, vec);
  //this->camera_->Landing(star);
}

void Player::TakeOff()
{
  this->landed_star_ = nullptr;
  //this->camera_->Takeoff();
}

void Player::GetInVehicle(const VehicleData* data)
{
  this->actor_->ChangeVehicleData(data);
  this->GetCollider()->SetRadius(this->actor_->GetColliderRadius() * 2.0f);
  this->status_->ChangeVehicle(data);
  this->bullet_emitter_->ChangeVehicle(data);
  this->HpMax();
}

void Player::Death()
{
  if (this->is_dead_)
  {
    return;
  }
  this->status_->ChangeVehicle(nullptr);
  this->actor_->ChangeVehicleData(nullptr);
  this->GetCollider()->SetRadius(2.0f);
  this->AddDamagedVelocity(TVec3f(Util::GetRandom(-1.0f, 1.0f), Util::GetRandom(-1.0f, 1.0f), Util::GetRandom(-1.0f, 1.0f)));
  this->is_dead_ = true;
  PlayerManager::GetInstance().GetPlayerView(this->id_)->OnDead();
}

void Player::HpMax()
{
  this->hp_ = HP_MAX;
  this->is_dead_ = false;
}

void Player::ChangeState(T_UINT8 state_id)
{
  this->state_->ChangeState(this, state_id);
}
