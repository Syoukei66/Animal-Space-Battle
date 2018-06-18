#include "stdafx.h"
#include "DebugResultScene.h"
#include "DeveloperUtil.h"

void DebugResultScene::Update()
{
  ResultScene::Update();
  DeveloperUtil::ShowDebugWindow(DeveloperUtil::DEBUG_RETURN_INIT_SCENE);
}
