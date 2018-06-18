#pragma once

#include "PlayerState.h"
#include "Player.h"

class PlayerStateManager
{
public:
  PlayerStateManager();
  ~PlayerStateManager();

public:
  void ChangeState(Player* player, T_UINT8 state);

public:
  void ResolveInput(Player* player, const PlayerInput& input);

private:
  T_UINT8 current_state_id_;
  PlayerState* current_state_;
  PlayerState* states_[Player::STATE_NUMMAX];

};