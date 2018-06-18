#pragma once

#include <HalEngine.h>

#include "Gauge.h"
#include "HPGauge.h"

class Player;

class PlayerUI : public GameObject2D
{
public:
  PlayerUI(Player* player);
  ~PlayerUI();

public:
  void GachaCountDown(T_INT32 left_time);
  void GameViewMode();
  void GachaViewMode();
  void OnDead();
  void SetAllLayerId(T_UINT8 id);
  void UiUpdate(Camera2D* ui_camera, Camera3D_LookAt* player_camera);

private:
  Player* player_;
  HPGauge* hp_gauge_;
  Sprite* target_;
  Sprite* effect_;
  EntityModifierRoot* gacha_effect_modifier_;
  EntityModifierRoot* death_effect_modifier_;

  AnimatedSprite* count_message_;
  AnimatedSprite* count_number_;
  GameObject2D* count_base_;
  EntityModifierRoot* count_modifier_;

  bool is_gacha_view_;

};