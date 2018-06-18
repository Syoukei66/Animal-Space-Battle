#pragma once

#include <HalEngine.h>
#include "GameController.h"

class BaseGameScene : public Scene
{
public:
  BaseGameScene();
  ~BaseGameScene();

public:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

  virtual void Update() override;
  virtual void PostUpdate() override;

private:
  GameController* controller_;

};