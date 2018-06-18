#pragma once

#include "AnimalData.h"
#include "VehicleData.h"
#include "JetManager.h"

class PlayerActor : public GameObject3D
{
public:
  PlayerActor();
  ~PlayerActor();

public:
  void ChangeAnimalData(const AnimalData* data);
  void ChangeVehicleData(const VehicleData* data);
  void ChangePlayerId(T_UINT8 id);

public:
  void Update() override;

public:
  void ApplyDesignParam();

public:
  inline const AnimalData* GetAnimalData()
  {
    return this->animal_data_;
  }
  inline const VehicleData* GetVehicleData()
  {
    return this->vehicle_data_;
  }
  inline T_FLOAT GetColliderRadius() const
  {
    return this->collider_radius_;
  }
  inline Material* GetModelMaterial()
  {
    return this->body_material_;
  }

private:
  GameObject3D* body_;

  Model* animal_model_;
  const AnimalData* animal_data_;
  const VehicleData* vehicle_data_;
  JetManager* jets_;

  Material* body_material_;

  T_FLOAT collider_radius_;

  T_FLOAT eye_line_length_;
  Model* eye_line_;

  Model* current_vehicle_;
  Model** vehicle_pool_;
  T_UINT8 pooled_vehicle_count_;

};