#pragma once

#include <HalEngine.h>

class Player;
class Star;

class BaseBulletEmitter
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  BaseBulletEmitter()
    : player_(nullptr)
  {
  }
  virtual ~BaseBulletEmitter() {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Init(Player* player)
  {
    this->player_ = player;
  }

  virtual void Emission()
  {
    if (this->delay_ > 0)
    {
      return;
    }
    this->delay_ = this->EmissionProcess();
  }

  virtual void Update()
  {
    if (this->delay_ == 0)
    {
      return;
    }
    this->delay_--;
  }

  virtual void AttachToScene(GameObject3D* root3d) = 0;
  virtual void DetachFromScene() = 0;

  virtual T_UINT32 CollisionToPlayer(Player* player) = 0;
  virtual T_UINT32 CollisionToStar(Star* player) = 0;

protected:
  virtual T_UINT32 EmissionProcess() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
protected:
  inline Player* GetPlayer() const
  {
    return this->player_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Player* player_;
  T_UINT16 delay_;

};