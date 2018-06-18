#include "stdafx.h"
#include "VehicleData.h"
#include "BulletEmitterTable.h"
#include "DeveloperSettings.h"

const VehicleData* VehicleData::Create(CSVTokenizer& tokenizer)
{
  VehicleData* ret = new VehicleData();
  ret->id_ = tokenizer.NextToken().ToInt32();
  ret->name_id_ = tokenizer.NextToken().ToString();
  ret->rare_ = tokenizer.NextToken().ToInt32();
  ret->name_ = tokenizer.NextToken().ToString();
  ret->comment_ = tokenizer.NextToken().ToString();
  ret->accel_ = tokenizer.NextToken().ToInt32();
  ret->brake_ = tokenizer.NextToken().ToInt32();
  ret->speed_ = tokenizer.NextToken().ToInt32();
  ret->rot_speed_ = tokenizer.NextToken().ToInt32();
  ret->bullet_emitter_data_normal_ = BulletEmitterTable::GetInstance().GetDataByNameId(tokenizer.NextToken().ToString());
  ret->bullet_emitter_data_power_ = BulletEmitterTable::GetInstance().GetDataByNameId(tokenizer.NextToken().ToString());

  std::string data_path = "Asset/data/vehicle/";
  data_path.append(ret->name_id_);
  data_path.append("/");

  std::string icon_path = data_path;
  icon_path.append("icon.png");
  ret->icon_texture_ = TextureResource::DynamicLoad(icon_path.c_str());

  std::string model_path = data_path;
  model_path.append("model.fbx");
  if (DeveloperSettings::GetInstance()->IsModelLoad())
  {
    ret->model_ = FbxResource::DynamicLoad(model_path.c_str());
  }
  else
  {
    ret->model_ = &Asset::Fbx::STAR;
  }
  return ret;
}

VehicleData::VehicleData()
{
}

VehicleData::~VehicleData()
{
  if (DeveloperSettings::GetInstance()->IsModelLoad())
  {
    this->icon_texture_->Release();
  }
}

Sprite* VehicleData::CreateIcon() const
{
  return Sprite::CreateWithResource(*this->icon_texture_);
}

Model* VehicleData::CreateModel() const
{
  return new Model(*this->model_);
}
