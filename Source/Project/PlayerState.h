#pragma once

#include "PlayerInput.h"
#include "Player.h"

class PlayerState
{
public:
  virtual ~PlayerState() {}

public:
  void Start(Player* self, T_UINT8 old_state);
  void Finish(Player* self);
  void ResolveInput(Player* self, const PlayerInput& input);

protected:
  virtual void OnStart(Player* self) = 0;
  virtual void OnFinish(Player* self) = 0;
  virtual void ResolveInputProcess(Player* self, const PlayerInput& input) = 0;

  void ReturnState(Player* self);

private:
  T_UINT8 old_state_;

};

class PlayerState_Null : public PlayerState
{
protected:
  void OnStart(Player* self) override {}
  void OnFinish(Player* self) override {}
  void ResolveInputProcess(Player* self, const PlayerInput& input) override {}
};