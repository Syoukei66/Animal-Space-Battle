#include "stdafx.h"
#include "ModelDesignParam.h"

static const char* ATTR_POSITION = "Position";
static const char* ATTR_SCALE = "Scale";
static const char* ATTR_EULAR_ANGLES = "EularAngles";

ModelDesignParam* ModelDesignParam::CreateWithJson(JsonNode* node)
{
  ModelDesignParam* ret = new ModelDesignParam();
  ret->LoadFromJson(node);
  return ret;
}

ModelDesignParam & ModelDesignParam::operator=(const ModelDesignParam& o)
{
  for (T_UINT8 i = 0; i < 3; ++i)
  {
    this->position_[i] = o.position_[i];
    this->scale_[i] = o.scale_[i];
    this->eular_angles_[i] = o.eular_angles_[i];
  }
  return *this;
}

void ModelDesignParam::LoadFromJson(JsonNode* node)
{
  JsonList<JsonValue>* positions = node->GainList<JsonValue>(ATTR_POSITION);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    this->position_[i] = *positions->Gain(i);
  }
  JsonList<JsonValue>* scales = node->GainList<JsonValue>(ATTR_SCALE);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    JsonValue* scale = nullptr;
    if (scales->Gain(i, &scale))
    {
      *scale = 1.0f;
    }
    this->scale_[i] = *scale;
  }
  JsonList<JsonValue>* eular_angles = node->GainList<JsonValue>(ATTR_EULAR_ANGLES);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    this->eular_angles_[i] = *eular_angles->Gain(i);
  }
}

void ModelDesignParam::ToJson(JsonNode* dest)
{
  JsonList<JsonValue>* positions = dest->PutList<JsonValue>(ATTR_POSITION);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    *positions->Add() = this->position_[i];
  }
  JsonList<JsonValue>* scale = dest->PutList<JsonValue>(ATTR_SCALE);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    *scale->Add() = this->scale_[i];
  }
  JsonList<JsonValue>* eular_angles = dest->PutList<JsonValue>(ATTR_EULAR_ANGLES);
  for (T_INT8 i = 0; i < 3; ++i)
  {
    *eular_angles->Add() = this->eular_angles_[i];
  }
}

bool ModelDesignParam::EditWithImgui()
{
  bool edited = false;
  edited |= ImGui::SliderFloat3(ATTR_POSITION, this->position_, -30.0f, 30.0f, "%.2f");
  edited |= ImGui::SliderFloat3(ATTR_SCALE, this->scale_, 0.0f, 30.0f, "%.2f");
  edited |= ImGui::SliderFloat3(ATTR_EULAR_ANGLES, this->eular_angles_, -180.0f, 180.0f, "%.2f");
  return edited;
}

void ModelDesignParam::ResetFlags()
{
}

void ModelDesignParam::ChangeTransform(Transform3D* transform) const
{
  transform->SetPosition(this->position_[0], this->position_[1], this->position_[2]);
  transform->SetScale(this->scale_[0], this->scale_[1], this->scale_[2]);
  transform->SetEularAngles(this->eular_angles_[0], this->eular_angles_[1], this->eular_angles_[2]);
}
