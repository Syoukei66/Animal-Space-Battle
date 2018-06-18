#pragma once

#include <HalEngine.h>

class Gauge : public GameObject2D
{
public:
  Gauge(const TextureResource& texture);
  ~Gauge();

public:
  void ViewInit(T_UINT32 max_value, T_UINT32 value);
  void Update();

public:
  void SetAllLayerId(T_UINT8 layer_id);
  void SetMaxValue(T_UINT32 max_value);
  void SetValue(T_UINT32 value);
  void OnUpdateView();
  void SetSize(T_FLOAT width, T_FLOAT height);

public:
  inline T_FLOAT GetWidth() const
  {
    return this->width_;
  }

private:
  T_FLOAT width_;
  Sprite* sprite_;
  T_UINT32 value_;
  T_UINT32 display_value_;
  T_UINT32 value_max_;
};

