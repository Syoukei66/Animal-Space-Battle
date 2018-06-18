#include "stdafx.h"
#include "PlayerState_Gacha.h"
#include "PlayerManager.h"
#include "GameDirector.h"
#include "VehicleTable.h"
#include "GameLayer.h"

PlayerState_Gacha::PlayerState_Gacha()
{
  this->effect_ = new GachaEffect();
  this->effect_->SetVisible(false);
  GameDirector::GetScene()->AddChild(this->effect_);
}

PlayerState_Gacha::~PlayerState_Gacha()
{
  delete this->effect_;
}

void PlayerState_Gacha::OnStart(Player* self)
{
  self->ResetVelocity();
  self->GetInVehicle(VehicleTable::GetInstance().GetData(0));
  T_UINT8 layer_id = self->GetID() + GameLayer::LAYER_PLAYER_0;
  this->effect_->SetLayerIdForAll(layer_id);
  this->effect_->SetVisible(true);
  this->effect_->EffectBegin();
  this->count_ = 300;
  PlayerManager::GetInstance().GetPlayerView(self->GetID())->GachaViewMode();
}

void PlayerState_Gacha::OnFinish(Player* self)
{
  self->GetInVehicle(VehicleTable::GetInstance().GetData(Util::GetRandom(0, VehicleTable::GetInstance().GetDataCount())));
  this->effect_->SetVisible(false);
  PlayerManager::GetInstance().GetPlayerView(self->GetID())->GameViewMode();
}

void PlayerState_Gacha::ResolveInputProcess(Player* self, const PlayerInput& input)
{
  if (this->count_ == 0)
  {
    this->ReturnState(self);
    return;
  }
  const Camera3D* camera = PlayerManager::GetInstance().GetPlayerView(self->GetID())->GetCamera();
  const TVec3f camera_position = camera->GetTransform()->GetWorldPosition();
  this->effect_->GetTransform()->SetPosition(camera_position);
  this->effect_->GetTransform()->LerpRotation(self->GetTransform()->GetQuaternion(), 1.0f);
  --this->count_;
}