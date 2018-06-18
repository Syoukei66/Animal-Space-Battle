#pragma once

namespace DeveloperUtil
{

enum MenuFlag
{
  DEBUG_RETURN_INIT_SCENE  = 0x0001,
  DEBUG_CP_CAMERA          = 0x0002,
  DEBUG_ALL_PLAYER_HP_MAX  = 0x0004,
  DEBUG_GAME_FINISH        = 0x0008,
};

void ShowDebugWindow(T_INT32 flag);

}