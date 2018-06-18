#pragma once

#include "AllocatableGameEntityManager.h"
#include "Bullet.h"

class BulletManager : public AllocatableGameEntityManager<Bullet>
{
public:
  BulletManager(T_INT16 size)
    : AllocatableGameEntityManager<Bullet>(size)
  {
  }
  ~BulletManager() {}

public:
  void Update() override
  {
    std::vector<Bullet*> delete_bullets = std::vector<Bullet*>();
    this->Loop([&](Bullet* bullet)
    {
      if (bullet->IsAlive())
      {
        bullet->BulletUpdate();
        return;
      }
      delete_bullets.push_back(bullet);
    });
    for (Bullet* bullet : delete_bullets)
    {
      this->Free(bullet);
    }
  }

};