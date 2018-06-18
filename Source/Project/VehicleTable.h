#pragma once

#include "VehicleData.h"
#include "DataTable.h"

class VehicleTable : public DataTable<VehicleData>
{
public:
  static VehicleTable& GetInstance()
  {
    static VehicleTable self;
    return self;
  }

private:
  VehicleTable()
    : DataTable<VehicleData>("Asset/data/vehicle/vehicleTable.csv")
  {}
  VehicleTable(const VehicleTable& b) = delete;

public:
  ~VehicleTable() {}

};