#pragma once

#include "DevelopParam.h"
#include "VehicleModelDesignParam.h"

class AnimalModelDesignParam : public DevelopParam
{
public:
  static AnimalModelDesignParam* CreateWithJson(const char* path);

public:
  AnimalModelDesignParam(const char* path);
  ~AnimalModelDesignParam();

  AnimalModelDesignParam& operator =(const AnimalModelDesignParam& o);

public:
  virtual void LoadFromJson(JsonNode* node) override;
  virtual void ToJson(JsonNode* dest) override;
  virtual bool EditWithImgui() override;
  virtual void ResetFlags() override;

public:
  bool EditWithImgui(T_UINT8 vehicle_id);

public:
  inline const std::string& GetPath() const
  {
    return this->path_;
  }
  inline T_UINT8 GetVehicleDesignParamCount() const
  {
    return this->vehicle_design_params_.size();
  }
  inline VehicleModelDesignParam* GetVehicleDesignParam(T_UINT8 id)
  {
    return this->vehicle_design_params_[id];
  }
  inline const VehicleModelDesignParam* GetVehicleDesignParam(T_UINT8 id) const
  {
    return this->vehicle_design_params_[id];
  }
private:
  std::string path_;
  std::vector<VehicleModelDesignParam*> vehicle_design_params_;

  bool is_dirty_;

};