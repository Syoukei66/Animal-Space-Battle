#pragma once

#include <HalEngine.h>
#include "GameEntityManager.h"

template<class T>
class AllocatableGameEntityManager : public GameEntityManager<T>
{
public:
  AllocatableGameEntityManager(T_UINT16 size)
    : allocator_(size)
  {
    this->Loop([](T* p) {
      p->SetVisible(false);
    });
  }

  virtual ~AllocatableGameEntityManager()
  {
    this->Loop([](T* p) {
      p->RemoveSelf();
    });
  }

public:
  virtual void Loop(std::function<void(T*)> func) override
  {
    this->allocator_.Loop(func);
  }

  virtual void LoopIncludingPool(std::function<void(T*)> func) override
  {
    this->allocator_.LoopIncludingPool(func);
  }

  virtual T* Select(std::function<bool(T*)> condition) override
  {
    return this->allocator_.Select(condition);
  }

  virtual void SelectAll(std::deque<T*>* dest, std::function<bool(T*)> condition) override
  {
    this->allocator_.SelectAll(dest, condition);
  }

public:
  inline T* Allocate()
  {
    return this->allocator_.Allocate();
  }
  inline void Free(T* p)
  {
    return this->allocator_.Free(p);
  }

private:
  PoolAllocator<T> allocator_;

};