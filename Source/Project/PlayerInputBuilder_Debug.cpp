#include "stdafx.h"
#include "PlayerInputBuilder_Debug.h"

void PlayerInputBuilder_Debug::InputProcess(Player* self, PlayerInput* dest)
{
  dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_BRAKE);
}
