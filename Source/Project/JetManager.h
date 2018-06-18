#pragma once

#include "VehicleModelDesignParam.h"

class PlayerActor;

class JetManager
{
public:
  JetManager();
  ~JetManager();

public:
  void AttachToVehicle(GameObject3D* vehicle);
  void DetachFromVehicle();

public:
  void Update();

public:
  void SetAllLayerId(T_UINT8 layer_id);
  void ApplyDesignParams(const VehicleModelDesignParam* design);
  void SetAccel(const TVec3f& accel);

private:
  Model* jet_main_[2];

};