#include "stdafx.h"
#include "PlayerActor.h"
#include "VehicleTable.h"
#include "PlayerEntry.h"
#include "GameLayer.h"

PlayerActor::PlayerActor()
  : animal_model_()
  , animal_data_()
  , vehicle_data_()
  , current_vehicle_()
{
  this->body_ = new GameObject3D();
  this->AddChild(this->body_);

  this->jets_ = new JetManager();

  this->body_material_ = EngineAsset::Material::LAMBERT.Clone();

  this->pooled_vehicle_count_ = VehicleTable::GetInstance().GetDataCount();
  this->vehicle_pool_ = new Model*[this->pooled_vehicle_count_]();
  for (T_UINT8 i = 0; i < this->pooled_vehicle_count_; ++i)
  {
    this->vehicle_pool_[i] = VehicleTable::GetInstance().GetData(i)->CreateModel();
    this->vehicle_pool_[i]->SetVisible(false);
    this->vehicle_pool_[i]->GetTransform()->SetScale(0.5f);
    this->vehicle_pool_[i]->SetMaterialForTree(*this->body_material_);
    this->body_->AddChild(this->vehicle_pool_[i]);
  }

  this->eye_line_length_ = 300.0f;
  this->eye_line_ = new Model(Asset::Fbx::PLAYER_EYE_LINE);
  Material* mat = Asset::Material::PLAYER_EYE_LINE.Clone();
  mat->SetZTestLevel(1);
  this->eye_line_->SetMaterialForTree(*mat);
  this->eye_line_->GetTransform()->SetScale(0.2f, this->eye_line_length_, 0.2f);
  this->eye_line_->GetTransform()->RotateX(MathConstants::PI_1_2);
  this->eye_line_->GetTransform()->SetZ(this->eye_line_length_);
  this->AddChild(this->eye_line_);
}

PlayerActor::~PlayerActor()
{
  delete this->eye_line_;
  for (T_UINT8 i = 0; i < this->pooled_vehicle_count_; ++i)
  {
    delete this->vehicle_pool_[i];
  }
  delete[] this->vehicle_pool_;
  delete this->animal_model_;
  delete this->jets_;
  delete this->body_;
}

void PlayerActor::ChangeAnimalData(const AnimalData* data)
{
  if (this->animal_model_)
  {
    this->animal_model_->RemoveSelf();
    delete this->animal_model_;
  }
  this->animal_data_ = data;
  this->animal_model_ = data->CreateModel();
  this->animal_model_->SetMaterialForTree(*this->body_material_);
  this->body_->AddChild(this->animal_model_);
  this->ApplyDesignParam();
}

void PlayerActor::ChangeVehicleData(const VehicleData* data)
{
  if (this->current_vehicle_)
  {
    this->current_vehicle_->SetVisible(false);
    this->jets_->DetachFromVehicle();
  }
  this->vehicle_data_ = data;
  this->current_vehicle_ = data ? this->vehicle_pool_[data->GetId()] : nullptr;
  if (this->current_vehicle_)
  {
    this->current_vehicle_->SetVisible(true);
    this->jets_->AttachToVehicle(this->current_vehicle_);
  }
  this->eye_line_->SetVisible(this->current_vehicle_);
  this->ApplyDesignParam();
}

void PlayerActor::ChangePlayerId(T_UINT8 id)
{
  this->eye_line_->GetMaterial()->ColorProperty("_PlayerColor") = PlayerEntry::PLAYER_ENTRY_COLORS[id];

  T_UINT8 layer_id = id + GameLayer::LAYER_PLAYER_0_BODY;
  this->eye_line_->SetLayerIdForTree(layer_id);
  this->animal_model_->SetLayerIdForTree(layer_id);
  for (T_UINT8 i = 0; i < this->pooled_vehicle_count_; ++i)
  {
    this->vehicle_pool_[i]->SetLayerId(layer_id);
  }
  this->jets_->SetAllLayerId(layer_id);
}

void PlayerActor::Update()
{
  this->jets_->Update();
}

void PlayerActor::ApplyDesignParam()
{
  for (T_UINT8 i = 0; i < this->pooled_vehicle_count_; ++i)
  {
    const VehicleModelDesignParam* param = this->animal_data_->GetDesignParams()->GetVehicleDesignParam(i);
    param->GetModelDesignParam()->ChangeTransform(this->vehicle_pool_[i]->GetTransform());
  }
  if (this->vehicle_data_)
  {
    const VehicleModelDesignParam* param = this->animal_data_->GetDesignParams()->GetVehicleDesignParam(this->vehicle_data_->GetId());
    this->collider_radius_ = param->GetColliderRadius();
    this->jets_->ApplyDesignParams(param);
    this->body_->GetTransform()->SetPosition(param->GetOffset(0), param->GetOffset(1), param->GetOffset(2));
  }
}
