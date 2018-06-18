#include "GameEntityCollider.h"
#include "GameEntity.h"

GameEntityCollider::GameEntityCollider(GameEntity* entity)
  : Collider3D_Sphare(entity)
  , tag_(0)
{}
