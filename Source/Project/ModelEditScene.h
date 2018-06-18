#pragma once
#include "PlayerActor.h"

class ModelEditScene : public Scene
{
public:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

public:
  void Update() override;

private:
  void OnChangeDistance();
  void OnChangeParam();

private:
  Camera3D_LookAt* camera_x_;
  Camera3D_LookAt* camera_y_;
  Camera3D_LookAt* camera_z_;
  GameObject3D* actor_camera_anchor_;
  Camera3D_LookAt* camera_rot_;
  GameObject3D* camera_rot_anchor_;
  PlayerActor* actor_;

  Model* collider_;

  char** animal_combobox_elements_;
  T_UINT8 animal_data_count_;
  char** vehicle_combobox_elements_;
  T_UINT8 vehicle_data_count_;
  T_INT32 edit_animal_id_;
  T_INT32 edit_vehicle_id_;

  T_INT32 copy_animal_id_;

  bool drag_;
  T_FLOAT distance_;

};