#include "BulletTestGameScene.h"
#include "GameDirector.h"
#include "DeveloperUtil.h"
#include "AnimalTable.h"
#include "VehicleTable.h"
#include "GameLevelParam.h"

void BulletTestGameScene::OnSetup()
{
  PlayerEntry* entry = GameDirector::GetPlayerEntryList()->AddDebugEntity();
  entry->animal_data = AnimalTable::GetInstance().GetData(0);
  entry->vehicle_data = VehicleTable::GetInstance().GetData(0);
  BaseGameScene::OnSetup();
  GameLevelParam::GetInstance().SetStarLevel(StarManager::COUNT, 0);
}

void BulletTestGameScene::Update()
{
  BaseGameScene::Update();
  using namespace DeveloperUtil;
  ShowDebugWindow(DEBUG_RETURN_INIT_SCENE | DEBUG_CP_CAMERA | DEBUG_RETURN_INIT_SCENE);
}
