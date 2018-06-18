#pragma once

#include "DevelopParamEditor.h"
#include "GameLevelParam.h"

class GameLevelEditor : public DevelopParamEditor
{
public:
  GameLevelEditor()
    : DevelopParamEditor(&GameLevelParam::GetInstance(), "Asset/json", "GameLevel")
  {
  }
};