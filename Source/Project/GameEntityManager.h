#pragma once

#include <map>
#include <list>
#include <deque>
#include <HalEngine.h>
#include "GameEntity.h"

class IGameEntityManager
{
public:
  virtual void Update() {}
  virtual void AttachToEntity(GameObject3D* entity) = 0;
  virtual void DetachFromEntity() = 0;
};

template<class T>
class GameEntityManager : public IGameEntityManager
{
public:
  virtual void Loop(std::function<void(T*)> func) = 0;
  virtual void LoopIncludingPool(std::function<void(T*)> func) = 0;
  virtual T* Select(std::function<bool(T*)> condition) = 0;
  virtual void SelectAll(std::deque<T*>* dest, std::function<bool(T*)> condition) = 0;

public:
  void AttachToEntity(GameObject3D* entity) override
  {
    this->LoopIncludingPool([&](T* p) {
      entity->AddChild(p);
    });
  }

  void DetachFromEntity() override
  {
    this->Loop([&](T* p) {
      p->RemoveSelf();
    });
  }

  T* GetHitEntity(GameEntity* other)
  {
    return Select([&](T* p) {
      return p->HitCheck(other);
    });
  }

  template<class T2>
  T* GetHitEntity(GameEntityManager<T2>* other_collider_manager, T2** other_dest)
  {
    return Select([&](T* p) {
      (*other_dest) = other_collider_manager->GetHitEntity((*itr));
      return (*other_dest);
    });
  }

  void GetHitEntities(GameEntity* other, typename std::deque<T*>* dest)
  {
    return SelectAll(
      dest,
      [&](T* p) {
        return p->HitCheck(other);
      }
    );
  }

  template<class T2>
  void GetHitEntities(GameEntityManager<T2>* other_collider_manager, typename std::map<T*, std::deque<T2*>>* dest)
  {
    this->Loop([&](T* p)
    {
      other_collider_manager->GetHitEntities(p, &((*dest)[p]));
    });
  }

  T* GetNearestEntity(GameEntity* entity)
  {
    T_FLOAT nearest_distance = Limit::T_FLOAT_MAX;
    T* nearest_entity = nullptr;
    this->Loop([&](T* p)
    {
      if (p == entity)
      {
        return;
      }
      T_FLOAT distance = (entity->GetTransform()->GetWorldPosition() - p->GetTransform()->GetWorldPosition()).Length();
      distance -= p->GetColliderRadius() + entity->GetColliderRadius();
      if (distance < nearest_distance)
      {
        nearest_distance = distance;
        nearest_entity = p;
      }
    });
    return nearest_entity;
  }

};
