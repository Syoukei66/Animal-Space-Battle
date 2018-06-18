#pragma once

#include "GameEntity.h"
#include "PlayerStatus.h"
#include "BulletEmitterManager.h"

class PlayerActor;
class PlayerInput;
class PlayerEntry;
class PlayerResult;
class PlayerManager;
class PlayerStateManager;
class CharactorController;
class Star;

class Player : public GameEntity
{
public:
  enum State
  {
    STATE_NULL,
    STATE_FLYING,
    STATE_GACHA,

    STATE_NUMMAX,
  };

public:
  Player(const PlayerEntry& entry);
  virtual ~Player();

public:
  void GameLevelReflection();
  void ResolveInput(const PlayerInput& input, const PlayerManager& manager);
  void BulletUpdateProcess();
  void TransformUpdate();

  void ResetVelocity();
  void SetVelocity(const TVec3f& velocity);
  void AddVelocity(const TVec3f& velocity);
  void AddDamagedVelocity(const TVec3f& velocity);
  bool AddDamage(T_UINT16 damage);
  void AddScore(T_UINT32 score);
  void SubScore(T_UINT32 score);
  T_UINT32 DivideScore();

  bool CollisionToOther(Player* other);
  bool CollisionToStar(Star* star);

  void Landing(Star* star, const TVec3f& vec);
  void TakeOff();

  void GetInVehicle(const VehicleData* data);
  void Death();

  void HpMax();

public:
  inline void ChangeState(T_UINT8 state_id);

public:
  inline T_UINT8 GetID() const
  {
    return this->id_;
  }

  inline bool IsDead() const
  {
    return this->is_dead_;
  }

  inline bool IsHuman() const
  {
    return this->is_human_;
  }

  inline bool IsGrounded() const
  {
    return this->landed_star_;
  }

  inline void SetTarget(Player* target)
  {
    this->target_ = target;
  }

  inline Player* GetTarget() const
  {
    return this->target_;
  }

  inline const TVec3f& GetVelocity() const
  {
    return this->velocity_;
  }

  inline const PlayerStatus& GetStatus() const
  {
    return *this->status_;
  }

  inline T_UINT16 GetHp() const
  {
    return this->hp_;
  }

  inline T_UINT16 GetMaxHp() const
  {
    return this->max_hp_;
  }

  inline BulletEmitterManager* GetBulletEmitter() const
  {
    return this->bullet_emitter_;
  }

  inline const PlayerResult* GetResult() const
  {
    return this->result_;
  }

private:
  const T_UINT8 id_;
  PlayerResult* result_;
  const bool is_human_;
  PlayerStatus* const status_;
  PlayerStateManager* const state_;
  BulletEmitterManager* const bullet_emitter_;

  PlayerActor* actor_;

  TVec3f velocity_;
  TVec3f damaged_velocity_;

  T_UINT16 hp_;
  T_UINT16 max_hp_;
  bool is_dead_;

  Player* target_;
  Star* landed_star_;

};
