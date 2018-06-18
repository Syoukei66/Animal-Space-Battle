#include "stdafx.h"
#include "VehicleModelDesignParam.h"

static const char* ATTR_OFFSET = "Offset";
static const char* ATTR_COLLIDER_RADIUS = "ColliderRadius";
static const char* ATTR_TRANSFORM = "Transform";
static const char* ATTR_MAIN_JET = "MainJet";

VehicleModelDesignParam* VehicleModelDesignParam::CreateWithJson(JsonNode* node)
{
  VehicleModelDesignParam* ret = new VehicleModelDesignParam();
  ret->LoadFromJson(node);
  return ret;
}

VehicleModelDesignParam::VehicleModelDesignParam()
  : model_transform_(nullptr)
  , main_jet_transform_(nullptr)
{
}

VehicleModelDesignParam::~VehicleModelDesignParam()
{
  delete this->model_transform_;
  delete this->main_jet_transform_;
}

VehicleModelDesignParam& VehicleModelDesignParam::operator=(const VehicleModelDesignParam& o)
{
  for (T_UINT8 i = 0; i < 3; ++i)
  {
    this->offset_[i] = o.offset_[i];
  }
  this->collider_radius_ = o.collider_radius_;
  *this->model_transform_ = *o.model_transform_;
  *this->main_jet_transform_ = *o.main_jet_transform_;
  return *this;
}

void VehicleModelDesignParam::LoadFromJson(JsonNode* node)
{
  JsonList<JsonValue>* offset = node->GainList<JsonValue>(ATTR_OFFSET);
  this->offset_[0] = *offset->Gain(0);
  this->offset_[1] = *offset->Gain(1);
  this->offset_[2] = *offset->Gain(2);
  JsonValue* collider_radius = nullptr;
  if (node->GainValue(ATTR_COLLIDER_RADIUS, &collider_radius))
  {
    *collider_radius = 1.0f;
  }
  this->collider_radius_ = *collider_radius;
  this->model_transform_ = ModelDesignParam::CreateWithJson(node->GainNode(ATTR_TRANSFORM));
  this->main_jet_transform_ = ModelDesignParam::CreateWithJson(node->GainNode(ATTR_MAIN_JET));
}

void VehicleModelDesignParam::ToJson(JsonNode* dest)
{
  JsonList<JsonValue>* offset = dest->PutList<JsonValue>(ATTR_OFFSET);
  *offset->Add() = this->offset_[0];
  *offset->Add() = this->offset_[1];
  *offset->Add() = this->offset_[2];
  *dest->PutValue(ATTR_COLLIDER_RADIUS) = this->collider_radius_;
  this->model_transform_->ToJson(dest->PutNode(ATTR_TRANSFORM));
  this->main_jet_transform_->ToJson(dest->PutNode(ATTR_MAIN_JET));
}

bool VehicleModelDesignParam::EditWithImgui()
{
  bool edited = false;
  ImGui::Text(u8"オフセット座標");
  edited |= ImGui::SliderFloat3(ATTR_OFFSET, this->offset_, -5.0f, 5.0f, "%.1f");
  ImGui::Text(u8"当たり判定の大きさ");
  edited |= ImGui::SliderFloat(ATTR_COLLIDER_RADIUS, &this->collider_radius_, 0.0f, 10.0f, "%.1f");

  ImGui::Text(u8"乗り物のトランスフォーム");
  ImGui::PushID(0);
  edited |= this->model_transform_->EditWithImgui();
  ImGui::PopID();

  ImGui::Text(u8"メインジェットのトランスフォーム");
  ImGui::PushID(1);
  edited |= this->main_jet_transform_->EditWithImgui();
  ImGui::PopID();
  return edited;
}

void VehicleModelDesignParam::ResetFlags()
{
  this->model_transform_->ResetFlags();
  this->main_jet_transform_->ResetFlags();
}