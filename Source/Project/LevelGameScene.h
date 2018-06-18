#pragma once

#include "DeveloperGameScene.h"

class LevelGameScene : public DeveloperGameScene
{
public:
  virtual DevelopParamEditor* CreateEditor() override;
};