#pragma once

#include "DevelopParam.h"
#include "ModelDesignParam.h"

class VehicleModelDesignParam : public DevelopParam
{
public:
  static VehicleModelDesignParam* CreateWithJson(JsonNode* node);

private:
  VehicleModelDesignParam();

public:
  ~VehicleModelDesignParam();

public:
  VehicleModelDesignParam& operator=(const VehicleModelDesignParam& o);

public:
  virtual void LoadFromJson(JsonNode* node) override;
  virtual void ToJson(JsonNode* dest) override;
  virtual bool EditWithImgui() override;
  virtual void ResetFlags() override;

public:
  inline const std::string& GetName() const
  {
    return this->name_;
  }
  inline T_FLOAT GetOffset(T_UINT8 index) const
  {
    return this->offset_[index];
  }
  inline T_FLOAT GetColliderRadius() const
  {
    return this->collider_radius_;
  }
  inline const ModelDesignParam* GetModelDesignParam() const
  {
    return this->model_transform_;
  }
  inline const ModelDesignParam* GetMainJetDesignParam() const
  {
    return this->main_jet_transform_;
  }
private:
  std::string name_;
  T_FLOAT offset_[3];
  T_FLOAT collider_radius_;
  ModelDesignParam* model_transform_;
 
  ModelDesignParam* main_jet_transform_;

};