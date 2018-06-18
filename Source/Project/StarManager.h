#pragma once

#include "AllocatableGameEntityManager.h"
#include "Star.h"

class StarManager : public AllocatableGameEntityManager<Star>
{
public:
  enum LevelParam
  {
    COUNT,
    SCALE_MIN,
    SCALE_MAX,
    SPAWN_RADIUS_BEGIN,
    SPAWN_RADIUS_END,
    GRAVITY,
    
    LEVEL_DATANUM
  };

public:
  StarManager();

};