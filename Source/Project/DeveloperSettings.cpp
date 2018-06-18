#include "stdafx.h"
#include "DeveloperSettings.h"

void DeveloperSettings::Load()
{
  JsonResource* setting = JsonResource::DynamicLoad("setting.json");
  JsonNode* node = setting->GetContents()->GetRoot();
  this->debug_mode_ = node->GetValue("DebugMode")->IntValue() > 0;
  this->load_model_ = node->GetValue("LoadModel")->IntValue() > 0;
  this->window_size_.width = node->GetValue("ScreenWidth")->IntValue();
  this->window_size_.height = node->GetValue("ScreenHeight")->IntValue();
  setting->Release();
}
