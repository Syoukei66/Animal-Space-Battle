#include "stdafx.h"
#include "GachaEffect.h"

static const T_FLOAT JET_START_Z = 0.5f;
static const T_FLOAT JET_MOVE_Z = -10.0f;

GachaEffect::GachaEffect()
{
  this->wall_ = new Model(Asset::Fbx::SPACE_WALL);
  this->wall_->GetTransform()->SetScale(16.0f);
  this->wall_->SetMaterialForTree(*Asset::Material::GACHA_WORLD.Clone());
  this->wall_->GetMaterial()->SetZTestLevel(1);
  this->AddChild(this->wall_);

  this->sphare_effect_ = new Model(Asset::Fbx::STAR);
  this->sphare_effect_->GetTransform()->SetZ(1.5f);
  this->sphare_effect_->GetTransform()->SetScale(4.0f, 10.0f, 4.0f);
  this->sphare_effect_->GetTransform()->RotateY(MathConstants::PI_1_2);
  this->sphare_effect_->GetTransform()->RotateZ(MathConstants::PI_1_2);
  this->sphare_effect_->SetMaterialForTree(*Asset::Material::GACHA_STAR.Clone());
  this->sphare_effect_->GetMaterial()->SetZTestLevel(2);
  this->sphare_effect_->GetMaterial()->TextureProperty("_NoiseTexture") = Asset::Texture::SHADER_NOISE.GetContents();
  this->sphare_effect_->GetMaterial()->TextureProperty("_UvNoiseTexture") = Asset::Texture::SHADER_NOISE_NORMAL.GetContents();
  this->sphare_effect_->GetMaterial()->ColorProperty("_Color") = Color4F::CreateBy4BitFormat(255, 226, 64, 255);
  this->sphare_effect_->GetMaterial()->ColorProperty("_SubColor") = Color4F::CreateBy4BitFormat(255, 142, 0, 255);
  this->AddChild(this->sphare_effect_);

  this->jet_effect_ = new Model(Asset::Fbx::JET);
  this->jet_effect_->GetTransform()->SetZ(JET_START_Z);
  this->jet_effect_->GetTransform()->SetScaleY(5.0f);
  this->jet_effect_->GetTransform()->RotateX(-MathConstants::PI_1_2);
  this->jet_effect_->SetMaterialForTree(*Asset::Material::GACHA_JET.Clone());
  this->jet_effect_->GetMaterial()->SetZTestLevel(3);
  this->jet_effect_->GetMaterial()->TextureProperty("_NoiseTexture") = Asset::Texture::SHADER_NOISE.GetContents();
  this->jet_effect_->GetMaterial()->TextureProperty("_UvNoiseTexture") = Asset::Texture::SHADER_NOISE_NORMAL.GetContents();
  this->AddChild(this->jet_effect_);

  this->GetTransform()->SetScale(5.0f);
}

GachaEffect::~GachaEffect()
{
  delete this->sphare_effect_;
  delete this->jet_effect_;
  delete this->wall_;
}

void GachaEffect::SetLayerIdForAll(T_UINT8 id)
{
  this->wall_->SetLayerIdForTree(id);
  this->jet_effect_->SetLayerIdForTree(id);
  this->sphare_effect_->SetLayerIdForTree(id);
}

void GachaEffect::EffectBegin()
{
  this->gacha_time_count_ = 0;
}

void GachaEffect::Update()
{
  const T_FLOAT time = HalEngine::Time::ElapsedFrameSinceSceneCreate() / 60.0f / 20.0f;
  this->jet_effect_->GetMaterial()->FloatProperty("_Time") = time;
  this->sphare_effect_->GetMaterial()->FloatProperty("_Time") = time;
  this->jet_effect_->GetTransform()->SetZ(JET_START_Z + JET_MOVE_Z * this->gacha_time_count_ / 300.0f);
  this->wall_->GetMaterial()->IntProperty("_GachaTimeCount") = this->gacha_time_count_;
  ++this->gacha_time_count_;
}
