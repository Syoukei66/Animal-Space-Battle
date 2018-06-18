#pragma once

#include "GameEntity.h"

class Player;

class Bullet : public GameEntity, public IPoolAllocatable
{
public:
  Bullet();
  virtual ~Bullet();

public:
  virtual void OnAllocated() override;
  virtual void OnFree() override;

  void BulletInit();
  void BulletUninit();
  void BulletUpdate();

  void DeadBullet();

public:
  inline bool IsAlive() const
  {
    return this->lifetime_ > 0;
  }
  inline void SetPlayer(Player* player)
  {
    this->user_ = player;
  }
  inline const Player* GetPlayer() const
  {
    return this->user_;
  }
  inline void SetTarget(Player* target)
  {
    this->target_ = target;
  }
  inline const Player* GetTarget() const
  {
    return this->target_;
  }
  inline void SetEffectId(T_UINT8 id)
  {
    this->effect_id_ = id;
  }
  inline T_UINT8 GetEffectId() const
  {
    return this->effect_id_;
  }
  inline void SetLifeTime(T_UINT16 lifetime)
  {
    this->lifetime_ = lifetime;
  }
  inline T_UINT16 GetLifeTime() const
  {
    return this->lifetime_;
  }
  inline void SetPower(T_UINT16 power)
  {
    this->power_ = power;
  }
  inline T_UINT16 GetPower() const
  {
    return this->power_;
  }
  inline void SetDelay(T_UINT16 delay)
  {
    this->delay_ = delay;
  }
  inline T_UINT16 GetDelay() const
  {
    return this->delay_;
  }
  inline void SetHomingLifeTime(T_UINT16 homing_lifetime)
  {
    this->homing_lifetime_ = homing_lifetime;
  }
  inline T_UINT16 GetHomingLifeTime() const
  {
    return this->homing_lifetime_;
  }
  inline void SetHomingRate(T_FLOAT homing_rate)
  {
    this->homing_rate_ = homing_rate;
  }
  inline T_UINT16 GetHomingRate() const
  {
    return this->homing_rate_;
  }
  inline void SetRadius(T_FLOAT radius)
  {
    this->GetTransform()->SetScale(radius);
    this->radius_ = radius;
  }
  inline T_FLOAT GetRadius() const
  {
    return this->radius_;
  }
  inline void SetLength(T_FLOAT length)
  {
    this->length_ = length;
  }
  inline T_FLOAT GetLength() const
  {
    return this->length_;
  }
  inline void SetPadding(T_FLOAT padding)
  {
    this->padding_ = padding;
  }
  inline T_FLOAT GetPadding() const
  {
    return this->padding_;
  }
  inline void SetMaxSpeed(T_FLOAT speed)
  {
    this->max_speed_ = speed;
  }
  inline T_FLOAT GetMaxSpeed() const
  {
    return this->max_speed_;
  }
  inline void SetSpeed(T_FLOAT speed)
  {
    this->speed_ = speed;
  }
  inline T_FLOAT GetSpeed() const
  {
    return this->speed_;
  }
  inline void SetAccel(T_FLOAT accel)
  {
    this->accel_ = accel;
  }
  inline T_FLOAT GetAccel() const
  {
    return this->accel_;
  }
  inline void SetVector(const TVec3f& vec)
  {
    this->vec_ = vec;
  }
  inline const TVec3f& GetVector() const
  {
    return this->vec_;
  }
public:
  Player* user_;
  Player* target_;

  T_UINT8 effect_id_;
  T_UINT16 lifetime_;
  T_UINT16 power_;

  T_UINT16 delay_;

  T_UINT16 homing_lifetime_;
  T_FLOAT homing_rate_;

  T_FLOAT radius_;
  T_FLOAT length_;
  T_FLOAT padding_;

  T_FLOAT max_speed_;
  T_FLOAT speed_;
  T_FLOAT accel_;
  TVec3f vec_;

private:
  Model* model_;

};