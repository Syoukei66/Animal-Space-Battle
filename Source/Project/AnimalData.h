#pragma once

#include <string>

#include "BulletEmitterTable.h"
#include "AnimalModelDesignParam.h"

class AnimalData
{
public:
  static const AnimalData* Create(CSVTokenizer& tokenizer);

private:
  AnimalData();

public:
  ~AnimalData();

public:
  Sprite* CreateIcon() const;
  Model* CreateModel() const;

public:
  inline T_UINT8 GetId() const
  {
    return this->id_;
  }
  inline const std::string& GetNameId() const
  {
    return this->name_id_;
  }
  inline const std::string& GetName() const
  {
    return this->name_;
  }
  inline const std::string& GetComment() const
  {
    return this->comment_;
  }
  inline const INativeTexture* GetTexture() const
  {
    return this->icon_texture_->GetContents();
  }
  inline const AnimalModelDesignParam* GetDesignParams() const
  {
    return this->design_param_;
  }

private:
  T_UINT8 id_;
  std::string name_id_;
  std::string name_;
  std::string comment_;

  TextureResource* icon_texture_;
  FbxResource* model_;
  AnimalModelDesignParam* design_param_;

};
