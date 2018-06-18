#pragma once

#include "PlayerInputBuilder.h"

class PlayerInputBuilder_Player : public PlayerInputBuilder
{
public:
  PlayerInputBuilder_Player(T_UINT8 input_id);

public:
  virtual void InputProcess(Player* self, PlayerInput* dest) override;

private:
  T_UINT8 id_;

};