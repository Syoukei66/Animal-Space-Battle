#include "stdafx.h"
#include "DeveloperUtil.h"
#include "ViewportSetting.h"
#include "PlayerManager.h"
#include "DeveloperInitScene.h"
#include "GameDirector.h"

static bool show_computer_camera = false;

void DeveloperUtil::ShowDebugWindow(T_INT32 flag)
{
  ImVec2 winpos = ImVec2(800, 300);
  ImVec2 winsize = ImVec2(200, 150);

  ImGui::SetNextWindowPos(winpos, ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(winsize, ImGuiSetCond_Once);
  ImGui::Begin(u8"デバッグメニュー");
  if (flag & DEBUG_CP_CAMERA)
  {
    if (ImGui::Checkbox(u8"CPカメラ表示", &show_computer_camera))
    {
      const T_UINT8 count = ViewportSetting::GetInstance().GetViewportCount();
      for (T_UINT8 i = 0; i < count; ++i)
      {
        if (PlayerManager::GetInstance().GetPlayer(i)->IsHuman())
        {
          continue;
        }
        ViewportSetting::GetInstance().SetEnabled(i, show_computer_camera);
      }
    }
  }
  if (flag & DEBUG_ALL_PLAYER_HP_MAX)
  {
    if (ImGui::Button(u8"HP全回復", ImVec2(105, 20)))
    {
      T_UINT8 count = PlayerManager::GetInstance().GetPlayerCount();
      for (T_UINT8 i = 0; i < count; ++i)
      {
        PlayerManager::GetInstance().GetPlayer(i)->HpMax();
      }
    }
  }
  if (flag & DEBUG_RETURN_INIT_SCENE)
  {
    if (ImGui::Button(u8"開発メニューに戻る", ImVec2(125, 20)))
    {
      GameDirector::Finalize(new DeveloperInitScene());
    }
  }
  if (flag & DEBUG_GAME_FINISH)
  {
    if (ImGui::Button(u8"ゲーム終了", ImVec2(105, 20)))
    {
      GameDirector::GameFinish();
    }
  }
  ImGui::Text("App avg %.3f", 1000.0f / ImGui::GetIO().Framerate);
  ImGui::Text("ms/frame (%.1f FPS)", ImGui::GetIO().Framerate);
  ImGui::End();
}
