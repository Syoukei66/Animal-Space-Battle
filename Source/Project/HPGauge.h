#pragma once

#include "Gauge.h"
#include "NumberView.h"

class Player;

class HPGauge : public GameObject2D
{
public:
  enum DesignEntity
  {
    ANIMAL_ICON_FRAME,
    ICON,
    GAUGE_FRAME,
    GAUGE,

    RANK,

    VEHICLE_ICON_FRAME,
    VEHICLE_ICON,

    SCORE,

    PARAM_DATANUM,
  };

public:
  HPGauge(Player* player);
  ~HPGauge();

public:
  void DesignUpdate(T_FLOAT width, T_FLOAT height);
  void SetAllLayerId(T_UINT8 id);

  void UpdateStatus(Player* player);

private:
  Gauge* gauge_;
  Sprite* gauge_frame_;
  Sprite* icon_;
  Sprite* icon_frame_;
  Sprite* rank_;
  Sprite* vehicle_icon_;
  Sprite* vehicle_icon_frame_;
  NumberView* score_;

  Sprite* player_id_;

  const INativeTexture* rank_textures_[4];
};