#pragma once

#include <list>
#include <HalEngine.h>

#include "GameEntityCollider.h"

class GameEntity : public GameObject3D
{
public:
  GameEntity();
  virtual ~GameEntity();

public:
  void PostUpdate() override;

public:
  bool HitCheck(GameEntity* other);

public:
  inline void SetIgnoreSpaceWall(bool ignore)
  {
    this->ignore_space_wall_ = ignore;
  }
  inline bool IsIgnoreSpaceWall() const
  {
    return this->ignore_space_wall_;
  }
  inline GameEntityCollider* GetCollider()
  {
    return this->collider_;
  }
  inline const GameEntityCollider* GetCollider() const
  {
    return this->collider_;
  }
  inline T_FLOAT GetColliderRadius() const
  {
    return this->collider_->GetRadius();
  }
private:
  GameEntityCollider* collider_;
  bool ignore_space_wall_;
};