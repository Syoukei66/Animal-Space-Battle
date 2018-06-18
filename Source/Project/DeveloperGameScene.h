#pragma once

#include "BaseGameScene.h"
#include "DevelopParamEditor.h"

class DeveloperInitScene;

class DeveloperGameScene : public BaseGameScene
{
public:
  virtual void OnSetup() override;
  virtual void OnUnload() override;

public:
  void PreUpdate() override;
  void Update() override;

protected:
  virtual DevelopParamEditor* CreateEditor() = 0;

private:
  DevelopParamEditor* editor_;
  bool show_computer_camera_;

};