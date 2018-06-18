#include "PlayerInputBuilder_Computer.h"
#include "StarManager.h"
#include "Environment.h"

PlayerInputBuilder_Computer::PlayerInputBuilder_Computer()
  : interval_()
  , move_duration_()
  , move_()
  , target_star_(nullptr)
{
}

void PlayerInputBuilder_Computer::InputProcess(Player* self, PlayerInput* dest)
{
  dest->ResetCommandInput();
  //星を追いかける処理
  if (this->target_star_)
  {
    if (this->target_star_->GetMaster() == self || this->chase_count_ == 0)
    {
      this->target_star_ = nullptr;
      this->chase_count_ = 0;
      return;
    }
    const T_FLOAT rot_speed = self->GetStatus().GetRotationSpeed();
    const TVec3f dist = this->target_star_->GetTransform()->GetWorldPosition() - self->GetTransform()->GetWorldPosition();
    const TVec3f dist_norm = dist.Normalized();
    const TVec3f xvec = self->GetTransform()->GetWorldMatrix().GetCameraXVec();
    const TVec3f yvec = self->GetTransform()->GetWorldMatrix().GetCameraYVec();
    T_FLOAT x = TVec3f::InnerProduct(xvec, dist_norm);
    T_FLOAT y = TVec3f::InnerProduct(yvec, dist_norm);
    if (fabs(x) + fabs(y) < 0.5f)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_ACCEL);
    }
    else
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_SHOT);
    }
    if (fabs(x) + fabs(y) > 1.0f)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_BRAKE);
    }
    dest->SetVectorInput(TVec3f(x, y, 0.0f));
    --this->chase_count_;
    return;
  }
  //プレイヤーを追いかける処理
  if (this->chase_count_ > 0)
  {
    Player* target = self->GetTarget();
    if (!target)
    {
      this->chase_count_ = 0;
      return;
    }
    const T_FLOAT rot_speed = self->GetStatus().GetRotationSpeed();
    const TVec3f dist = target->GetTransform()->GetWorldPosition() - self->GetTransform()->GetWorldPosition();
    const TVec3f dist_norm = dist.Normalized();
    const TVec3f xvec = self->GetTransform()->GetWorldMatrix().GetCameraXVec();
    const TVec3f yvec = self->GetTransform()->GetWorldMatrix().GetCameraYVec();
    T_FLOAT x = TVec3f::InnerProduct(xvec, dist_norm);
    T_FLOAT y = TVec3f::InnerProduct(yvec, dist_norm);
    if (fabs(x) + fabs(y) < 0.5f)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_ACCEL);
    }
    if (fabs(x) + fabs(y) > 1.0f)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_BRAKE);
    }
    else
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_SHOT);
    }
    dest->SetVectorInput(TVec3f(x, y, 0.0f));
    --this->chase_count_;
    return;
  }

  //さまよう処理
  if (this->interval_ > 0)
  {
    --this->interval_;
  }
  else
  {
    this->move_duration_ = Util::GetRandom(30, 120);
    this->interval_ = Util::GetRandom(60, 180);

    T_UINT8 act = Util::GetRandom(0, 100);
    if (act % 2 == 0)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_SHOT);
    }
    if (act < 20)
    {
      this->move_ = TVec3f(Util::GetRandom(-1.0f, 1.0f), Util::GetRandom(-1.0f, 1.0f), Util::GetRandom(-1.0f, 1.0f));
    }
    else if (act < 40)
    {
      dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_LOCKON);
      this->chase_count_ = this->interval_;
      this->interval_ = 0;
    }
    else
    {
      this->target_star_ = Environment::GetInstance().GetNearestNotHoldedStar(self);
      this->chase_count_ = this->interval_;
      this->interval_ = 0;
    }
  }
  if (this->move_duration_ > 0)
  {
    dest->SetVectorInput(this->move_);
    --this->move_duration_;
  }
  else
  {
    dest->SetVectorInput(TVec3f(0.0f, 0.0f, 0.0f));
  }
  if (this->interval_ > 120)
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_ACCEL);
  }
  else if (this->interval_ > 60)
  {

  }
  else if (this->interval_ > 0)
  {
    dest->SetCommandInput(PlayerInput::PLAYER_COMMAND_BRAKE);
  }
  // TODO: return ステートメントをここに挿入します
}
