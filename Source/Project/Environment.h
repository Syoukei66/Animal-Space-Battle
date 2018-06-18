#pragma once

#include <set>

#include "PlayerManager.h"
#include "StarManager.h"

class Environment
{
public:
  static Environment& GetInstance()
  {
    static Environment self;
    return self;
  }

private:
  Environment() {}
  Environment(const Environment& b) = delete;

public:
  ~Environment() {}

public:
  Player* GetNearestPlayer(GameEntity* entity);
  Star* GetNearestStar(GameEntity* entity);
  Star* GetNearestNotHoldedStar(Player* player);

public:
  inline void SetPlayerManager(PlayerManager* manager)
  {
    this->player_manager_ = manager;
  }
  inline PlayerManager* GetPlayerManager()
  {
    return this->player_manager_;
  }
  inline void SetStarManager(StarManager* manager)
  {
    this->star_manager_ = manager;
  }
  inline StarManager* GetStarManager()
  {
    return this->star_manager_;
  }

private:
  PlayerManager* player_manager_;
  StarManager* star_manager_;

};
