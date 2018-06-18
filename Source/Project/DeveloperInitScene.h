#pragma once

#include <HalEngine.h>

#include "PlayerEntry.h"
#include "PlayerEntryList.h"

class BaseGameScene;

class DeveloperInitScene : public Scene
{
public:
  struct PlayerEntryData
  {
    PlayerEntryData(T_UINT8 id)
      : id(id)
      , entry_kind(PlayerEntry::PLAYER_ENTRY_NONE)
      , animal_id(id % 4)
      , vehicle_id(id % 4)
    {}
    int id;
    int entry_kind;
    int animal_id;
    int vehicle_id;
  };

public:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

public:
  void Update() override;

private:
  PlayerEntryList* CreateEntryList();
  void GameStart(BaseGameScene* scene);
  void ResultStart();

private:
  PlayerEntryData* entries_[PlayerEntry::PLAYER_ENTRY_MAX];
  char** animal_combobox_elements_;
  T_UINT8 animal_data_count_;
  char** vehicle_combobox_elements_;
  T_UINT8 vehicle_data_count_;
  T_UINT8 entry_count_;

  T_INT32 result_kind_;

  T_INT32 player_count_;
  T_INT32 computer_count_;
};