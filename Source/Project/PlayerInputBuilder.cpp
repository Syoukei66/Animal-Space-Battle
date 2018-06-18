#include "PlayerInputBuilder.h"

#include "PlayerInputBuilder_Player.h"
#include "PlayerInputBuilder_Computer.h"
#include "PlayerInputBuilder_Debug.h"

PlayerInputBuilder* PlayerInputBuilder::CreatePlayer(T_UINT8 player_id)
{
  return new PlayerInputBuilder_Player(player_id);
}

PlayerInputBuilder* PlayerInputBuilder::CreateComputer(T_UINT8 computer_id)
{
  return new PlayerInputBuilder_Computer();
}

PlayerInputBuilder* PlayerInputBuilder::CreateDebug()
{
  return new PlayerInputBuilder_Debug();
}

void PlayerInputBuilder::InputProcess(Player* self)
{
  this->InputProcess(self,  &this->input_);
}
