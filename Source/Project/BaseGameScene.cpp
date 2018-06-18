#include "BaseGameScene.h"

BaseGameScene::BaseGameScene()
{
  this->controller_ = new GameController(this);
}

BaseGameScene::~BaseGameScene()
{
  delete this->controller_;
}

void BaseGameScene::OnLoad(IResourceLoadReserver* resource)
{
  this->controller_->OnLoad(resource);
}

void BaseGameScene::OnSetup()
{
  this->controller_->OnSetup();
}

void BaseGameScene::OnUnload()
{
  this->controller_->OnUnload();
}

void BaseGameScene::OnShow(ISceneShowListener* listener)
{
  this->controller_->OnShow(listener);
}

void BaseGameScene::OnHide(ISceneHideListener* listener)
{
  this->controller_->OnHide(listener);
}

void BaseGameScene::Update()
{
  this->controller_->Update();
}

void BaseGameScene::PostUpdate()
{
  this->controller_->PostUpdate();
}
