#pragma once

#include "AnimalData.h"
#include "VehicleData.h"

class PlayerEntry
{
public:
  enum PlayerEntryKind
  {
    PLAYER_ENTRY_NONE,
    PLAYER_ENTRY_PLAYER,
    PLAYER_ENTRY_COMPUTER,

    PLAYER_ENTRY_DATANUM,
    PLAYER_ENTRY_DEBUG,
  };

public:
  enum { PLAYER_ENTRY_MAX = 16 };
  static Color4F PLAYER_ENTRY_COLORS[PLAYER_ENTRY_MAX];

public:
  PlayerEntry(T_UINT8 id)
    : id(id)
    , entry_kind(PLAYER_ENTRY_NONE)
    , animal_data(nullptr)
    , vehicle_data(nullptr)
    , handicap(0)
  {}

public:
  const T_UINT8 id;
  T_UINT8 entry_kind;
  const AnimalData* animal_data;
  const VehicleData* vehicle_data;
  T_UINT8 handicap;
};