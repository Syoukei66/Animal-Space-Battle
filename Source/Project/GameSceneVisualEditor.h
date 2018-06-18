#pragma once

#include "DevelopParamEditor.h"
#include "GameSceneVisualParam.h"

class GameSceneVisualEditor : public DevelopParamEditor
{
public:
  GameSceneVisualEditor()
    : DevelopParamEditor(&GameSceneVisualParam::GetInstance(), "Asset/json", "GameSceneVisual")
  {
  }

};