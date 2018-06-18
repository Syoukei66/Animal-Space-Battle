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
    RESULT_DUPLICATION, //2�ʈȍ~�d������
    RESULT_TOP_DUPLICATION,  //1�ʂ��d��
    RESULT_ALL_ONE, //�݂��1��

    RESULT_NUMMAX,
  };

public:
  PlayerResultList(const PlayerEntryList* entries);
  ~PlayerResultList();

public:
  void Commit();

  //�f�o�b�O�p
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

  //���ꏇ�ʂ̃L���������邩������Ȃ��̂�
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