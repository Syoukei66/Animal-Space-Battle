#pragma once

#include <HalEngine.h>
#include "TimeView.h"

struct PlayerCameraViewport
{
  PlayerCameraViewport()
    : enabled(false)
    , area()
  {}
  bool enabled;
  TAreaf area;
};

class ViewportSetting
{
public:
  static ViewportSetting& GetInstance()
  {
    static ViewportSetting self;
    return self;
  }

public:
  ~ViewportSetting() {}

private:
  ViewportSetting() {}
  ViewportSetting(const ViewportSetting& b) {}

public:
  void Init(T_UINT8 player_count);
  void Uninit();

public:
  bool Update();
  void EditWithImgui();
  inline void ResetDirtyFlag()
  {
    this->is_dirty_ = false;
  }

protected:
  void UpdateViewports();

public:
  inline bool IsDirty() const
  {
    return this->is_dirty_;
  }
  inline const PlayerCameraViewport& GetViewport(T_UINT8 id) const
  {
    const_cast<ViewportSetting*>(this)->UpdateViewports();
    return this->viewports_[id];
  }
  inline T_UINT8 GetViewportCount() const
  {
    return this->viewport_count_;
  }
  inline void SetEnabled(T_UINT8 id, bool enabled)
  {
    this->viewports_[id].enabled = enabled;
    this->is_dirty_ = true;
  }

private:
  PlayerCameraViewport* viewports_;
  T_UINT8 viewport_count_;

  //アップデート単位でのフラグ
  bool is_dirty_;
  //Viewport更新の為のフラグ
  bool viewport_dirty_;

  Camera2D* time_camera_;
  TimeView* left_time_;
  TimeView* gacha_left_time_;

};