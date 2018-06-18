#pragma once

#include <HalEngine.h>

class Field : public GameObject3D
{
public:
  enum LevelParam
  {
    FIELD_RADIUS,
    SPACE_RADIUS,

    LEVEL_DATANUM
  };

public:
  Field();
  ~Field();

public:
  void Update() override;

private:
  Model* skydome_;
  Material* space_material_;
  Model* skygrid_;
  Material* grid_material_;
  T_INT32 time_;

};