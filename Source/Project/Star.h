#pragma once

#include <HalEngine.h>

#include "GameEntity.h"

class Player;

class Star : public GameEntity, public IPoolAllocatable
{
public:
  Star();
  ~Star();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

public:
  virtual void Update() override;

public:
  void SetMaster(Player* player, const TVec3f& vec);
  void AddDamage(Player* player, T_UINT16 damage);

private:
  void MakeHitEffect(Player* player);

public:
  inline Player* GetMaster() const
  {
    return this->master_;
  }
  inline T_UINT16 GetMasteredTime() const
  {
    return this->mastered_time_;
  }
  inline T_UINT16 GetNeedMasteredTime() const
  {
    return this->need_mastered_time_;
  }

private:
  Player* master_;
  T_UINT16 mastered_time_;
  T_UINT16 need_mastered_time_;
  T_UINT16 hit_effect_count_;
  Model* body_;
  Model* wall_model_;
  GameObject3D* wall_;

};