#pragma once

#include <vector>
#include "PlayerEntry.h"

/*
  プレイヤーの参加状況を設定するクラス
  プレイヤーセレクト画面で利用する事ができる
*/

class PlayerEntryList
{
public:
  PlayerEntryList(T_UINT8 entries_count);
  ~PlayerEntryList();

public:
  PlayerEntry* AddEntry(T_UINT8 kind);

  void SetEntry(T_UINT8 id, T_UINT8 kind);
  //指定ＩＤのプレイヤーの参加状態を切り替え
  //（プレイヤー→コンピューター→不参加→プレイヤー→…でループ）
  void IncrementEntryKind(T_UINT8 id);
  //指定ＩＤのプレイヤーを未参加へ
  void ResetEntry(T_UINT8 id);

  void ResetEntries();

  PlayerEntry* AddDebugEntity();

protected:
  PlayerEntry* GetEmptyEntry();

public:
  inline PlayerEntry* GetEntry(T_UINT8 id) const
  {
    return this->entries_[id];
  }

  inline T_UINT8 GetEntriesCount() const
  {
    return this->entries_.size();
  }

private:
  //PlayerEntryDataModel自身が持っているidと配列のidは対応している
  std::vector<PlayerEntry*> entries_;
};
