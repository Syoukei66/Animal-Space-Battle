#include "ViewportSetting.h"
#include "GameDirector.h"
#include "GameLayer.h"
#include "PlayerManager.h"

static const T_UINT32 GAME_TIME = 1000 * 60 * 3;

void ViewportSetting::Init(T_UINT8 player_count)
{
  this->viewport_count_ = player_count;
  this->viewports_ = new PlayerCameraViewport[this->viewport_count_];

  this->time_camera_ = new Camera2D();
  this->time_camera_->GetRenderState()->AddTargetLayerId(GameLayer::LAYER_TIME);
  this->time_camera_->SetViewportClear(false);
  GameDirector::GetScene()->AddCamera(this->time_camera_);

  this->left_time_ = new TimeView();
  this->left_time_->SetAllLayerId(GameLayer::LAYER_TIME);
  GameDirector::GetScene()->AddChild(this->left_time_);
  this->left_time_->SetValule(GAME_TIME);

  this->gacha_left_time_ = new TimeView();
  this->gacha_left_time_->SetAllLayerId(GameLayer::LAYER_TIME);
  GameDirector::GetScene()->AddChild(this->gacha_left_time_);
}

void ViewportSetting::Uninit()
{
  delete this->gacha_left_time_;
  delete this->left_time_;
  delete this->time_camera_;
  delete[] this->viewports_;
  this->viewport_count_ = 0;
}

bool ViewportSetting::Update()
{
  T_INT32 gacha_left_time = this->gacha_left_time_->GetValue();
  if (gacha_left_time < 3000)
  {
    PlayerManager::GetInstance().GachaCountDown(gacha_left_time);
  }
  if (this->gacha_left_time_->GetValue() < 0.1f)
  {
    PlayerManager::GetInstance().StartGacha();
    this->gacha_left_time_->SetValule(1000 * 30);
  }
  if (this->left_time_->GetValue() < 0.1f)
  {
    return true;
  }
  return false;
}

void ViewportSetting::EditWithImgui()
{
}

void ViewportSetting::UpdateViewports()
{
  if (!this->is_dirty_)
  {
    return;
  }
  T_UINT8 enabled_viewport_count = 0;
  for (T_UINT8 i = 0; i < this->viewport_count_; ++i)
  {
    if (this->viewports_[i].enabled)
    {
      ++enabled_viewport_count;
    }
  }
  T_UINT8 x_num = 0;
  T_UINT8 y_num = 0;
  T_UINT8 bar_pos = 0;
  if (enabled_viewport_count == 1)
  {
    x_num = 1;
    y_num = 1;
    bar_pos = 1;
  }
  else if (enabled_viewport_count == 2)
  {
    x_num = 1;
    y_num = 2;
    bar_pos = 1;
  }
  else if (enabled_viewport_count <= 4)
  {
    x_num = 2;
    y_num = 2;
    bar_pos = 1;
  }
  else if (enabled_viewport_count <= 6)
  {
    x_num = 3;
    y_num = 2;
    bar_pos = 1;
  }
  else if (enabled_viewport_count <= 9)
  {
    x_num = 3;
    y_num = 3;
    bar_pos = 3;
  }
  else if (enabled_viewport_count <= 12)
  {
    x_num = 3;
    y_num = 4;
    bar_pos = 2;
  }
  else if (enabled_viewport_count <= 16)
  {
    x_num = 4;
    y_num = 4;
    bar_pos = 4;
  }

  const T_FLOAT screen_width = (T_FLOAT)Director::GetInstance()->GetScreenWidth();
  const T_FLOAT screen_height = (T_FLOAT)Director::GetInstance()->GetScreenHeight();
  const T_FLOAT padding = 2.0f;
  const T_FLOAT bar_height = 36.0f;
  TAreaf viewport;
  viewport.size.width = (screen_width - padding * (x_num + 1)) / x_num;
  viewport.size.height = (screen_height - bar_height - padding * y_num) / y_num;
  T_UINT8 viewport_id = 0;
  for (T_UINT8 id = 0; id < enabled_viewport_count; ++id)
  {
    if (!this->viewports_[id].enabled)
    {
      continue;
    }
    const T_UINT8 x = id % x_num;
    const T_UINT8 y = id / x_num;
    viewport.pos.x = padding + (viewport.size.width + padding) * x;
    viewport.pos.y = padding + (viewport.size.height + padding) * y;
    if (y >= bar_pos)
    {
      viewport.pos.y += bar_height - padding;
    }
    this->viewports_[viewport_id].area = viewport;
    ++viewport_id;
  }
  static T_FLOAT TIME_WIDTH = 180.0f;
  this->left_time_->GetTransform()->SetX(-screen_width * 0.5f + TIME_WIDTH * 0.5f);
  this->left_time_->GetTransform()->SetY(screen_height * 0.5f - bar_pos * viewport.size.height - bar_height * 0.5f);
  this->left_time_->SetSize(TIME_WIDTH, bar_height);

  this->gacha_left_time_->GetTransform()->SetX(screen_width * 0.5f - TIME_WIDTH * 0.5f);
  this->gacha_left_time_->GetTransform()->SetY(screen_height * 0.5f - bar_pos * viewport.size.height - bar_height * 0.5f);
  this->gacha_left_time_->SetSize(TIME_WIDTH, bar_height);
}
