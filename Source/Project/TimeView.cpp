#include "stdafx.h"
#include "TimeView.h"

static AnimatedSprite* CreateAnimatedSprite()
{
  Material* material = EngineAsset::Material::SPRITE.Clone();
  material->SetMainTexture(Asset::Texture::UI_GAME_NUMBER.GetContents());
  AnimatedSprite* ret = AnimatedSprite::CreateWithMaterial(*material, 5, 2);
  ret->GetTiledTextureRegion()->SetXNum(5);
  ret->GetTiledTextureRegion()->SetYNum(2);
  ret->GetTiledTextureRegion()->FitToTexture();
  ret->FitToTexture();
  return ret;
}

TimeView::TimeView()
  : size_(0.0f, 0.0f)
  , value_(0.0f)
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->minutes_[i] = CreateAnimatedSprite();
    this->second_[i] = CreateAnimatedSprite();
    this->millisecond_[i] = CreateAnimatedSprite();

    this->AddChild(this->minutes_[i]);
    this->AddChild(this->second_[i]);
    this->AddChild(this->millisecond_[i]);
  }

  this->minutes_dot_ = AnimatedSprite::CreateWithResource(Asset::Texture::UI_GAME_NUMBER_DOT, 2, 1);
  this->minutes_dot_->GetTiledTextureRegion()->SetXNum(2);
  this->minutes_dot_->GetTiledTextureRegion()->SetYNum(1);
  this->minutes_dot_->GetTiledTextureRegion()->FitToTexture();
  this->minutes_dot_->FitToTexture();
  this->AddChild(this->minutes_dot_);

  this->second_dot_ = AnimatedSprite::CreateWithResource(Asset::Texture::UI_GAME_NUMBER_DOT, 2, 1);
  this->second_dot_->GetTiledTextureRegion()->SetXNum(2);
  this->second_dot_->GetTiledTextureRegion()->SetYNum(1);
  this->second_dot_->GetTiledTextureRegion()->FitToTexture();
  this->second_dot_->SetCurrentIndex(1);
  this->second_dot_->FitToTexture();
  this->AddChild(this->second_dot_);
}

TimeView::~TimeView()
{
  delete this->second_dot_;
  delete this->minutes_dot_;
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    delete this->minutes_[i];
    delete this->second_[i];
    delete this->millisecond_[i];
  }
}

void TimeView::SetAllLayerId(T_UINT8 id)
{
  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->minutes_[i]->SetLayerId(id);
    this->second_[i]->SetLayerId(id);
    this->millisecond_[i]->SetLayerId(id);
  }
  this->minutes_dot_->SetLayerId(id);
  this->second_dot_->SetLayerId(id);
}

void TimeView::ViewInit(T_UINT32 millisecond)
{
  this->value_ = (T_FLOAT)millisecond;
  this->OnUpdateView();
}

void TimeView::SetValule(T_UINT32 millisecond)
{
  this->value_ = (T_FLOAT)millisecond;
}

void TimeView::Update()
{
  if (this->value_ == 0.0f)
  {
    return;
  }
  this->value_ = std::max(0.0f, this->value_ - HalEngine::Time::DeltaTime() * 1000.0f);
  this->OnUpdateView();
}

void TimeView::OnUpdateView()
{
  T_UINT32 num = (T_UINT32)this->value_;
  T_UINT8 digit_index = 0;
  T_UINT8 millisecond = num % 1000;
  T_UINT8 second = (num / 1000) % 60;
  T_UINT8 minutes = (num / 60000) % 100;

  this->millisecond_[0]->SetCurrentIndex(millisecond / 10);
  this->millisecond_[1]->SetCurrentIndex(millisecond % 10);

  this->second_[0]->SetCurrentIndex(second / 10);
  this->second_[1]->SetCurrentIndex(second % 10);

  this->minutes_[0]->SetCurrentIndex(minutes / 10);
  this->minutes_[1]->SetCurrentIndex(minutes % 10);
}

void TimeView::SetSize(T_FLOAT width, T_FLOAT height)
{
  const T_FLOAT digit_width = width / 7.0f;
  const T_FLOAT offset_x = width * 0.5f - digit_width * 0.5f;

  this->millisecond_[0]->GetTransform()->SetX(offset_x - digit_width);
  this->millisecond_[1]->GetTransform()->SetX(offset_x);

  this->second_dot_->GetTransform()->SetX(offset_x - digit_width * 1.75f);

  this->second_[0]->GetTransform()->SetX(offset_x - digit_width * 3.5f);
  this->second_[1]->GetTransform()->SetX(offset_x - digit_width * 2.5f);

  this->minutes_dot_->GetTransform()->SetX(offset_x - digit_width * 4.25f);

  this->minutes_[0]->GetTransform()->SetX(offset_x - digit_width * 6.0f);
  this->minutes_[1]->GetTransform()->SetX(offset_x - digit_width * 5.0f);

  for (T_UINT8 i = 0; i < 2; ++i)
  {
    this->millisecond_[i]->SetSize(digit_width, height);
    this->second_[i]->SetSize(digit_width, height);
    this->minutes_[i]->SetSize(digit_width, height);
  }
  this->minutes_dot_->SetSize(digit_width * 0.75f, height);
  this->second_dot_->SetSize(digit_width * 0.75f, height);
}
