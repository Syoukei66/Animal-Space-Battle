#pragma once

#include <vector>
#include <HalEngine.h>
#include "GameEntityManager.h"
#include "Player.h"
#include "PlayerEntryList.h"
#include "PlayerView.h"
#include "PlayerInputBuilder.h"

class StarManager;

class PlayerManager : public GameEntityManager<Player>
{
public:
  static PlayerManager& GetInstance()
  {
    static PlayerManager self;
    return self;
  }

private:
  PlayerManager();

public:
  virtual ~PlayerManager();

public:
  void Init(const PlayerEntryList* entries);
  void Uninit();

public:
  virtual void Loop(std::function<void(Player*)> func) override;
  virtual void Loop(std::function<void(const Player*)> func) const;
  virtual void LoopIncludingPool(std::function<void(Player*)> func) override;
  virtual void LoopIncludingPool(std::function<void(const Player*)> func) const;

  virtual Player* Select(std::function<bool(Player*)> condition) override;
  virtual const Player* Select(std::function<bool(const Player*)> condition) const;
  virtual void SelectAll(std::deque<Player*>* dest, std::function<bool(Player*)> condition) override;
  virtual void SelectAll(std::deque<const Player*>* dest, std::function<bool(const Player*)> condition) const;

  virtual void LoopMT(std::function<void(Player*)> func);
  virtual void LoopMT(std::function<void(const Player*)> func) const;
  virtual void LoopIncludingPoolMT(std::function<void(Player*)> func);
  virtual void LoopIncludingPoolMT(std::function<void(const Player*)> func);

public:
  void AttachAdditionToScene(Scene* scene);
  void DetachAdditionFromScene(Scene* scene);

  void GachaCountDown(T_UINT32 left_time);
  void StartGacha();

  void Update() override;

  void CollisionToOtherPlayers();
  void CollisionToStar(StarManager* star_manager);

public:
  inline Player* GetPlayer(T_UINT8 id) const
  {
    return this->players_[id];
  }
  inline PlayerView* GetPlayerView(T_UINT8 id) const
  {
    return this->views_[id];
  }
  inline T_UINT8 GetPlayerCount() const
  {
    return this->players_.size();
  }
  
private:
  std::vector<Player*> players_;
  std::vector<PlayerView*> views_;
  std::vector<PlayerInputBuilder*> inputs_;

};
