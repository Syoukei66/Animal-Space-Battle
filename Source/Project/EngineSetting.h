#ifndef HAL_PROJECT_ENGINESETTING_H
#define HAL_PROJECT_ENGINESETTING_H

#include <HalEngine.h>

class EngineSetting : public IEngineSetting
{

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
  virtual void OnEngineInit() override;
  virtual void OnGameInit() override;
  virtual void OnGameFinal() override;
  virtual void InputSetting(InputSettingBuilder* setting) override;
  virtual Scene* FirstScene() override;
  virtual TSize WinodwSize() override;
  virtual const char* ActivityName() override;
  virtual T_UINT16 RenderCycle() override;

};

#endif
