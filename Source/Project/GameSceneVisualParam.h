#pragma once

#include <HalEngine.h>
#include "DevelopParam.h"
#include "HPGauge.h"
#include "DesignData.h"

class GameSceneVisualParam : public DevelopParam
{
public:
  static GameSceneVisualParam& GetInstance()
  {
    static GameSceneVisualParam self;
    return self;
  }

protected:
  GameSceneVisualParam();
  GameSceneVisualParam(const GameSceneVisualParam&) = delete;
  ~GameSceneVisualParam();

public:
  virtual void LoadFromJson(JsonNode* node) override;
  virtual void ToJson(JsonNode* dest) override;
  virtual bool EditWithImgui() override;
  virtual void ResetFlags() override;

public:
  inline const DesignData& GetHpGaugeParam(HPGauge::DesignEntity param) const
  {
    return *this->hp_gauge_params_[param];
  }
  inline bool IsHpGaugeParamsDirty() const
  {
    return this->hp_gauge_params_dirty_;
  }

private:
  DesignData* hp_gauge_params_[HPGauge::PARAM_DATANUM];
  bool hp_gauge_params_dirty_;
  DesignData* rank_param_;
  bool rank_param_dirty_;
  DesignData* flag_param_;
  bool flag_param_dirty_;
//  DesignData* 

};
