#include "LevelGameScene.h"
#include "GameLevelEditor.h"
DevelopParamEditor* LevelGameScene::CreateEditor()
{
  return new GameLevelEditor();
}

