#pragma once

#include <vector>
#include "PlayerResult.h"
#include "PlayerEntryList.h"

class PlayerResultList
{
public:
  enum DebugResultKind
  {
    RESULT_LINER,
    RESULT_DUPLICATION, //2位以降重複あり
    RESULT_TOP_DUPLICATION,  //1位が重複
    RESULT_ALL_ONE, //みんな1位

    RESULT_NUMMAX,
  };

public:
  PlayerResultList(const PlayerEntryList* entries);
  ~PlayerResultList();

public:
  void Commit();

  //デバッグ用
  void DebugCommit(T_UINT8 kind);

public:
  inline PlayerResult* GetResultById(T_UINT8 id)
  {
    return this->results_[id];
  }

  inline const PlayerResult* GetResultById(T_UINT8 id) const
  {
    return this->results_[id];
  }

  inline T_UINT8 GetPlayerCount() const
  {
    return this->results_.size();
  }

  //同一順位のキャラがいるかもしれないので
  inline const std::vector<PlayerResult*>& GetResultByRank(T_UINT8 rank) const
  {
    return this->ranked_results_[rank];
  }

  inline T_UINT8 GetRankCount() const
  {
    return 4;
  }

private:
  std::vector<PlayerResult*> results_;
  
  std::vector<PlayerResult*> ordered_results_;

  std::vector<PlayerResult*> ranked_results_[4];
};