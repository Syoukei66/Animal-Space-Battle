#pragma once

#include <string>
#include "VehicleData.h"

class GachaData
{
public:
  static const GachaData* Create(CSVTokenizer& tokenizer);

private:
  GachaData();

public:
  Model* CreateModel();
  VehicleData* CreateVehicle();

public:
  inline const std::string& GetNameId() const
  {
    return this->name_id_;
  }

private:
  T_UINT8 id_;
  std::string name_id_;
  T_UINT8 rare1_;
  T_UINT8 rare2_;
  T_UINT8 rare3_;
  T_UINT8 rare4_;
  T_UINT8 rare5_;

  FbxResource* model_;

};
