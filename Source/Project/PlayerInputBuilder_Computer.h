#pragma once

#include "PlayerInputBuilder.h"

class PlayerInputBuilder_Computer : public PlayerInputBuilder
{
public:
  PlayerInputBuilder_Computer();

public:
  virtual void InputProcess(Player* self, PlayerInput* dest) override;

private:
  T_UINT16 interval_;
  T_UINT16 move_duration_;
  TVec3f move_;
  Star* target_star_;
  T_UINT16 chase_count_;
};