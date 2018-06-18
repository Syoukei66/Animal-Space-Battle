#include "PlayerState_Flying.h"
#include "Player.h"
#include "PlayerManager.h"

void PlayerState_Flying::OnStart(Player* self)
{
}

void PlayerState_Flying::OnFinish(Player* self)
{
}

void PlayerState_Flying::ResolveInputProcess(Player* self, const PlayerInput& input)
{
  const T_FLOAT rot_speed = self->GetStatus().GetRotationSpeed();
  TVec3f vr = TVec3f();
  vr.x = input.GetVectorInput().x;
  vr.y = input.GetVectorInput().y;
  vr.z = input.GetVectorInput().z;
  vr = vr * rot_speed;
  self->GetTransform()->RotateY(vr.x);
  self->GetTransform()->RotateX(-vr.y);
  self->GetTransform()->RotateZ(vr.z);

  TVec3f speed = TVec3f();
  if (input.IsCommand(PlayerInput::PLAYER_COMMAND_BRAKE))
  {
    speed = -self->GetVelocity().Normalized();
    self->AddVelocity(speed.Normalized() * self->GetStatus().GetBrake());
  }
  else if (input.IsCommand(PlayerInput::PLAYER_COMMAND_ACCEL))
  {
    speed += self->GetTransform()->GetMatrix().GetCameraZVec();
    self->AddVelocity(speed.Normalized() * self->GetStatus().GetAccel());
  }
 
  if (input.IsCommand(PlayerInput::PLAYER_COMMAND_LOCKON))
  {
    Player* current_target = self->GetTarget();
    self->SetTarget(nullptr);
    bool targeted = false;
    PlayerManager::GetInstance().Loop([&](Player* target)
    {
      if (targeted || target == self)
      {
        return;
      }
      if (current_target && target->GetID() <= current_target->GetID())
      {
        return;
      }
      //Ž‹‘ä‚ð—p‚¢‚½•û–@‚É•Ï‚¦‚é
      TVec3f distance = (self->GetTransform()->GetWorldPosition() - target->GetTransform()->GetWorldPosition()).Normalized();
      T_FLOAT dot = -TVec3f::InnerProduct(self->GetWorldMatrix().GetDirection3d(), distance);
      dot *= fabs(dot * dot * dot * dot * dot);
      if (dot <= 0.1f)
      {
        return;
      }
      self->SetTarget(target);
      targeted = true;
    });
  }

  if (!self->IsDead() && input.IsCommand(PlayerInput::PLAYER_COMMAND_SHOT))
  {
    self->GetBulletEmitter()->Emission(input);
  }
}
