#include "GameLevelParam.h"

struct LevelParamInfo
{
  const char* name;
  const char* comment;
  T_FLOAT min;
  T_FLOAT max;
  const char* format;
};

static const char* ID_FIELD = "Field";
static const LevelParamInfo FIELD_PARAMS[Field::LEVEL_DATANUM] =
{
  { "FieldRadius", u8"移動可能領域半径",
  1.0f, 500.0f, "%.0f" },

  { "SpaceRadius", u8"宇宙半径",
  1.0f, 500.0f, "%.0f" },
};

static const char* ID_STAR = "Star";
static const LevelParamInfo STAR_PARAMS[StarManager::LEVEL_DATANUM] =
{
  { "Count", u8"星の数",
  1.0f, 100.0f, "%.0f" },

  { "ScaleMin", u8"星の最小サイズ",
  1.0f, 100.0f, "%.0f" },

  { "ScaleMax", u8"星の最大のサイズ",
  1.0f, 100.0f, "%.0f" },

  { "SpawnRadiusBegin", u8"星が出現する最小半径エリア",
  1.0f, 500.0f, "%.0f" },

  { "SpawnRadiusEnd", u8"星が出現する最大半径エリア",
  1.0f, 500.0f, "%.0f" },

  { "Gravity", u8"星の重力の大きさ",
  0.00001f, 0.0005f, "%.5f" },
};

static const char* ID_STATUS = "Status";
static const LevelParamInfo STATUS_PARAMS[PlayerStatus::LEVEL_DATANUM] =
{
  { "AccelWeight", u8"加速度の重み",
  0.00001f, 0.0005f, "%.5f" },

  { "SpeedWeight", u8"速度の重み",
  0.0001f, 0.01f, "%.4f" },

  { "RotSpeedWeight", u8"角速度の重み",
  0.00001f, 0.001f, "%.5f" },

  { "PowerWeight", u8"パワーの重み",
  0.1f, 10.0f, "%.1f" },
};

static const T_UINT8 MENU_HEIGHT = 40;
static const T_UINT8 BAR_HEIGHT = 40;

GameLevelParam::GameLevelParam()
  : field_levels_()
  , field_levels_dirty_(true)
  , star_levels_()
  , star_levels_dirty_(true)
  , status_levels_()
  , status_levels_dirty_(true)
{
  for (T_UINT8 i = 0; i < Field::LEVEL_DATANUM; ++i)
  {
    this->field_levels_[i] = FIELD_PARAMS[i].min;
  }
  for (T_UINT8 i = 0; i < StarManager::LEVEL_DATANUM; ++i)
  {
    this->star_levels_[i] = STAR_PARAMS[i].min;
  }
  for (T_UINT8 i = 0; i < PlayerStatus::LEVEL_DATANUM; ++i)
  {
    this->status_levels_[i] = STATUS_PARAMS[i].min;
  }
}

GameLevelParam::~GameLevelParam()
{
}

void GameLevelParam::LoadFromJson(JsonNode* node)
{
  JsonNode* field = node->GainNode(ID_FIELD);
  for (T_UINT8 i = 0; i < Field::LEVEL_DATANUM; ++i)
  {
    this->field_levels_[i] = field->GainValue(FIELD_PARAMS[i].name)->FloatValue(FIELD_PARAMS[i].min);
  }

  JsonNode* star = node->GainNode(ID_STAR);
  for (T_UINT8 i = 0; i < StarManager::LEVEL_DATANUM; ++i)
  {
    this->star_levels_[i] = star->GainValue(STAR_PARAMS[i].name)->FloatValue(STAR_PARAMS[i].min);
  }

  JsonNode* status = node->GainNode(ID_STATUS);
  for (T_UINT8 i = 0; i < PlayerStatus::LEVEL_DATANUM; ++i)
  {
    this->status_levels_[i] = status->GainValue(STATUS_PARAMS[i].name)->FloatValue(STATUS_PARAMS[i].min);
  }
}

bool GameLevelParam::EditWithImgui()
{
  ImVec2 winpos = ImVec2(20, 50);
  ImVec2 winsize = ImVec2(400, 400);

  winsize.x = 300;
  winsize.y = Field::LEVEL_DATANUM * MENU_HEIGHT + BAR_HEIGHT;
  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(ID_FIELD);
  for (T_UINT8 i = 0; i < Field::LEVEL_DATANUM; ++i)
  {
    const LevelParamInfo& info = FIELD_PARAMS[i];
    ImGui::Text(" *%s", info.comment);
    if (ImGui::SliderFloat(info.name, &this->field_levels_[i], info.min, info.max, info.format))
    {
      this->field_levels_[i] = floor(this->field_levels_[i] / info.min) * info.min;
      this->field_levels_dirty_ = true;
    }
  }
  ImGui::End();

  winpos.y += winsize.y;
  winsize.x = 380;
  winsize.y = (StarManager::LEVEL_DATANUM + 0.5f) * MENU_HEIGHT + BAR_HEIGHT;
  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(ID_STAR);
  for (T_UINT8 i = 0; i < StarManager::LEVEL_DATANUM; ++i)
  {
    const LevelParamInfo& info = STAR_PARAMS[i];
    ImGui::Text(" *%s", info.comment);
    if (ImGui::SliderFloat(info.name, &this->star_levels_[i], info.min, info.max, info.format))
    {
      this->star_levels_[i] = floor(this->star_levels_[i] / info.min) * info.min;
    }
  }
  if (ImGui::Button(u8"適用", ImVec2(100, 20)))
  {
    this->star_levels_dirty_ = true;
  }
  ImGui::End();

  winpos.y += winsize.y;
  winsize.x = 350;
  winsize.y = PlayerStatus::LEVEL_DATANUM * MENU_HEIGHT + BAR_HEIGHT;
  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(ID_STATUS);
  for (T_UINT8 i = 0; i < PlayerStatus::LEVEL_DATANUM; ++i)
  {
    const LevelParamInfo& info = STATUS_PARAMS[i];
    ImGui::Text(" *%s", info.comment);
    if (ImGui::SliderFloat(info.name, &this->status_levels_[i], info.min, info.max, info.format))
    {
      this->status_levels_[i] = floor(this->status_levels_[i] / info.min) * info.min;
      this->status_levels_dirty_ = true;
    }
  }
  ImGui::End();

  return this->field_levels_dirty_ || this->star_levels_dirty_ || this->status_levels_dirty_;
}

void GameLevelParam::ToJson(JsonNode* dest)
{
  JsonNode* field = dest->GainNode(ID_FIELD);
  for (T_UINT8 i = 0; i < Field::LEVEL_DATANUM; ++i)
  {
    *field->GainValue(FIELD_PARAMS[i].name) = this->field_levels_[i];
  }

  JsonNode* star = dest->GainNode(ID_STAR);
  for (T_UINT8 i = 0; i < StarManager::LEVEL_DATANUM; ++i)
  {
    *star->GainValue(STAR_PARAMS[i].name) = this->star_levels_[i];
  }

  JsonNode* status = dest->GainNode(ID_STATUS);
  for (T_UINT8 i = 0; i < PlayerStatus::LEVEL_DATANUM; ++i)
  {
    *status->GainValue(STATUS_PARAMS[i].name) = this->status_levels_[i];
  }
}

void GameLevelParam::ResetFlags()
{
  this->field_levels_dirty_ = false;
  this->star_levels_dirty_ = false;
  this->status_levels_dirty_ = false;
}
