#pragma once

#include <string>

#include "BulletEmitterData.h"
#include "BaseBulletEmitter.h"

class VehicleData
{
public:
  static const VehicleData* Create(CSVTokenizer& tokenizer);

private:
  VehicleData();

public:
  ~VehicleData();

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
  inline T_UINT16 GetAccel() const
  {
    return this->accel_;
  }
  inline T_UINT16 GetBrake() const
  {
    return this->brake_;
  }
  inline T_UINT16 GetSpeed() const
  {
    return this->speed_;
  }
  inline T_UINT16 GetRotSpeed() const
  {
    return this->rot_speed_;
  }
  inline const BulletEmitterData* GetBulletEmitterData_Normal() const
  {
    return this->bullet_emitter_data_normal_;
  }
  inline const BulletEmitterData* GetBulletEmitterData_Power() const
  {
    return this->bullet_emitter_data_power_;
  }
  inline const INativeTexture* GetIconTexture() const
  {
    return this->icon_texture_->GetContents();
  }
private:
  T_UINT8 id_;
  std::string name_id_;
  T_UINT8 rare_;
  std::string name_;
  std::string comment_;
  T_UINT16 accel_;
  T_UINT16 brake_;
  T_UINT16 speed_;
  T_UINT16 rot_speed_;
  const BulletEmitterData* bullet_emitter_data_normal_;
  const BulletEmitterData* bullet_emitter_data_power_;

  TextureResource* icon_texture_;
  FbxResource* model_;

};

