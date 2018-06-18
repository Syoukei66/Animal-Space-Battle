#pragma once

#include <HalEngine.h>

#include "PlayerEntryList.h"
#include "PlayerResultList.h"

/*
  GameDirectorをシングルトンにした理由
  GameDirectorはゲームのルールに関わる部分であり、
  ゲーム中の殆どのオブジェクトがGameDirectorに依存するため
  グローバルなアクセスが可能になっても問題は少ない
  
  GameSettingをメンバにした理由
  ゲーム内の殆どのオブジェクトが参照するデータの為
  ゲーム中のアクセスはGetterを経由したconstアクセスだけに限定し、
  設定の変更を行う際はInit()を経由し、ゲームを再起動する。

  ゲームの開始もGameDirectorを経由させる事で、
  ゲームとの１対１対応である事を強調した。
*/

class GameDirector
{
public:
  inline static void GameStart(Scene* game_scene, Scene* result_scene, PlayerEntryList* player_entry_list)
  {
    GameDirector::GetInstance()->GameStart_(game_scene, result_scene, player_entry_list);
  }
  inline static void GameFinish()
  {
    GameDirector::GetInstance()->GameFinish_();
  }
  inline static void Finalize(Scene* init_scene)
  {
    GameDirector::GetInstance()->Finalize_(init_scene);
  }
  inline static PlayerEntryList* GetPlayerEntryList()
  {
    return GameDirector::GetInstance()->player_entry_list_;
  }
  inline static PlayerResultList* GetPlayerResultList()
  {
    return GameDirector::GetInstance()->player_result_list_;
  }
  inline static Scene* GetScene()
  {
    return GameDirector::GetInstance()->game_scene_;
  }

private:
  static GameDirector* GetInstance()
  {
    static GameDirector self;
    return &self;
  }
  GameDirector();
  GameDirector(const GameDirector&) {}

public:
  void GameStart_(Scene* game_scene, Scene* result_scene, PlayerEntryList* player_entry_list);
  void GameFinish_();
  void Finalize_(Scene* init_scene);
  
private:
  PlayerEntryList* player_entry_list_;
  PlayerResultList* player_result_list_;
  Scene* game_scene_;
  Scene* result_scene_;
};