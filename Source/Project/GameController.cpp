#include "GameController.h"
#include "GameLevelParam.h"
#include "GameDirector.h"
#include "BaseGameScene.h"
#include "GameSceneVisualParam.h"
#include "ViewportSetting.h"
#include "Environment.h"

GameController::GameController(BaseGameScene* scene)
{
  this->scene_ = scene;
}

void GameController::OnLoad(IResourceLoadReserver* resource)
{
  resource->ReserveLoad(Asset::Fbx::SKYDOME);
  resource->ReserveLoad(Asset::Fbx::STAR);
  resource->ReserveLoad(Asset::Fbx::SPACE_WALL);
  resource->ReserveLoad(Asset::Fbx::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Fbx::JET);

  resource->ReserveLoad(Asset::Texture::TEST_BULLET);
  resource->ReserveLoad(Asset::Texture::UI_GAME_BG);
  resource->ReserveLoad(Asset::Texture::UI_GAME_NUMBER);
  resource->ReserveLoad(Asset::Texture::UI_GAME_NUMBER_DOT);
  resource->ReserveLoad(Asset::Texture::UI_GAME_ANIMAL_ICON_BG);
  resource->ReserveLoad(Asset::Texture::UI_GAME_VEHICLE_ICON_BG);
  resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK1);
  resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK2);
  resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK3);
  resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK4);
  resource->ReserveLoad(Asset::Texture::UI_GAME_HP_GAUGE);
  resource->ReserveLoad(Asset::Texture::UI_GAME_HP_GAUGE_FRAME);
  resource->ReserveLoad(Asset::Texture::UI_GAME_LOCKON);
  resource->ReserveLoad(Asset::Texture::UI_GAME_COUNT_MESSAGE);
  resource->ReserveLoad(Asset::Texture::UI_GAME_COUNT_NUMBER);
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE);
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE_NORMAL);
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE_NORMAL1);

  resource->ReserveLoad(Asset::Texture::UI_PLAYER_1P);
  resource->ReserveLoad(Asset::Texture::UI_PLAYER_2P);
  resource->ReserveLoad(Asset::Texture::UI_PLAYER_3P);
  resource->ReserveLoad(Asset::Texture::UI_PLAYER_4P);

  resource->ReserveLoad(Asset::Shader::STAR);
  resource->ReserveLoad(Asset::Shader::STAR_WALL);
  resource->ReserveLoad(Asset::Shader::SPACE_GRID);
  resource->ReserveLoad(Asset::Shader::SPACE_WALL);
  resource->ReserveLoad(Asset::Shader::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Shader::JET);
  resource->ReserveLoad(Asset::Shader::GACHA_STAR);
  resource->ReserveLoad(Asset::Shader::GACHA_JET);
  resource->ReserveLoad(Asset::Shader::GACHA_WORLD);
  resource->ReserveLoad(Asset::Shader::POST_EFFECT);

  resource->ReserveLoad(Asset::Json::GAME_UI);
  resource->ReserveLoad(Asset::Json::GAME_LEVEL);
  resource->ReserveLoad(Asset::Json::GAME_SCENE_VISUAL);

  resource->ReserveLoad(Asset::Sound::SHOT_SHOT_CIRCLE);
  resource->ReserveLoad(Asset::Sound::SHOT_SHOT_SANDAN);
  resource->ReserveLoad(Asset::Sound::SHOT_SHOT_WAY);
  resource->ReserveLoad(Asset::Sound::SHOT_SHOT_ZIBAKU);

  resource->ReserveLoad(Asset::Sound::BARRIER);
  resource->ReserveLoad(Asset::Sound::DAMAGE);
  resource->ReserveLoad(Asset::Sound::FLAG);
  resource->ReserveLoad(Asset::Sound::BGM_GAME);

}

void GameController::OnSetup()
{
  GameLevelParam::GetInstance().LoadFromJson(Asset::Json::GAME_LEVEL.GetContents()->GetRoot());
  GameSceneVisualParam::GetInstance().LoadFromJson(Asset::Json::GAME_SCENE_VISUAL.GetContents()->GetRoot());

  this->star_manager_ = new StarManager();
  Environment::GetInstance().SetStarManager(this->star_manager_);
  PlayerManager::GetInstance().Init(GameDirector::GetPlayerEntryList());
  this->field_ = new Field();
  this->scene_->AddChild(this->field_);

  PlayerManager::GetInstance().AttachToEntity(this->scene_->GetRoot3d());
  PlayerManager::GetInstance().AttachAdditionToScene(this->scene_);
  this->star_manager_->AttachToEntity(this->scene_->GetRoot3d());

  Environment::GetInstance().SetPlayerManager(&PlayerManager::GetInstance());
}

void GameController::OnUnload()
{
  delete this->field_;
  delete this->star_manager_;
  PlayerManager::GetInstance().Uninit();
}

void GameController::OnShow(ISceneShowListener* listener)
{
  Asset::Sound::BGM_GAME.Play(-1);
}

void GameController::OnHide(ISceneHideListener* listener)
{
}

void GameController::Update()
{
  if (GameLevelParam::GetInstance().IsStarLevelsDirty())
  {
    this->star_manager_->DetachFromEntity();
    delete this->star_manager_;
    this->star_manager_ = new StarManager();
    this->star_manager_->AttachToEntity(this->scene_->GetRoot3d());
    Environment::GetInstance().SetStarManager(this->star_manager_);
  }

  PlayerManager::GetInstance().CollisionToStar(this->star_manager_);
  PlayerManager::GetInstance().CollisionToOtherPlayers();
  PlayerManager::GetInstance().Update();
  GameDirector::GetPlayerResultList()->Commit();

  if (ViewportSetting::GetInstance().Update())
  {
    GameDirector::GameFinish();
  }

}

void GameController::PostUpdate()
{
  GameLevelParam::GetInstance().ResetFlags();
}
