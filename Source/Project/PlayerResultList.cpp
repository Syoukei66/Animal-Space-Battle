#include "stdafx.h"
#include "PlayerResultList.h"
#include <algorithm>

PlayerResultList::PlayerResultList(const PlayerEntryList* entries)
{
  T_UINT8 entry_count = entries->GetEntriesCount();
  for (T_UINT8 i = 0; i < entry_count; ++i)
  {
    PlayerResult* result = new PlayerResult(entries->GetEntry(i));
    this->results_.push_back(result);
    this->ordered_results_.push_back(result);
  }
}

PlayerResultList::~PlayerResultList()
{
  for (PlayerResult* result : this->results_)
  {
    delete result;
  }
}

void PlayerResultList::Commit()
{
  std::sort(this->ordered_results_.begin(), this->ordered_results_.end(), [] (PlayerResult* a, PlayerResult* b){
    return a->point > b->point;
  });
  for (PlayerResult* result : this->results_)
  {
    result->rank = -1;
  }
  for (T_UINT8 i = 0; i < 4; ++i)
  {
    this->ranked_results_[i].clear();
  }
  T_UINT8 rank = 0;
  T_INT32 prev_point = -1;
  for (PlayerResult* result : this->ordered_results_)
  {
    if (prev_point == -1)
    {
      prev_point = result->point;
    }
    else if (prev_point != result->point)
    {
      ++rank;
      if (rank >= 4)
      {
        break;
      }
      prev_point = result->point;
    }
    result->rank = rank;
    this->ranked_results_[rank].push_back(result);
  }
}

void PlayerResultList::DebugCommit(T_UINT8 kind)
{
  T_UINT8 result_count = 4;
  if (kind == RESULT_LINER)
  {
    for (T_UINT8 i = 0; i < result_count; ++i)
    {
      this->ranked_results_[i].push_back(this->results_[i]);
    }
  }
  else if (kind == RESULT_DUPLICATION)
  {
    T_UINT8 dbl = Util::GetRandom(1, std::max(1, result_count - 2));
    for (T_UINT8 i = 0; i < dbl; ++i)
    {
      this->ranked_results_[i].push_back(this->results_[i]);
    }
    for (T_UINT8 i = dbl; i < result_count; ++i)
    {
      this->ranked_results_[dbl].push_back(this->results_[i]);
    }
  }
  else if (kind == RESULT_TOP_DUPLICATION)
  {
    T_UINT8 dbl = Util::GetRandom(1, std::max(1, result_count - 2));
    for (T_UINT8 i = 0; i < dbl; ++i)
    {
      this->ranked_results_[0].push_back(this->results_[i]);
    }
    for (T_UINT8 i = dbl; i < result_count - 1; ++i)
    {
      this->ranked_results_[1 + i].push_back(this->results_[i]);
    }
  }
  else if (kind == RESULT_ALL_ONE)
  {
    for (T_UINT8 i = 0; i < result_count; ++i)
    {
      this->ranked_results_[0].push_back(this->results_[i]);
    }
  }
}
