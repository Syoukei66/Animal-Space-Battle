#include "Bullet.h"
#include "Player.h"
#include "GameDirector.h"

Bullet::Bullet()
{
  this->model_ = new Model(Asset::Fbx::STAR);
  this->model_->SetMaterialForTree(EngineAsset::Material::WHITE);
  this->AddChild(this->model_);
  this->SetVisible(false);
}

Bullet::~Bullet()
{
  delete this->model_;
}

void Bullet::OnAllocated()
{
  this->BulletInit();
  this->SetVisible(true);
  GameDirector::GetScene()->AddChild(this);
}

void Bullet::OnFree()
{
  Scene* scene = GameDirector::GetScene();
  if (scene)
  {
    scene->RemoveChild(this);
  }
  this->SetVisible(false);
  this->BulletUninit();
}

void Bullet::BulletInit()
{
  this->user_ = nullptr;
  this->target_ = nullptr;

  this->effect_id_ = 0;
  this->lifetime_ = 0;
  this->power_ = 0;
  this->delay_ = 0;

  this->homing_lifetime_ = 0;
  this->homing_rate_ = 0.0f;

  this->radius_ = 0.0f;
  this->length_ = 0.0f;
  this->padding_ = 0.0f;

  this->max_speed_ = 0.0f;
  this->speed_ = 0.0f;
  this->accel_ = 0.0f;
  this->vec_ = TVec3f();

}

void Bullet::BulletUninit()
{
}

void Bullet::BulletUpdate()
{
  if (this->lifetime_ == 0)
  {
    return;
  }
  if (this->delay_ > 0)
  {
    --this->delay_;
    return;
  }
  this->speed_ += this->accel_;

  if (this->target_ && this->homing_lifetime_ > 0)
  {
    if (this->homing_rate_ != 0.0f)
    {
      const TVec3f distance = this->target_->GetTransform()->GetWorldPosition() - this->GetTransform()->GetWorldPosition();
      this->vec_ = this->vec_ * (1.0f - this->homing_rate_) + distance.Normalized() * this->homing_rate_;
    }
    --this->homing_lifetime_;
  }

  this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + this->vec_ * this->speed_);

  if (this->lifetime_ > 0)
  {
    --this->lifetime_;
  }
}

void Bullet::DeadBullet()
{
  this->lifetime_ = 0;
}