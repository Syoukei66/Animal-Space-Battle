#include "PlayerManager.h"

#include <ppl.h>

#include "GameLevelParam.h"
#include "Bullet.h"
#include "StarManager.h"
#include "PlayerUI.h"
#include "PlayerInput.h"
#include "ViewportSetting.h"

#include "GachaEffect.h"
#include "ScoreConstatns.h"

PlayerManager::PlayerManager()
  : players_()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Init(const PlayerEntryList* entries)
{
  T_UINT8 entry_count = entries->GetEntriesCount();
  ViewportSetting::GetInstance().Init(entry_count);
  T_UINT8 player_id = 0;
  T_UINT8 computer_id = 0;
  for (T_UINT8 i = 0; i < entry_count; ++i)
  {
    PlayerEntry* entry = entries->GetEntry(i);
    if (!entry)
    {
      continue;
    }
    Player* player = new Player(*entry);
    player->GetTransform()->RotateY((T_FLOAT)i / entry_count * MathConstants::PI_2);
    player->GetTransform()->MoveZ(-150.0f);
    this->players_.push_back(player);
    if (player->IsHuman())
    {
      this->views_.push_back(PlayerView::Create(player));
      this->inputs_.push_back(PlayerInputBuilder::CreatePlayer(player_id));
      ViewportSetting::GetInstance().SetEnabled(player_id + computer_id, true);
      ++player_id;
      continue;
    }
    if (entry->entry_kind == PlayerEntry::PLAYER_ENTRY_COMPUTER)
    {
      this->inputs_.push_back(PlayerInputBuilder::CreateComputer(computer_id));
    }
    if (entry->entry_kind == PlayerEntry::PLAYER_ENTRY_DEBUG)
    {
      this->inputs_.push_back(PlayerInputBuilder::CreateDebug());
    }
    this->views_.push_back(PlayerView::Create(player));

    ++computer_id;
  }
}

void PlayerManager::Uninit()
{
  for (PlayerInputBuilder* input : this->inputs_)
  {
    delete input;
  }
  this->inputs_.clear();
  for (PlayerView* view : this->views_)
  {
    delete view;
  }
  this->views_.clear();
  for (Player* player : this->players_)
  {
    delete player;
  }
  this->players_.clear();
  ViewportSetting::GetInstance().Uninit();
}

void PlayerManager::Loop(std::function<void(Player*)> func)
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

void PlayerManager::Loop(std::function<void(const Player*)> func) const
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

void PlayerManager::LoopIncludingPool(std::function<void(Player*)> func)
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

void PlayerManager::LoopIncludingPool(std::function<void(const Player*)> func) const
{
  for (Player* player : this->players_)
  {
    func(player);
  }
}

Player* PlayerManager::Select(std::function<bool(Player*)> condition)
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      return player;
    }
  }
  return nullptr;
}

const Player* PlayerManager::Select(std::function<bool(const Player*)> condition) const
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      return player;
    }
  }
  return nullptr;
}

void PlayerManager::SelectAll(std::deque<Player*>* dest, std::function<bool(Player*)> condition)
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      dest->push_back(player);
    }
  }
}

void PlayerManager::SelectAll(std::deque<const Player*>* dest, std::function<bool(const Player*)> condition) const
{
  for (Player* player : this->players_)
  {
    if (condition(player))
    {
      dest->push_back(player);
    }
  }
}

void PlayerManager::LoopMT(std::function<void(Player*)> func)
{
  concurrency::parallel_for_each(this->players_.begin(), this->players_.end(), [&](Player* player)
  {
    func(player);
  });
}

void PlayerManager::LoopMT(std::function<void(const Player*)> func) const
{
  concurrency::parallel_for_each(this->players_.begin(), this->players_.end(), [&](Player* player)
  {
    func(player);
  });
}

void PlayerManager::LoopIncludingPoolMT(std::function<void(Player*)> func)
{
  concurrency::parallel_for_each(this->players_.begin(), this->players_.end(), [&](Player* player)
  {
    func(player);
  });
}

void PlayerManager::LoopIncludingPoolMT(std::function<void(const Player*)> func)
{
  concurrency::parallel_for_each(this->players_.begin(), this->players_.end(), [&](Player* player)
  {
    func(player);
  });
}

void PlayerManager::AttachAdditionToScene(Scene* scene)
{
  for (PlayerView* view : this->views_)
  {
    if (view)
    {
      view->AttachAdditionToScene(scene);
    }
  }
}

void PlayerManager::DetachAdditionFromScene(Scene* scene)
{
  for (PlayerView* view : this->views_)
  {
    if (view)
    {
      view->DetachAdditionFromScene(scene);
    }
  }
}

void PlayerManager::GachaCountDown(T_UINT32 left_time)
{
  for (PlayerView* view : this->views_)
  {
    if (view)
    {
      view->GachaCountDown(left_time);
    }
  }
}

void PlayerManager::StartGacha()
{
  this->Loop([](Player* player)
  {
    player->ChangeState(Player::STATE_GACHA);
  });
}

void PlayerManager::Update()
{
  this->Loop([&](Player* player)
  {
    player->GameLevelReflection();
  });
  T_UINT8 id = 0;
  for (PlayerInputBuilder* input : this->inputs_)
  {
    input->InputProcess(this->players_[id]);
    ++id;
  }
  id = 0;
  this->Loop([&](Player* player)
  {
    player->ResolveInput(this->inputs_[id]->GetInput(), *this);
    ++id;
  });
  this->Loop([&](Player* player)
  {
    player->BulletUpdateProcess();
  });
  this->Loop([&](Player* player)
  {
    player->TransformUpdate();
  });
  for (PlayerView* view : this->views_)
  {
    view->ViewportUpdate();
  }
  ViewportSetting::GetInstance().ResetDirtyFlag();
}

void PlayerManager::CollisionToOtherPlayers()
{
  T_UINT8 player_count = this->GetPlayerCount();
  T_UINT8 loop_offset = 0;
  T_UINT8 loop_index = 0;
  this->Loop([&](Player* player)
  {
    loop_index = 0;
    this->Loop([&](Player* other_player)
    {
      loop_index++;
      if (player == other_player)
      {
        return;
      }
      const T_UINT32 hited_count = player->GetBulletEmitter()->CollisionToPlayer(other_player);
      player->AddScore(ScoreConstants::POINT_ATTACK_TO_ENEMY * hited_count);
      if (loop_index - 1 < loop_offset)
      {
        return;
      }
      player->CollisionToOther(other_player);
    });
    ++loop_offset;
  });
}

void PlayerManager::CollisionToStar(StarManager* star_manager)
{
  this->Loop([&](Player* player)
  {
    star_manager->Select([&](Star* star)
    {
      return player->CollisionToStar(star);
    });
  });
}
