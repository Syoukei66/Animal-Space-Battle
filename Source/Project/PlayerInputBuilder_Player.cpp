#include "PlayerInputBuilder_Player.h"

PlayerInputBuilder_Player::PlayerInputBuilder_Player(T_UINT8 input_id)
  : id_(input_id)
{
}

void PlayerInputBuilder_Player::InputProcess(Player* self, PlayerInput* dest)
{
  using namespace HalEngine;
  InputState* input = Input(this->id_);
  T_FLOAT x = input->GetAxis(GameInput::X_AXIS, 0.2f);
  T_FLOAT y = input->GetAxis(GameInput::Y_AXIS, 0.2f);
  T_FLOAT z = 0.0f;
  //  T_FLOAT z = input->GetAxis(GameInput::R2, 0.2f) - input->GetAxis(GameInput::L2, 0.2f);
  dest->SetVectorInput(x, y, z);

  dest->ResetCommandInput();
  if (input->GetButton(GameInput::ACCEL))
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_ACCEL);
  }
  if (input->GetButton(GameInput::BRAKE))
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_BRAKE);
  }
  if (input->GetButtonDown(GameInput::LOCKON))
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_LOCKON);
  }
  if (input->GetButton(GameInput::FIRE))
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_SHOT);
  }
}
