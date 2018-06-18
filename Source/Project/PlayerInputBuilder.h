#pragma once

#include "PlayerInput.h"
#include "Player.h"

class PlayerInputBuilder
{
public:
  static PlayerInputBuilder* CreatePlayer(T_UINT8 player_id);
  static PlayerInputBuilder* CreateComputer(T_UINT8 computer_id);
  static PlayerInputBuilder* CreateDebug();

public:
  void InputProcess(Player* self);

protected:
  virtual void InputProcess(Player* self, PlayerInput* dest) = 0;

public:
  inline const PlayerInput& GetInput() const
  {
    return this->input_;
  }

protected:
  PlayerInput input_;

};