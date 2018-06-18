#include "stdafx.h"
#include "AnimalData.h"
#include "DeveloperSettings.h"

const AnimalData* AnimalData::Create(CSVTokenizer& tokenizer)
{
  AnimalData* ret = new AnimalData();
  ret->id_ = tokenizer.NextToken().ToInt32();
  ret->name_id_ = tokenizer.NextToken().ToString();
  ret->name_ = tokenizer.NextToken().ToString();
  ret->comment_ = tokenizer.NextToken().ToString();

  std::string data_path = "Asset/data/animal/";
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
  std::string design_path = data_path;
  design_path.append("Design.json");
  ret->design_param_ = AnimalModelDesignParam::CreateWithJson(design_path.c_str());
  //ret->design_param_ = AnimalModelDesignParam::CreateWithJson("Asset/data/animal/Design.json");
  return ret;
}

AnimalData::AnimalData()
{
}

AnimalData::~AnimalData()
{
  this->icon_texture_->Release();
  if (DeveloperSettings::GetInstance()->IsModelLoad())
  {
    this->model_->Release();
  }
  delete this->design_param_;
}

Sprite* AnimalData::CreateIcon() const
{
  return Sprite::CreateWithResource(*this->icon_texture_);
}

Model* AnimalData::CreateModel() const
{
  return new Model(*this->model_);
}