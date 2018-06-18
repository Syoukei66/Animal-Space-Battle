#include "PlayerState.h"


void PlayerState::Start(Player* self, T_UINT8 old_state)
{
  this->old_state_ = old_state;
  this->OnStart(self);
}

void PlayerState::Finish(Player* self)
{
  this->OnFinish(self);
}

void PlayerState::ResolveInput(Player* self, const PlayerInput& input)
{
  this->ResolveInputProcess(self, input);
}

void PlayerState::ReturnState(Player* self)
{
  self->ChangeState(this->old_state_);
}
