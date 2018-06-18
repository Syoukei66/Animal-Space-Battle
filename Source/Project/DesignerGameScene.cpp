#include "DesignerGameScene.h"
#include "GameSceneVisualEditor.h"

DevelopParamEditor* DesignerGameScene::CreateEditor()
{
  return new GameSceneVisualEditor();
}
