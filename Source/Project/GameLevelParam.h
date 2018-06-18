#pragma once

#include <HalEngine.h>
#include "DevelopParam.h"
#include "StarManager.h"
#include "PlayerStatus.h"
#include "Field.h"

class GameLevelParam : public DevelopParam
{
public:
  static GameLevelParam& GetInstance()
  {
    static GameLevelParam self;
    return self;
  }

protected:
  GameLevelParam();
  GameLevelParam(const GameLevelParam&) {}
  ~GameLevelParam();

public:
  void LoadFromJson(JsonNode* node) override;
  void ToJson(JsonNode* dest) override;

  bool EditWithImgui() override;
  void ResetFlags() override;

public:
  inline void SetStarLevel(Field::LevelParam level, T_FLOAT value)
  {
    this->field_levels_[level] = value;
  }
  inline T_FLOAT GetFieldLevel(Field::LevelParam level) const
  {
    return this->field_levels_[level];
  }
  inline bool IsFieldLevelsDirty() const
  {
    return this->field_levels_dirty_;
  }

  inline void SetStarLevel(StarManager::LevelParam level, T_FLOAT value)
  {
    this->star_levels_[level] = value;
  }
  inline T_FLOAT GetStarLevel(StarManager::LevelParam level) const
  {
    return this->star_levels_[level];
  }
  inline bool IsStarLevelsDirty() const
  {
    return this->star_levels_dirty_;
  }

  inline void SetStarLevel(PlayerStatus::LevelParam level, T_FLOAT value)
  {
    this->status_levels_[level] = value;
  }
  inline T_FLOAT GetPlayerStatusLevel(PlayerStatus::LevelParam level) const
  {
    return this->status_levels_[level];
  }
  inline bool IsStatusLevelsDirty() const
  {
    return this->status_levels_dirty_;
  }

private:
  T_FLOAT field_levels_[Field::LEVEL_DATANUM];
  bool field_levels_dirty_;
  T_FLOAT star_levels_[StarManager::LEVEL_DATANUM];
  bool star_levels_dirty_;
  T_FLOAT status_levels_[PlayerStatus::LEVEL_DATANUM];
  bool status_levels_dirty_;

};