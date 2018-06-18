#include "EngineSetting.h"

#include "TitleScene.h"
#include "DeveloperInitScene.h"

#include "GameDirector.h"
#include "GameInput.h"

#include "AnimalTable.h"
#include "BulletEmitterTable.h"
#include "VehicleTable.h"
#include "GachaTable.h"

#include "DeveloperSettings.h"

void EngineSetting::OnEngineInit()
{
  Util::RandomInit();
  DeveloperSettings::GetInstance()->Load();
}

void EngineSetting::OnGameInit()
{
  BulletEmitterTable::GetInstance().Load();
  VehicleTable::GetInstance().Load();
  AnimalTable::GetInstance().Load();
  GachaTable::GetInstance().Load();
}

void EngineSetting::OnGameFinal()
{
  GameDirector::Finalize(nullptr);
  GachaTable::GetInstance().Unload();
  AnimalTable::GetInstance().Unload();
  VehicleTable::GetInstance().Unload();
  BulletEmitterTable::GetInstance().Unload();
}

void EngineSetting::InputSetting(InputSettingBuilder* setting)
{
  setting->SetPlayerCount(4);
  setting->Register(GameInput::GetInputEntities(), GameInput::GAME_INPUT_DATANUM);
}

Scene* EngineSetting::FirstScene()
{
  if (DeveloperSettings::GetInstance()->IsDebugMode())
  {
    return new DeveloperInitScene();
  }
  return new TitleScene();
}

TSize EngineSetting::WinodwSize()
{
  return DeveloperSettings::GetInstance()->GetWindowSize();
}

const char* EngineSetting::ActivityName()
{
  return "Test";
}

T_UINT16 EngineSetting::RenderCycle()
{
  return 1000 / 60;
}
