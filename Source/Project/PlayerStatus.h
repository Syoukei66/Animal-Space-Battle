#pragma once

#include "AnimalData.h"
#include "VehicleData.h"
#include "PlayerEntry.h"

class PlayerStatus
{
public:
  enum LevelParam
  {
    ACCEL_WEIGHT,
    SPEED_WEIGHT,
    ROT_SPEED_WEIGHT,
    BRAKE_WEIGHT,

    LEVEL_DATANUM,
  };

public:
  PlayerStatus(const PlayerEntry& entry);
  ~PlayerStatus();

public:
  void ChangeVehicle(const VehicleData* vehicle);
  void OnStatusChanged();

public:
  inline const AnimalData* GetAnimalData() const
  {
    return this->animal_data_;
  }
  inline const VehicleData* GetVehcileData() const
  {
    return this->vehicle_data_;
  }
  inline T_FLOAT GetAccel() const
  {
    return this->accel_;
  }
  inline T_FLOAT GetMaxSpeed() const
  {
    return this->max_speed_;
  }
  inline T_FLOAT GetRotationSpeed() const
  {
    return this->rot_speed_;
  }
  inline T_FLOAT GetBrake() const
  {
    return this->brake_;
  }

private:
  const AnimalData* animal_data_;
  const VehicleData* vehicle_data_;
  const T_UINT8 handicap_;

  T_FLOAT accel_;
  T_FLOAT brake_;
  T_FLOAT max_speed_;
  T_FLOAT rot_speed_;

};