#include "Field.h"
#include "GameLevelParam.h"

Field::Field()
{
  const GameLevelParam& level = GameLevelParam::GetInstance();

  this->skydome_ = new Model(Asset::Fbx::SPACE_WALL);
  this->skydome_->GetTransform()->SetScale(level.GetFieldLevel(SPACE_RADIUS));
  this->space_material_ = Asset::Material::SPACE_WALL.Clone();
  this->skydome_->SetMaterialForTree(*this->space_material_);
  this->AddChild(this->skydome_);

  this->skygrid_ = new Model(Asset::Fbx::SPACE_WALL);
  this->skygrid_->GetTransform()->SetScale(level.GetFieldLevel(FIELD_RADIUS));
  this->grid_material_ = Asset::Material::SPACE_GRID.Clone();
  this->skygrid_->SetMaterialForTree(*this->grid_material_);
  this->AddChild(this->skygrid_);

  this->grid_material_->FloatProperty("_GridRadius") = level.GetFieldLevel(FIELD_RADIUS);

  this->GetTransform()->RotateX(MathConstants::PI_1_2);
  this->time_ = 0;
}

Field::~Field()
{
  delete this->skydome_;
  delete this->skygrid_;
}

void Field::Update()
{
  this->time_++;
  this->grid_material_->FloatProperty("_Time") = this->time_;
  if (GameLevelParam::GetInstance().IsFieldLevelsDirty())
  {
    const GameLevelParam& level = GameLevelParam::GetInstance();
    this->skydome_->GetTransform()->SetScale(level.GetFieldLevel(SPACE_RADIUS));
    this->skygrid_->GetTransform()->SetScale(level.GetFieldLevel(FIELD_RADIUS));
    this->grid_material_->FloatProperty("_GridRadius") = level.GetFieldLevel(FIELD_RADIUS);
  }
}
