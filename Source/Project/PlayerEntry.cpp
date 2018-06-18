#include "PlayerEntry.h"

Color4F PlayerEntry::PLAYER_ENTRY_COLORS[PLAYER_ENTRY_MAX] = 
{
  Color4F::CreateBy4BitFormat(255,   0,   0, 255),
  Color4F::CreateBy4BitFormat(  0,   0, 255, 255),
  Color4F::CreateBy4BitFormat(  0, 255,   0, 255),
  Color4F::CreateBy4BitFormat(255, 255,   0, 255),

  Color4F::CreateBy4BitFormat(255,   0, 255, 255),
  Color4F::CreateBy4BitFormat(  0, 255, 255, 255),
  Color4F::CreateBy4BitFormat(255,  80, 128, 255),
  Color4F::CreateBy4BitFormat(200, 200, 200, 255),
  Color4F::CreateBy4BitFormat(180,  50,   0, 255),
};