#pragma once

#include "PlayerState.h"
#include "GachaEffect.h"

class PlayerState_Gacha : public PlayerState
{
public:
  PlayerState_Gacha();
  ~PlayerState_Gacha();

public:
  virtual void OnStart(Player* self) override;
  virtual void OnFinish(Player* self) override;
  virtual void ResolveInputProcess(Player* self, const PlayerInput& input) override;

private:
  GachaEffect* effect_;
  T_UINT32 count_;

};