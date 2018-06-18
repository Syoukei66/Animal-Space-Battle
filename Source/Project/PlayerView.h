#pragma once

#include "PlayerUI.h"
#include "GachaEffect.h"

class PlayerView
{
public:
  static PlayerView* Create(Player* player);

private:
  PlayerView(Player* player);

public:
  ~PlayerView();

public:
  void AttachAdditionToScene(Scene* scene);
  void DetachAdditionFromScene(Scene* scene);

public:
  void GachaCountDown(T_INT32 left_time);
  void OnDead();
  void GameViewMode();
  void GachaViewMode();
  void ViewportUpdate();

public:
  inline const Camera3D_LookAt* GetCamera() const
  {
    return this->player_camera_;
  }
  
private:
  Player* player_;
  PlayerUI* ui_;
  Camera2D* ui_camera_;
  Camera3D_LookAt* player_camera_;
  Sprite* view_3d_;
  Material* post_effect_;
  INativeRenderTexture* render_target_;

};