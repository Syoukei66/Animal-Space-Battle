#include "GameDirector.h"
#include "DeveloperInitScene.h"

GameDirector::GameDirector()
  : player_entry_list_(nullptr)
  , player_result_list_(nullptr)
  , game_scene_(nullptr)
  , result_scene_(nullptr)
{}

void GameDirector::GameStart_(Scene* game_scene, Scene* result_scene, PlayerEntryList* player_entry_list)
{
  this->player_entry_list_ = player_entry_list;
  this->game_scene_ = game_scene;
  this->result_scene_ = result_scene;
  this->player_result_list_ = new PlayerResultList(player_entry_list);
  Director::GetInstance()->ChangeScene(game_scene);
}

void GameDirector::GameFinish_()
{
  Director::GetInstance()->ChangeScene(this->result_scene_);
  this->game_scene_ = nullptr;
  if (!this->result_scene_)
  {
    this->Finalize(new DeveloperInitScene());
  }
}

void GameDirector::Finalize_(Scene* init_scene)
{
  delete this->player_result_list_;
  delete this->player_entry_list_;
  this->player_entry_list_ = nullptr;
  this->player_result_list_ = nullptr;
  Director::GetInstance()->ChangeScene(init_scene);
  this->result_scene_ = nullptr;
}
