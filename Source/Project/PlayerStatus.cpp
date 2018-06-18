#include "PlayerStatus.h"
#include "VehicleTable.h"
#include "GameLevelParam.h"

PlayerStatus::PlayerStatus(const PlayerEntry& entry)
  : animal_data_(entry.animal_data)
  , vehicle_data_(nullptr)
  , handicap_(entry.handicap)
{
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::ChangeVehicle(const VehicleData* vehicle)
{
  this->vehicle_data_ = vehicle;
  this->OnStatusChanged();
}

void PlayerStatus::OnStatusChanged()
{
  const GameLevelParam& param = GameLevelParam::GetInstance();
  T_FLOAT rate = (T_FLOAT)(100 - this->handicap_) / 100;
  if (this->vehicle_data_)
  {
    this->accel_ = this->vehicle_data_->GetAccel() * param.GetPlayerStatusLevel(ACCEL_WEIGHT) * rate;
    this->brake_ = this->vehicle_data_->GetBrake() * param.GetPlayerStatusLevel(ACCEL_WEIGHT) * rate;
    this->max_speed_ = this->vehicle_data_->GetSpeed() * param.GetPlayerStatusLevel(SPEED_WEIGHT) * rate;
    this->rot_speed_ = this->vehicle_data_->GetRotSpeed() * param.GetPlayerStatusLevel(ROT_SPEED_WEIGHT) * rate;
  }
  else
  {
    this->accel_ = 1000 * param.GetPlayerStatusLevel(ACCEL_WEIGHT);
    this->brake_ = 1000 * param.GetPlayerStatusLevel(ACCEL_WEIGHT);
    this->max_speed_ = 50 * param.GetPlayerStatusLevel(SPEED_WEIGHT);
    this->rot_speed_ = 100 * param.GetPlayerStatusLevel(ROT_SPEED_WEIGHT);
  }
}
