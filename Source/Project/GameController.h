#pragma once

#include <HalEngine.h>
#include "PlayerManager.h"
#include "StarManager.h"
#include "Field.h"

class BaseGameScene;

class GameController
{
public:
  GameController(BaseGameScene* scene);

public:
  void OnLoad(IResourceLoadReserver* resource);
  void OnSetup();
  void OnUnload();
  void OnShow(ISceneShowListener* listener);
  void OnHide(ISceneHideListener* listener);
  void Update();
  void PostUpdate();

private:
  BaseGameScene* scene_;

  StarManager* star_manager_;
  Field* field_;
  T_UINT32 rest_time_;
};