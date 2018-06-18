#pragma once

#include <HalEngine.h>

class GameEntity;

class GameEntityCollider : public Collider3D_Sphare
{
public:
  GameEntityCollider(GameEntity* entity);

public:
  inline void SetTag(T_UINT8 tag)
  {
    this->tag_ = tag;
  }
  inline T_UINT8 GetTag() const
  {
    return this->tag_;
  }

private:
  T_UINT8 tag_;

};

