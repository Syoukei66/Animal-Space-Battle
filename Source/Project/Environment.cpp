#include "stdafx.h"
#include "Environment.h"

Player* Environment::GetNearestPlayer(GameEntity* entity)
{
  return this->player_manager_->GetNearestEntity(entity);
}

Star* Environment::GetNearestStar(GameEntity* entity)
{
  return this->star_manager_->GetNearestEntity(entity);
}

Star* Environment::GetNearestNotHoldedStar(Player* player)
{
  if (!this->star_manager_)
  {
    return nullptr;
  }
  T_FLOAT nearest_distance = Limit::T_FLOAT_MAX;
  Star* nearest_star = nullptr;
  this->star_manager_->Loop([&](Star* p)
  {
    if (p->GetMaster() == player)
    {
      return;
    }
    T_FLOAT distance = (player->GetTransform()->GetWorldPosition() - p->GetTransform()->GetWorldPosition()).Length();
    distance -= p->GetColliderRadius() + player->GetColliderRadius();
    if (distance < nearest_distance)
    {
      nearest_distance = distance;
      nearest_star = p;
    }
  });
  return nearest_star;
}
