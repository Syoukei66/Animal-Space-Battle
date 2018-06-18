#include "NumberView.h"
#include "../Engine/Director.h"

#include "Asset.h"

NumberView::NumberView(T_UINT8 digit_count)
  : digit_count_(digit_count)
  , display_value_(0.0f)
  , value_(0.0f)
  , count_value_(0.0f)
  , duration_(1)
{
  this->sprites_ = new AnimatedSprite*[digit_count];
  //”Ô†‚ªá‚¢‡‚©‚ç‚P‚ÌˆÊ‚ğ’S“–
  for (T_UINT8 i = 0; i < digit_count; ++i)
  {
    Material* material = EngineAsset::Material::SPRITE.Clone();
    material->SetMainTexture(Asset::Texture::UI_GAME_NUMBER.GetContents());
    this->sprites_[i] = AnimatedSprite::CreateWithMaterial(*material, 5, 2);
    this->sprites_[i]->GetTiledTextureRegion()->SetXNum(5);
    this->sprites_[i]->GetTiledTextureRegion()->SetYNum(2);
    this->sprites_[i]->GetTiledTextureRegion()->FitToTexture();
    this->sprites_[i]->FitToTexture();
    //this->sprites_[i]->SetAnimateRange(0, 9);
    this->AddChild(this->sprites_[i]);
  }
}

NumberView::~NumberView()
{
  for (T_UINT8 i = 0; i < this->digit_count_; ++i)
  {
    delete this->sprites_[i];
  }
  delete[] this->sprites_;
}

void NumberView::SetAllLayerId(T_UINT8 id)
{
  for (T_UINT8 i = 0; i < this->digit_count_; ++i)
  {
    this->sprites_[i]->SetLayerId(id);
  }
}

void NumberView::ViewInit(T_UINT32 value)
{
  this->value_ = (T_FLOAT)value;
  this->display_value_ = (T_FLOAT)value;
  this->OnUpdateView();
}

void NumberView::Update()
{
  if (this->value_ == this->display_value_)
  {
    return;
  }
  this->display_value_ += this->count_value_;
  if (fabs(this->value_ - this->display_value_) < 1.0f)
  {
    this->display_value_ = this->value_;
  }
  this->OnUpdateView();
}

void NumberView::SetValue(T_UINT32 value)
{
  this->value_ = (T_FLOAT)value;
  this->count_value_ = (this->value_ - this->display_value_) / (T_FLOAT)this->duration_;
}

void NumberView::AnimationFinish()
{
  this->display_value_ = this->value_;
  this->OnUpdateView();
}

void NumberView::OnUpdateView()
{
  T_UINT32 num = (T_UINT32)this->display_value_;
  T_UINT8 digit_index = 0;
  while (num != 0)
  {
    this->sprites_[digit_index]->SetCurrentIndex(num % 10);
    num /= 10;
    digit_index++;
  }
  for (T_UINT8 i = digit_index; i < this->digit_count_; ++i)
  {
    this->sprites_[i]->SetCurrentIndex(0);
  }
}

void NumberView::SetSize(T_FLOAT width, T_FLOAT height)
{
  const T_FLOAT digit_width = width / this->digit_count_;
  const T_FLOAT offset_x = width * 0.5f - digit_width * 0.5f;
  for (T_UINT8 i = 0; i < this->digit_count_; ++i)
  {
    this->sprites_[i]->SetWidth(digit_width);
    this->sprites_[i]->SetHeight(height);
    this->sprites_[i]->GetTransform()->SetX(offset_x - digit_width * i);
  }
}


