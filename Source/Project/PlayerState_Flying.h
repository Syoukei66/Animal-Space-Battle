#pragma once

#include "PlayerState.h"

class PlayerState_Flying : public PlayerState
{
protected:
  virtual void OnStart(Player* self) override;
  virtual void OnFinish(Player* self) override;
  void ResolveInputProcess(Player* self, const PlayerInput& input) override;

};