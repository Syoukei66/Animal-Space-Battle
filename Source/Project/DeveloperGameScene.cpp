#include "DeveloperGameScene.h"
#include "DeveloperInitScene.h"
#include "ViewportSetting.h"
#include "DeveloperUtil.h"

void DeveloperGameScene::OnSetup()
{
  BaseGameScene::OnSetup();
  this->editor_ = this->CreateEditor();
  this->show_computer_camera_ = false;
}

void DeveloperGameScene::OnUnload()
{
  delete this->editor_;
  BaseGameScene::OnUnload();
}

void DeveloperGameScene::PreUpdate()
{
  this->editor_->Update();
  BaseGameScene::PreUpdate();
}

void DeveloperGameScene::Update()
{
  BaseGameScene::Update();
  using namespace DeveloperUtil;
  ShowDebugWindow(DEBUG_RETURN_INIT_SCENE | DEBUG_CP_CAMERA | DEBUG_RETURN_INIT_SCENE);

}
