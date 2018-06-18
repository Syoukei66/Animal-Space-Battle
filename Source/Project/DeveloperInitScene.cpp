#include "DeveloperInitScene.h"
#include "GameDirector.h"
#include "DesignerGameScene.h"
#include "LevelGameScene.h"
#include "GameScene.h"
#include "BaseGameScene.h"

#include "AnimalTable.h"
#include "VehicleTable.h"

#include "TitleScene.h"
#include "BulletTestGameScene.h"
#include "ModelEditScene.h"
#include "DebugResultScene.h"

static const char* RESULT_KIND_HEADS[PlayerResultList::RESULT_NUMMAX] = 
{
  u8"順位=PlayerId",
  u8"2位以降がランダムに重複",
  u8"1位が重複",
  u8"みんな１位",
};

void DeveloperInitScene::OnLoad(IResourceLoadReserver* resource)
{
}

void DeveloperInitScene::OnSetup()
{
  this->player_count_ = 1;
  this->computer_count_ = 0;
  for (T_UINT8 i = 0; i < PlayerEntry::PLAYER_ENTRY_MAX; ++i)
  {
    this->entries_[i] = new PlayerEntryData(i);
  }

  this->animal_data_count_ = AnimalTable::GetInstance().GetDataCount();
  this->animal_combobox_elements_ = new char*[this->animal_data_count_]();
  for (T_UINT8 i = 0; i < this->animal_data_count_; ++i)
  {
    const AnimalData* data = AnimalTable::GetInstance().GetData(i);
    T_UINT8 name_length = data->GetNameId().length() + 1;
    this->animal_combobox_elements_[i] = new char[name_length];
    strcpy_s(this->animal_combobox_elements_[i], name_length, data->GetNameId().c_str());
  }

  this->vehicle_data_count_ = VehicleTable::GetInstance().GetDataCount();
  this->vehicle_combobox_elements_ = new char*[this->vehicle_data_count_]();
  for (T_UINT8 i = 0; i < this->vehicle_data_count_; ++i)
  {
    const VehicleData* data = VehicleTable::GetInstance().GetData(i);
    T_UINT8 name_length = data->GetNameId().length() + 1;
    this->vehicle_combobox_elements_[i] = new char[name_length];
    strcpy_s(this->vehicle_combobox_elements_[i], name_length, data->GetNameId().c_str());
  }

}

void DeveloperInitScene::OnUnload()
{
  for (T_UINT8 i = 0; i < this->vehicle_data_count_; ++i)
  {
    delete[] this->vehicle_combobox_elements_[i];
  }
  delete[] this->vehicle_combobox_elements_;

  for (T_UINT8 i = 0; i < this->animal_data_count_; ++i)
  {
    delete[] this->animal_combobox_elements_[i];
  }
  delete[] this->animal_combobox_elements_;

  for (T_UINT8 i = 0; i < PlayerEntry::PLAYER_ENTRY_MAX; ++i)
  {
    delete this->entries_[i];
  }
}

void DeveloperInitScene::OnShow(ISceneShowListener* listener)
{
}

void DeveloperInitScene::OnHide(ISceneHideListener* listener)
{
}

void DeveloperInitScene::Update()
{
  ImGui::SetNextWindowPos(ImVec2(800, 300), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(240, 300), ImGuiSetCond_Once);
  ImGui::Begin(u8"ゲーム設定");
  bool entry_updated = false;
  if (ImGui::SliderInt(u8"Player数", &this->player_count_, 0, 4))
  {
    entry_updated = true;
  }
  if (ImGui::SliderInt(u8"CP数", &this->computer_count_, 0, PlayerEntry::PLAYER_ENTRY_MAX))
  {
    entry_updated = true;
  }

  this->entry_count_ = this->player_count_ + this->computer_count_;
  if (entry_updated && this->entry_count_ > PlayerEntry::PLAYER_ENTRY_MAX)
  {
    this->computer_count_ = PlayerEntry::PLAYER_ENTRY_MAX - this->player_count_;
    this->entry_count_ = PlayerEntry::PLAYER_ENTRY_MAX;
  }
  if (ImGui::Button(u8"BulletEmitterTestScene", ImVec2(200, 20)))
  {
    this->GameStart(new BulletTestGameScene());
  }
  if (ImGui::Button(u8"デザイナーモードで開始", ImVec2(200, 20)))
  {
    this->GameStart(new DesignerGameScene());
  }
  if (ImGui::Button(u8"レベルデザインモードで開始", ImVec2(200, 20)))
  {
    this->GameStart(new LevelGameScene());
  }
  if (ImGui::TreeNode(u8"3Dモデル設定"))
  {
    if (ImGui::Button(u8"モデル位置調整", ImVec2(200, 20)))
    {
      Director::GetInstance()->ChangeScene(new ModelEditScene());
    }
    ImGui::TreePop();
  }
  if (ImGui::TreeNode(u8"ゲーム開始"))
  {
    if (ImGui::Button(u8"ゲーム開始", ImVec2(200, 20)))
    {
      Director::GetInstance()->ChangeScene(new TitleScene());
    }
    if (ImGui::Button(u8"いきなりリザルト", ImVec2(200, 20)))
    {
      this->ResultStart();
    }
    ImGui::TreePop();
  }
  ImGui::End();

  ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiSetCond_Once);
  ImGui::Begin(u8"参加プレイヤー設定");
  for (T_UINT8 i = 0; i < this->entry_count_; ++i)
  {
    if (i < this->player_count_)
    {
      this->entries_[i]->entry_kind = PlayerEntry::PLAYER_ENTRY_PLAYER;
    }
    else
    {
      this->entries_[i]->entry_kind = PlayerEntry::PLAYER_ENTRY_COMPUTER;
    }
    std::string name = std::string();
    std::string id = "EntryID = ";
    id += std::to_string(i);
    if (this->entries_[i]->entry_kind == PlayerEntry::PLAYER_ENTRY_PLAYER)
    {
      name += "(";
      name += std::to_string(i + 1);
      name += "P)";
    }
    else
    {
      name += "(CP";
      name += std::to_string(i + 1 - this->player_count_);
      name += ")";
    }
    id += " ";
    id += name;
    ImGui::Text(id.c_str());

    ImGui::PushID(i);
    std::string animal = "Animal";
    ImGui::Combo(animal.c_str(), &this->entries_[i]->animal_id, this->animal_combobox_elements_, this->animal_data_count_);

    std::string vehicle = "Vehicle";
    ImGui::Combo(vehicle.c_str(), &this->entries_[i]->vehicle_id, this->vehicle_combobox_elements_, this->vehicle_data_count_);
    ImGui::PopID();
  }
  ImGui::Text(u8"いきなりリザルトでの順位の決まり方");
  ImGui::Combo("", &this->result_kind_, RESULT_KIND_HEADS, PlayerResultList::RESULT_NUMMAX);
  ImGui::End();
}

PlayerEntryList* DeveloperInitScene::CreateEntryList()
{
  //プレイヤーの参加状況を決める
  //計9人まで対応(意味無し)
  PlayerEntryList* entries = new PlayerEntryList(this->entry_count_);

  for (T_UINT8 i = 0; i < this->entry_count_; ++i)
  {
    PlayerEntry* entry = entries->AddEntry(this->entries_[i]->entry_kind);
    entry->animal_data = AnimalTable::GetInstance().GetData(this->entries_[i]->animal_id);
    entry->vehicle_data = VehicleTable::GetInstance().GetData(this->entries_[i]->vehicle_id);
  }

  return entries;
}

void DeveloperInitScene::GameStart(BaseGameScene* scene)
{
  //実行するシーン、キャラクターの参加状況、ゲームの設定をGameDirectorに渡し、ゲーム開始
  GameDirector::GameStart(scene, new ResultScene(), this->CreateEntryList());
}

void DeveloperInitScene::ResultStart()
{
  GameDirector::GameStart(nullptr, new DebugResultScene(), this->CreateEntryList());
  GameDirector::GetPlayerResultList()->DebugCommit(this->result_kind_);
  GameDirector::GameFinish();
}
