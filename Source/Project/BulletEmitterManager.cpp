#include "stdafx.h"
#include "BulletEmitterManager.h"
#include "BulletEmitterTable.h"

BulletEmitterManager::BulletEmitterManager(Player* player)
  : emitter_normal_(nullptr)
  , emitter_power_(nullptr)
{
  this->pooled_emitter_count_ = BulletEmitterTable::GetInstance().GetDataCount();
  this->emitter_pool_ = new BaseBulletEmitter*[this->pooled_emitter_count_];
  for (T_UINT8 i = 0; i < this->pooled_emitter_count_; ++i)
  {
    this->emitter_pool_[i] = BulletEmitterTable::GetInstance().GetData(i)->CreateBulletEmitter();
    this->emitter_pool_[i]->Init(player);
  }
}

BulletEmitterManager::~BulletEmitterManager()
{
  for (T_UINT8 i = 0; i < this->pooled_emitter_count_; ++i)
  {
    delete this->emitter_pool_[i];
  }
  delete[] this->emitter_pool_;
}

void BulletEmitterManager::Update()
{
  for (T_UINT8 i = 0; i < this->pooled_emitter_count_; ++i)
  {
    this->emitter_pool_[i]->Update();
  }
}

void BulletEmitterManager::ChangeVehicle(const VehicleData* data)
{
  this->emitter_normal_ = this->emitter_pool_[data->GetBulletEmitterData_Normal()->GetId()];
  this->emitter_power_ = this->emitter_pool_[data->GetBulletEmitterData_Power()->GetId()];
}

void BulletEmitterManager::Emission(const PlayerInput& input)
{
  if (input.IsCommand(PlayerInput::PLAYER_COMMAND_BRAKE))
  {
    this->emitter_power_->Emission();
    return;
  }
  this->emitter_normal_->Emission();
}

T_UINT32 BulletEmitterManager::CollisionToPlayer(Player* player)
{
  T_UINT32 hited_count = 0;
  for (T_UINT8 i = 0; i < this->pooled_emitter_count_; ++i)
  {
    hited_count += this->emitter_pool_[i]->CollisionToPlayer(player);
  }
  return hited_count;
}

T_UINT32 BulletEmitterManager::CollisionToStar(Star* star)
{
  T_UINT32 hited_count = 0;
  for (T_UINT8 i = 0; i < this->pooled_emitter_count_; ++i)
  {
    hited_count += this->emitter_pool_[i]->CollisionToStar(star);
  }
  return hited_count;
}
