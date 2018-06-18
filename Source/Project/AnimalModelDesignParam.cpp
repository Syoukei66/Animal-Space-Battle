#include "stdafx.h"
#include "AnimalModelDesignParam.h"
#include "VehicleTable.h"

static const char* ATTR_VEHICLE_DESIGN_LIST = "VehicleDesign";

AnimalModelDesignParam* AnimalModelDesignParam::CreateWithJson(const char* path)
{
  AnimalModelDesignParam* ret = new AnimalModelDesignParam(path);
  JsonResource* json = JsonResource::DynamicLoad(path);
  JsonNode* node = json->GetContents()->GetRoot();
  ret->LoadFromJson(node);
  return ret;
}

AnimalModelDesignParam::AnimalModelDesignParam(const char* path)
  : path_(path)
{
}

AnimalModelDesignParam::~AnimalModelDesignParam()
{
  for (VehicleModelDesignParam* param : this->vehicle_design_params_)
  {
    delete param;
  }
}

AnimalModelDesignParam& AnimalModelDesignParam::operator=(const AnimalModelDesignParam & o)
{
  for (VehicleModelDesignParam* param : this->vehicle_design_params_)
  {
    for (VehicleModelDesignParam* o_param : o.vehicle_design_params_)
    {
      if (param->GetName() != o_param->GetName())
      {
        continue;
      }
      *param = *o_param;
      break;
    }
  }
  this->is_dirty_ = true;
  return *this;
}

void AnimalModelDesignParam::LoadFromJson(JsonNode* node)
{
  this->vehicle_design_params_.clear();
  JsonList<JsonNode>* vehicle_designs = node->GainList<JsonNode>(ATTR_VEHICLE_DESIGN_LIST);
  T_UINT8 vehicle_count = VehicleTable::GetInstance().GetDataCount();
  for (T_UINT8 i = 0; i < vehicle_count; ++i)
  {
    JsonNode* vehicle_design = vehicle_designs->Gain(i);
    this->vehicle_design_params_.push_back(VehicleModelDesignParam::CreateWithJson(vehicle_design));
  }
}

void AnimalModelDesignParam::ToJson(JsonNode* dest)
{
  JsonList<JsonNode>* vehicle_design_list = dest->PutList<JsonNode>(ATTR_VEHICLE_DESIGN_LIST);
  for (VehicleModelDesignParam* param : this->vehicle_design_params_)
  {
    param->ToJson(vehicle_design_list->Add());
  }
}

bool AnimalModelDesignParam::EditWithImgui()
{
  if (ImGui::TreeNode(ATTR_VEHICLE_DESIGN_LIST))
  {
    T_UINT8 id = 0;
    for (VehicleModelDesignParam* param : this->vehicle_design_params_)
    {
      ImGui::PushID(id);
      ImGui::Text(VehicleTable::GetInstance().GetData(id)->GetNameId().c_str());
      this->is_dirty_ |= param->EditWithImgui();
      ImGui::PopID();
      ++id;
    }
    ImGui::TreePop();
  }
  if (ImGui::Button(u8"•Û‘¶"))
  {
    JsonNode* root = JsonNode::CreateRoot();
    this->ToJson(root);
    NativeMethod::IO().TextFile_Write(this->path_.c_str(), root->ToString());
    root->Release();
  }
  return this->is_dirty_;
}

void AnimalModelDesignParam::ResetFlags()
{
  for (VehicleModelDesignParam* param : this->vehicle_design_params_)
  {
    param->ResetFlags();
  }
  this->is_dirty_ = false;
}

bool AnimalModelDesignParam::EditWithImgui(T_UINT8 vehicle_id)
{
  bool ret = this->vehicle_design_params_[vehicle_id]->EditWithImgui();
  if (ImGui::Button(u8"•Û‘¶"))
  {
    JsonNode* root = JsonNode::CreateRoot();
    this->ToJson(root);
    NativeMethod::IO().TextFile_Write(this->path_.c_str(), root->ToString());
    root->Release();
  }
  return ret;
}
