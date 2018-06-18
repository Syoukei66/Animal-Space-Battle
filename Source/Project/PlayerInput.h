#pragma once

#include <HalEngine.h>

class PlayerInput
{
public:
  enum CommandKind
  {
    PLAYER_COMMAND_SHOT,
    PLAYER_COMMAND_ACCEL,
    PLAYER_COMMAND_BRAKE,
    PLAYER_COMMAND_LOCKON,

    PLAYER_COMMAND_DATANUM,

    PLAYER_COMMAND_NONE,
  };
public:
  PlayerInput()
    : vector_input_()
    , command_input_(0)
  {}

public:
  inline void SetVectorInput(const TVec3f& input)
  {
    this->vector_input_ = input;
    T_FLOAT length = this->vector_input_.Length();
    if (length > 1.0f)
    {
      this->vector_input_ /= length;
    }
  }
  inline void SetVectorInput(T_FLOAT x, T_FLOAT y, T_FLOAT z)
  {
    this->vector_input_.x = x;
    this->vector_input_.y = y;
    this->vector_input_.z = z;
    T_FLOAT length = this->vector_input_.Length();
    if (length > 1.0f)
    {
      this->vector_input_ /= length;
    }
  }
  inline const TVec3f& GetVectorInput() const
  {
    return this->vector_input_;
  }
  inline void ResetCommandInput()
  {
    this->command_input_ = 0;
  }
  inline void SetCommandInput(CommandKind command)
  {
    this->command_input_ |= 1 << command;
  }
  inline bool IsCommand(CommandKind command) const
  {
    return this->command_input_ & (1 << command);
  }

private:
  TVec3f vector_input_;
  T_UINT8 command_input_;
};
