#include "PlayerUI.h"
#include "Player.h"
#include "GameSceneVisualParam.h"

PlayerUI::PlayerUI(Player* player)
  : player_(player)
{
  this->target_ = Sprite::CreateWithResource(Asset::Texture::UI_GAME_LOCKON);
  this->target_->SetVisible(false);
  this->target_->GetTransform()->SetScale(0.1f);
  this->AddChild(this->target_);

  this->effect_ = Sprite::CreateWithResource(Asset::Texture::UI_GAME_BG);
  this->effect_->SetVisible(false);
  this->AddChild(this->effect_);

  this->hp_gauge_ = new HPGauge(player);
  this->AddChild(this->hp_gauge_);

  EntityModifier* m00 = EntityModifierFactory::ColorFromTo(10, Color4F::WHITE, Color4F::CreateBy4BitFormat(255, 0, 0, 160));
  EntityModifier* m01 = EntityModifierFactory::ColorTo(120, Color4F::CreateBy4BitFormat(0, 0, 0, 160));
  EntityModifier* m0 = EntityModifierFactory::Sequence(m00, m01);
  this->death_effect_modifier_ = EntityModifierFactory::Root(m0);
  this->death_effect_modifier_->Retain();
  this->death_effect_modifier_->Stop();
  this->effect_->RegisterEntityModifier(this->death_effect_modifier_);

  EntityModifier* m10 = EntityModifierFactory::ColorFromTo(30, Color4F::WHITE, Color4F::CreateBy4BitFormat(0, 0, 0, 0));
  this->gacha_effect_modifier_ = EntityModifierFactory::Root(m10);
  this->gacha_effect_modifier_->Retain();
  this->gacha_effect_modifier_->Stop();
  this->gacha_effect_modifier_->AddEntityModifierListener([&]() {
    this->effect_->SetVisible(false);
  });
  this->effect_->RegisterEntityModifier(this->gacha_effect_modifier_);

  this->count_base_ = new GameObject2D();
  this->count_base_->SetVisible(false);
  this->AddChild(this->count_base_);

  this->count_message_ = AnimatedSprite::CreateWithResource(Asset::Texture::UI_GAME_COUNT_MESSAGE, 1, 2);
  this->count_message_->GetMaterial()->GetDiffuse().SetAlpha(0.5f);
  this->count_message_->GetTransform()->SetScale(1.5f);
  this->count_message_->GetTransform()->SetY(200.0f);
  this->count_base_->AddChild(this->count_message_);

  this->count_number_ = AnimatedSprite::CreateWithResource(Asset::Texture::UI_GAME_COUNT_NUMBER, 5, 2);
  this->count_number_->GetMaterial()->GetDiffuse().SetAlpha(0.5f);
  this->count_number_->GetTransform()->SetScale(1.0f);
  this->count_number_->GetTransform()->SetY(-60.0f);
  this->count_base_->AddChild(this->count_number_);
  
  EntityModifier* m2 = EntityModifierFactory::ScaleFromTo(60, 1.0f, 1.2f);
  this->count_modifier_ = EntityModifierFactory::Root(m2);
  this->count_modifier_->Retain();
  this->count_modifier_->Stop();
  this->count_base_->RegisterEntityModifier(this->count_modifier_);

  this->is_gacha_view_ = false;
}

PlayerUI::~PlayerUI()
{
  this->count_modifier_->Release();
  delete this->count_base_;
  delete this->count_message_;
  delete this->count_number_;
  delete this->hp_gauge_;
  this->gacha_effect_modifier_->Release();
  this->death_effect_modifier_->Release();
  delete this->effect_;
  delete this->target_;
}

void PlayerUI::GachaCountDown(T_INT32 left_time)
{
  if (left_time > 2000)
  {
    if (this->count_number_->GetCurrentIndex() == 0)
    {
      this->count_number_->SetCurrentIndex(3);
      this->count_modifier_->Play();
      this->count_base_->SetVisible(true);
    }
  }
  else if (left_time > 1000)
  {
    if (this->count_number_->GetCurrentIndex() == 3)
    {
      this->count_number_->SetCurrentIndex(2);
      this->count_modifier_->Play();
    }
  }
  else if (left_time > 0)
  {
    if (this->count_number_->GetCurrentIndex() == 2)
    {
      this->count_number_->SetCurrentIndex(1);
      this->count_modifier_->Play();
    }
  }
}

void PlayerUI::GameViewMode()
{
  this->count_modifier_->Play();
  this->target_->SetVisible(this->player_->GetTarget());
  this->effect_->SetVisible(false);
  this->is_gacha_view_ = false;
}

void PlayerUI::GachaViewMode()
{
  this->count_number_->SetCurrentIndex(0);
  this->count_base_->SetVisible(false);
  this->target_->SetVisible(false);
  this->effect_->SetVisible(true);
  this->gacha_effect_modifier_->Play();
  this->is_gacha_view_ = true;
}

void PlayerUI::OnDead()
{
  this->effect_->SetVisible(true);
  this->death_effect_modifier_->Play();
}

void PlayerUI::SetAllLayerId(T_UINT8 id)
{
  this->hp_gauge_->SetAllLayerId(id);
  this->target_->SetLayerId(id);
  this->effect_->SetLayerId(id);
  this->count_message_->SetLayerId(id);
  this->count_number_->SetLayerId(id);
}

void PlayerUI::UiUpdate(Camera2D* ui_camera, Camera3D_LookAt* player_camera)
{
  const T_FLOAT viewport_width = ui_camera->GetViewportWidth();
  const T_FLOAT viewport_height = ui_camera->GetViewportHeight();
  
  const T_FLOAT x_rate = viewport_width / Director::GetInstance()->GetScreenWidth();
  const T_FLOAT y_rate = viewport_height / Director::GetInstance()->GetScreenHeight();

  this->count_base_->GetTransform()->SetScale(std::min(x_rate, y_rate));

  this->effect_->SetSize(viewport_width, viewport_height);

  this->hp_gauge_->DesignUpdate(viewport_width, viewport_height);

  this->hp_gauge_->UpdateStatus(this->player_);

  Player* target = this->player_->GetTarget();
  if (this->is_gacha_view_)
  {
    return;
  }
  this->target_->SetVisible(target);
  if (!target)
  {
    return;
  }
  const T_FLOAT min_x = -viewport_width * 0.5f;
  const T_FLOAT max_x =  viewport_width * 0.5f;
  const T_FLOAT min_y = -viewport_height * 0.5f;
  const T_FLOAT max_y =  viewport_height * 0.5f;
  const TVec3f pos = player_camera->Get2dPositionScale(target);
  if (pos.z > 0.0f)
  {
    const T_FLOAT x = std::max(min_x, std::min(max_x, pos.x * viewport_width * 0.5f));
    const T_FLOAT y = std::max(min_y, std::min(max_y, pos.y * viewport_height * 0.5f));
    this->target_->GetTransform()->SetPositon(x, y);
  }
}
