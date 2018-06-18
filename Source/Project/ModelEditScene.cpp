#include "ModelEditScene.h"
#include "AnimalTable.h"
#include "VehicleTable.h"
#include "DeveloperUtil.h"

void ModelEditScene::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE);
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE_NORMAL);

  resource->ReserveLoad(Asset::Fbx::STAR);
  resource->ReserveLoad(Asset::Fbx::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Fbx::JET);

  resource->ReserveLoad(Asset::Shader::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Shader::JET);
  resource->ReserveLoad(Asset::Shader::COLLIDER);
}

void ModelEditScene::OnSetup()
{
  this->actor_camera_anchor_ = new GameObject3D();
  this->AddChild(this->actor_camera_anchor_);

  this->camera_rot_anchor_ = new GameObject3D();
  this->AddChild(this->camera_rot_anchor_);

  this->actor_ = new PlayerActor();

  this->actor_->GetModelMaterial()->Vec3fProperty("_LightDirection") = TVec3f(0.0f, 0.0f, 1.0f);

  this->actor_->ChangeAnimalData(AnimalTable::GetInstance().GetData(0));
  this->actor_->ChangeVehicleData(VehicleTable::GetInstance().GetData(0));
  this->actor_camera_anchor_->AddChild(this->actor_);

  this->collider_ = new Model(Asset::Fbx::STAR);
  this->collider_->SetShaderForTree(Asset::Shader::COLLIDER);
  this->AddChild(this->collider_);

  const T_FLOAT width = Director::GetInstance()->GetScreenWidth() * 0.5f;
  const T_FLOAT height = Director::GetInstance()->GetScreenHeight() * 0.5f;

  this->camera_x_ = new Camera3D_LookAt();
  this->camera_x_->SetViewportWidth(width);
  this->camera_x_->SetViewportHeight(height);
  this->camera_x_->SetViewportX(width);
  this->camera_x_->SetViewportY(height);
  this->camera_x_->SetPlayer(this->actor_camera_anchor_);
  this->camera_x_->GetTransform()->RotateY(-MathConstants::PI_1_2);
  this->AddCamera(this->camera_x_);

  this->camera_y_ = new Camera3D_LookAt();
  this->camera_y_->SetViewportWidth(width);
  this->camera_y_->SetViewportHeight(height);
  this->camera_y_->SetPlayer(this->actor_camera_anchor_);
  this->camera_y_->GetTransform()->RotateX(MathConstants::PI_1_2);
  this->AddCamera(this->camera_y_);

  this->camera_z_ = new Camera3D_LookAt();
  this->camera_z_->SetViewportWidth(width);
  this->camera_z_->SetViewportHeight(height);
  this->camera_z_->SetViewportY(height);
  this->camera_z_->SetPlayer(this->actor_camera_anchor_);
  this->camera_z_->GetTransform()->RotateY(-MathConstants::PI);
  this->AddCamera(this->camera_z_);

  this->camera_rot_ = new Camera3D_LookAt();
  this->camera_rot_->SetViewportWidth(width);
  this->camera_rot_->SetViewportHeight(height);
  this->camera_rot_->SetViewportX(width);
  this->camera_rot_->SetPlayer(this->camera_rot_anchor_);
  this->camera_rot_->GetTransform()->RotateY(-MathConstants::PI);
  this->AddCamera(this->camera_rot_);

  this->animal_data_count_ = AnimalTable::GetInstance().GetDataCount();
  this->animal_combobox_elements_ = new char*[this->animal_data_count_];
  for (T_UINT8 i = 0; i < this->animal_data_count_; ++i)
  {
    const AnimalData* data = AnimalTable::GetInstance().GetData(i);
    T_UINT8 name_length = data->GetNameId().length() + 1;
    this->animal_combobox_elements_[i] = new char[name_length];
    strcpy_s(this->animal_combobox_elements_[i], name_length, data->GetNameId().c_str());
  }

  this->vehicle_data_count_ = VehicleTable::GetInstance().GetDataCount();
  this->vehicle_combobox_elements_ = new char*[this->vehicle_data_count_];
  for (T_UINT8 i = 0; i < this->vehicle_data_count_; ++i)
  {
    const VehicleData* data = VehicleTable::GetInstance().GetData(i);
    T_UINT8 name_length = data->GetNameId().length() + 1;
    this->vehicle_combobox_elements_[i] = new char[name_length];
    strcpy_s(this->vehicle_combobox_elements_[i], name_length, data->GetNameId().c_str());
  }

  this->edit_animal_id_ = 0;
  this->edit_vehicle_id_ = 0;
  this->drag_ = false;

  this->distance_ = 10.0f;
  this->OnChangeDistance();

  this->OnChangeParam();
}

void ModelEditScene::OnUnload()
{
  for (T_UINT8 i = 0; i < this->vehicle_data_count_; ++i)
  {
    delete[] this->vehicle_combobox_elements_[i];
  }
  delete[] this->vehicle_combobox_elements_;

  for (T_UINT8 i = 0; i < this->animal_data_count_; ++i)
  {
    delete[] this->animal_combobox_elements_[i];
  }
  delete[] this->animal_combobox_elements_;

  delete this->camera_rot_;
  delete this->camera_z_;
  delete this->camera_y_;
  delete this->camera_x_;
  delete this->collider_;
  delete this->actor_;
  delete this->camera_rot_anchor_;
  delete this->actor_camera_anchor_;
}

void ModelEditScene::OnShow(ISceneShowListener* listener)
{
}

void ModelEditScene::OnHide(ISceneHideListener* listener)
{
}

void ModelEditScene::Update()
{
  DeveloperUtil::ShowDebugWindow(DeveloperUtil::DEBUG_RETURN_INIT_SCENE);

  bool edited = false;

  ImGui::SetNextWindowPos(ImVec2(50, 200), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200, 80), ImGuiSetCond_Once);

  ImGui::Begin(u8"編集対象モデル");
  if (ImGui::Combo("Animal", &this->edit_animal_id_, this->animal_combobox_elements_, this->animal_data_count_))
  {
    this->actor_->ChangeAnimalData(AnimalTable::GetInstance().GetData(this->edit_animal_id_));
    this->OnChangeParam();
  }
  if (ImGui::Combo("Vehicle", &this->edit_vehicle_id_, this->vehicle_combobox_elements_, this->vehicle_data_count_))
  {
    this->actor_->ChangeVehicleData(VehicleTable::GetInstance().GetData(this->edit_vehicle_id_));
    this->OnChangeParam();
  }
  ImGui::End();

  ImGui::SetNextWindowPos(ImVec2(50, 300), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiSetCond_Once);

  ImGui::Begin(u8"Actor設定");
  ImGui::Text(u8"Animal = %s, Vehicle = %s", AnimalTable::GetInstance().GetData(this->edit_animal_id_)->GetNameId().c_str(), VehicleTable::GetInstance().GetData(this->edit_vehicle_id_)->GetNameId().c_str());
  const AnimalData* data = this->actor_->GetAnimalData();
  if (data)
  {
    AnimalModelDesignParam* param = const_cast<AnimalModelDesignParam*>(data->GetDesignParams());
    param->ResetFlags();
    if (param->EditWithImgui(this->edit_vehicle_id_))
    {
      edited = true;
      this->OnChangeParam();
    }
  }
  ImGui::Text(u8"他の動物のデータからコピー");
  ImGui::Combo("Animal", &this->copy_animal_id_, this->animal_combobox_elements_, this->animal_data_count_);
  if (ImGui::Button(u8"コピーする", ImVec2(100, 30)))
  {
    AnimalModelDesignParam* dest = const_cast<AnimalModelDesignParam*>(data->GetDesignParams());
    *dest->GetVehicleDesignParam(this->edit_vehicle_id_) = *AnimalTable::GetInstance().GetData(this->copy_animal_id_)->GetDesignParams()->GetVehicleDesignParam(this->edit_vehicle_id_);
    this->OnChangeParam();
  }
  ImGui::End();

  if (!edited)
  {
    if (HalEngine::Input(0)->GetButtonDown(GameInput::DEBUG_MOUSE_CLICK))
    {
      this->drag_ = true;
    }
    if (HalEngine::Input(0)->GetButtonUp(GameInput::DEBUG_MOUSE_CLICK))
    {
      this->drag_ = false;
    }
    if (this->drag_ && HalEngine::Input(0)->GetButton(GameInput::LOCKON))
    {
      static const T_FLOAT ROTATION_SPEED = 100.0f;
      const T_FLOAT mouse_x_axis = HalEngine::Input(0)->GetAxis(GameInput::DEBUG_SCREEN_X);
      const T_FLOAT mouse_y_axis = HalEngine::Input(0)->GetAxis(GameInput::DEBUG_SCREEN_Y);
      if (fabs(mouse_x_axis) > 0.0f)
      {
        this->actor_camera_anchor_->GetTransform()->SetEularY(
          this->actor_camera_anchor_->GetTransform()->GetEularY() - mouse_x_axis * 5.0f
        );
      }
      if (fabs(mouse_y_axis) > 0.0f)
      {
        this->distance_ += mouse_y_axis;
        this->OnChangeDistance();
      }
    }
  }
}

void ModelEditScene::OnChangeDistance()
{
  this->camera_x_->GetTransform()->SetX(this->distance_);
  this->camera_y_->GetTransform()->SetY(this->distance_);
  this->camera_z_->GetTransform()->SetZ(this->distance_);
  this->camera_rot_->GetTransform()->SetZ(this->distance_);
}

void ModelEditScene::OnChangeParam()
{
  this->actor_->ApplyDesignParam();
  this->collider_->GetTransform()->SetScale(this->actor_->GetColliderRadius() * 2.0f);
}
