#pragma once

#include "PlayerEntry.h"
#include "BaseBulletEmitter.h"
#include "PlayerInput.h"

class BulletEmitterManager
{
public:
  BulletEmitterManager(Player* player);
  ~BulletEmitterManager();

public:
  void Update();
  void ChangeVehicle(const VehicleData* data);
  void Emission(const PlayerInput& input);
  T_UINT32 CollisionToPlayer(Player* player);
  T_UINT32 CollisionToStar(Star* star);

private:
  BaseBulletEmitter** emitter_pool_;
  T_UINT16 pooled_emitter_count_;

  BaseBulletEmitter* emitter_normal_;
  BaseBulletEmitter* emitter_power_;

};