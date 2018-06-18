#pragma once

#include "PlayerInputBuilder.h"

class PlayerInputBuilder_Debug : public PlayerInputBuilder
{
public:
  virtual void InputProcess(Player* self, PlayerInput* dest) override;

};