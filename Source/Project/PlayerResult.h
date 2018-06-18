#pragma once

#include "PlayerEntry.h"

class PlayerResult
{
public:
  PlayerResult(const PlayerEntry* entry)
    : entry(entry)
    , rank(-1)
    , point(0)
  {}

public:
  const PlayerEntry* const entry;
  T_INT8 rank;
  T_INT32 point;

};