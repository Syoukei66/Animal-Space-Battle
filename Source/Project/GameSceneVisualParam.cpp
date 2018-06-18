#include "GameSceneVisualParam.h"

struct LevelParamInfo
{
  const char* name;
  DesignData::SizeType size_type;
  T_INT8 parent;
};

static const char* ID_HP_GAUGE = "HpGauge";
static const LevelParamInfo PARAMS_HP_GAUGE[HPGauge::PARAM_DATANUM] =
{
  { "animal_icon_frame", DesignData::SizeType::SCALE, -1 },
  { "animal_icon", DesignData::SizeType::SCALE, HPGauge::DesignEntity::ANIMAL_ICON_FRAME },
  { "gauge_frame", DesignData::SizeType::SIZE, HPGauge::DesignEntity::ANIMAL_ICON_FRAME },
  { "gauge", DesignData::SizeType::SIZE, HPGauge::DesignEntity::GAUGE_FRAME },
  { "rank", DesignData::SizeType::SCALE, -1 },
  { "vehicle_icon_frame", DesignData::SizeType::SCALE, -1 },
  { "vehicle_icon", DesignData::SizeType::SCALE, HPGauge::DesignEntity::VEHICLE_ICON_FRAME },
  { "score", DesignData::SizeType::SIZE, -1 },
};

//static const LevelParamInfo HP_GAUGE_PARAMS[HPGauge::PARAM_DATANUM] =
//{
//  { "GaugeX", u8"ゲージX",
//  -0.5f, 0.5f, "%.2f" },
//
//  { "GaugeY", u8"ゲージY",
//  -0.5f, 0.5f, "%.2f" },
//
//  { "GaugeWidth", u8"ゲージWidth",
//  0.0f, 1.0f, "%.2f" },
//
//  { "GaugeHeight", u8"ゲージHeight",
//  0.0f, 1.0f, "%.2f" },
//
//  { "IconX", u8"アイコンX",
//  -0.5f, 0.5f, "%.2f" },
//
//  { "IconY", u8"アイコンY",
//  -0.5f, 0.5f, "%.2f" },
//
//  { "IconSize", u8"アイコンSize",
//  0.0f, 1.0f, "%.2f" },
//};

static const T_UINT8 MENU_HEIGHT = 160;
static const T_UINT8 BAR_HEIGHT = 40;

GameSceneVisualParam::GameSceneVisualParam()
  : hp_gauge_params_dirty_(true)
{
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    this->hp_gauge_params_[i] = new DesignData(PARAMS_HP_GAUGE[i].name);
    this->hp_gauge_params_[i]->SetSizeType(PARAMS_HP_GAUGE[i].size_type);
  }
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    if (PARAMS_HP_GAUGE[i].parent == -1)
    {
      continue;
    }
    this->hp_gauge_params_[i]->SetParent(this->hp_gauge_params_[PARAMS_HP_GAUGE[i].parent]);
  }
}

GameSceneVisualParam::~GameSceneVisualParam()
{
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    delete this->hp_gauge_params_[i];
  }
}

void GameSceneVisualParam::LoadFromJson(JsonNode* node)
{
  JsonNode* status = node->GainNode(ID_HP_GAUGE);
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    this->hp_gauge_params_[i]->LoadFromJson(status);
  }
}

void GameSceneVisualParam::ToJson(JsonNode* dest)
{
  JsonNode* status = dest->GainNode(ID_HP_GAUGE);
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    this->hp_gauge_params_[i]->ToJson(status);
  }
}

bool GameSceneVisualParam::EditWithImgui()
{
  ImVec2 winpos = ImVec2(20, 50);
  ImVec2 winsize = ImVec2(400, 400);

  winsize.x = 450;
  winsize.y = MENU_HEIGHT * 3 + BAR_HEIGHT;
  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(ID_HP_GAUGE);
  for (T_UINT8 i = 0; i < HPGauge::PARAM_DATANUM; ++i)
  {
    this->hp_gauge_params_dirty_ |= this->hp_gauge_params_[i]->EditWithImgui();
  }
  ImGui::End();

  return this->hp_gauge_params_dirty_;
}

void GameSceneVisualParam::ResetFlags()
{
  this->hp_gauge_params_dirty_ = false;
}
