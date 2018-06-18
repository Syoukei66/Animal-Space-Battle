#include "Star.h"
#include "Player.h"
#include "ScoreConstatns.h"

static const T_UINT16 HIT_EFFECT_COUNT = 11;

Star::Star()
  : master_(nullptr)
  , mastered_time_(0)
  , need_mastered_time_(0)
{
  this->body_ = new Model(Asset::Fbx::STAR);
  this->body_->SetMaterialForTree(*Asset::Material::STAR.Clone());
  this->body_->GetMaterial()->ColorProperty("_PlayerColor") = Color4F::WHITE;
  this->AddChild(this->body_);

  this->wall_ = new GameObject3D();
  this->wall_->SetVisible(false);
  this->AddChild(this->wall_);

  this->wall_model_ = new Model(Asset::Fbx::STAR);
  this->wall_model_->SetMaterialForTree(*Asset::Material::STAR_WALL.Clone());
  this->wall_model_->GetMaterial()->SetZTestLevel(1);
  this->wall_model_->GetMaterial()->ColorProperty("_PlayerColor") = Color4F::WHITE;
  this->wall_model_->GetTransform()->RotateX(-MathConstants::PI_1_2);
  this->wall_->AddChild(this->wall_model_);

  this->wall_model_->GetMaterial()->IntProperty("_HitEffectCount") = 0;
}

Star::~Star()
{
  delete this->wall_model_;
  delete this->wall_;
  delete this->body_;
}

void Star::OnAllocated()
{
  this->SetVisible(true);
}

void Star::OnFree()
{
}

void Star::Update()
{
  if (this->hit_effect_count_ > 0)
  {
    this->hit_effect_count_--;
    this->wall_model_->GetMaterial()->IntProperty("_HitEffectCount") = this->hit_effect_count_;
  }
  this->mastered_time_++;
  this->wall_model_->GetTransform()->SetScale(1.0f + 4.0f / this->GetTransform()->GetScaleMax());
  this->wall_model_->GetMaterial()->FloatProperty("_Time") = HalEngine::Time::ElapsedFrameSinceSceneCreate();
  this->wall_model_->GetMaterial()->FloatProperty("_MasteredTime") = this->mastered_time_;
  this->body_->GetMaterial()->FloatProperty("_Time") = HalEngine::Time::ElapsedFrameSinceSceneCreate();
}

void Star::SetMaster(Player* player, const TVec3f& vec)
{
  if (this->master_ == player)
  {
    return;
  }
  Asset::Sound::FLAG.Play();
  if (this->master_)
  {
    this->master_->SubScore(ScoreConstants::POINT_GET_STAR_BASE);
  }
  player->AddScore(ScoreConstants::POINT_GET_STAR_BASE);
  this->master_ = player;
  if (!this->master_)
  {
    this->wall_->SetVisible(false);
    this->body_->GetMaterial()->ColorProperty("_PlayerColor") = Color4F::WHITE;
    return;
  }
  this->mastered_time_ = 0;
  this->need_mastered_time_ = (T_UINT16)this->GetTransform()->GetScaleMax() * 60;
  
  this->wall_->GetTransform()->SetEularAngles(0.0f, 0.0f, 0.0f);
  const TVec3f direction = this->wall_->GetTransform()->GetDirection().Normalized();
  const TVec3f cross = TVec3f::OuterProduct(direction, vec);
  const T_FLOAT dot = TVec3f::InnerProduct(vec, direction);
  this->wall_->GetTransform()->Rotate(cross, acosf(dot));

  this->MakeHitEffect(player);

  this->wall_model_->GetMaterial()->FloatProperty("_NeedMasteredTime") = this->need_mastered_time_;
  this->wall_->SetVisible(true);
 
  const Color4F& color = PlayerEntry::PLAYER_ENTRY_COLORS[player->GetID()];
  this->wall_model_->GetMaterial()->ColorProperty("_PlayerColor") = color;
  this->body_->GetMaterial()->ColorProperty("_PlayerColor") = color;
}

void Star::AddDamage(Player* player, T_UINT16 damage)
{
  this->MakeHitEffect(player);
}

void Star::MakeHitEffect(Player* player)
{
  if (!this->master_ || this->hit_effect_count_ > 0)
  {
    return;
  }
  Asset::Sound::BARRIER.Play();
  player->AddScore(ScoreConstants::POINT_ATTACK_TO_STAR);
  this->hit_effect_count_ = HIT_EFFECT_COUNT;
}
