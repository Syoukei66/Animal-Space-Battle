#pragma once

#include <HalEngine.h>
#include "BulletManager.h"
#include "BaseBulletEmitter.h"
#include "Bullet.h"
#include "Player.h"
#include "Star.h"
#include "ScoreConstatns.h"

class BulletEmitter : public BaseBulletEmitter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  BulletEmitter(T_UINT16 count)
    : bullets_(new BulletManager(count))
  {}
  virtual ~BulletEmitter()
  {
    delete this->bullets_;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  void Update() override
  {
    BaseBulletEmitter::Update();
    this->UpdateProcess();
    this->bullets_->Update();
  }
  void AttachToScene(GameObject3D* scene)
  {
    this->bullets_->AttachToEntity(scene);
  }
  void DetachFromScene()
  {
    this->bullets_->DetachFromEntity();
  }
  T_UINT32 CollisionToPlayer(Player* player) override
  {
    std::deque<Bullet*> hited_bullet = std::deque<Bullet*>();
    this->bullets_->GetHitEntities(player, &hited_bullet);
    for (Bullet* bullet : hited_bullet)
    {
      if (player->AddDamage(bullet->GetPower()))
      {
        this->GetPlayer()->AddScore(ScoreConstants::POINT_DESTROY_ENEMY);
      }
      bullet->DeadBullet();
    }
    return hited_bullet.size();
  }
  T_UINT32 CollisionToStar(Star* star) override
  {
    std::deque<Bullet*> hited_bullet = std::deque<Bullet*>();
    this->bullets_->GetHitEntities(star, &hited_bullet);
    for (Bullet* bullet : hited_bullet)
    {
      star->AddDamage(this->GetPlayer(), 100);
      bullet->DeadBullet();
    }
    return hited_bullet.size();
  }
protected:
  virtual void UpdateProcess() = 0;

  inline Bullet* Allocate()
  {
    Bullet* ret = this->bullets_->Allocate();
    if (!ret)
    {
      return nullptr;
    }
    ret->SetPlayer(this->GetPlayer());
    ret->SetTarget(this->GetPlayer()->GetTarget());
    return ret;
  }

  inline void Free(Bullet* p)
  {
    return this->bullets_->Free(p);
  }
  
  // =================================================================
  // Data Member
  // =================================================================
private:
  BulletManager* bullets_;

};