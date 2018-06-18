#pragma once

#include "DevelopParam.h"

class ModelDesignParam : public DevelopParam
{
public:
  static ModelDesignParam* CreateWithJson(JsonNode* node);
  
public:
  ModelDesignParam& operator=(const ModelDesignParam& o);

public:
  virtual void LoadFromJson(JsonNode* node) override;
  virtual void ToJson(JsonNode* dest) override;
  virtual bool EditWithImgui() override;
  virtual void ResetFlags() override;

public:
  void ChangeTransform(Transform3D* transform) const;

private:
  T_FLOAT position_[3];
  T_FLOAT scale_[3];
  T_FLOAT eular_angles_[3];

};