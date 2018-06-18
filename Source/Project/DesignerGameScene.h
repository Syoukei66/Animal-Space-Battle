#pragma once

#include "DeveloperGameScene.h"

class DesignerGameScene : public DeveloperGameScene
{
public:
  virtual DevelopParamEditor* CreateEditor() override;
};