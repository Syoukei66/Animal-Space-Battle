#include "stdafx.h"
#include "JetManager.h"
#include "PlayerActor.h"

static Model* CreateJetModel()
{
  Model* ret = new Model(Asset::Fbx::JET);
  ret->SetMaterialForTree(*Asset::Material::JET.Clone());
  ret->GetMaterial()->SetZTestLevel(1);
  ret->GetMaterial()->TextureProperty("_NoiseTexture") = Asset::Texture::SHADER_NOISE.GetContents();
  ret->GetMaterial()->TextureProperty("_UvNoiseTexture") = Asset::Texture::SHADER_NOISE_NORMAL.GetContents();
  return ret;
}

JetManager::JetManager()
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->jet_main_[i] = CreateJetModel();
  }
}

JetManager::~JetManager()
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    delete this->jet_main_[i];
  }
}

void JetManager::AttachToVehicle(GameObject3D* vehicle)
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    vehicle->AddChild(this->jet_main_[i]);
  }
}

void JetManager::DetachFromVehicle()
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->jet_main_[i]->RemoveSelf();
  }
}

void JetManager::Update()
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->jet_main_[i]->GetMaterial()->FloatProperty("_Time") = HalEngine::Time::ElapsedFrameSinceSceneCreate() * 0.0008333f;
  }
}

void JetManager::SetAllLayerId(T_UINT8 layer_id)
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->jet_main_[i]->SetLayerIdForTree(layer_id);
  }
}

void JetManager::ApplyDesignParams(const VehicleModelDesignParam* design)
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    design->GetMainJetDesignParam()->ChangeTransform(this->jet_main_[i]->GetTransform());
  }
  this->jet_main_[1]->GetTransform()->MoveX(this->jet_main_[1]->GetTransform()->GetX() * -2.0f);
}

void JetManager::SetAccel(const TVec3f& accel)
{
}
