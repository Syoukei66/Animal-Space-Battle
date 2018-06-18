#include "PlayerStateManager.h"
#include "PlayerState_Flying.h"
#include "PlayerState_Gacha.h"

PlayerStateManager::PlayerStateManager()
{
  this->states_[Player::STATE_NULL] = new PlayerState_Null();
  this->states_[Player::STATE_FLYING] = new PlayerState_Flying();
  this->states_[Player::STATE_GACHA] = new PlayerState_Gacha();
  this->current_state_ = this->states_[Player::STATE_NULL];
  this->current_state_id_ = Player::STATE_NULL;
}

PlayerStateManager::~PlayerStateManager()
{
  for (T_UINT8 i = 0; i < Player::STATE_NUMMAX; ++i)
  {
    delete this->states_[i];
  }
}

void PlayerStateManager::ChangeState(Player* player, T_UINT8 state)
{
  if (this->current_state_)
  {
    this->current_state_->Finish(player);
  }
  this->current_state_ = this->states_[state];
  this->current_state_->Start(player, this->current_state_id_);
  this->current_state_id_ = state;
}

void PlayerStateManager::ResolveInput(Player* player, const PlayerInput& input)
{
  this->current_state_->ResolveInput(player, input);
}
