#include "ResultScene.h"
#include "GameDirector.h"
#include "GameLayer.h"

const float camera_pos[]{
	12,-3,-17,
	12,-6,-5,
	12,-9,-11,
	6,-12,43
};

void ResultScene::OnLoad(IResourceLoadReserver* resource)
{
  //Playerを表示するのに最低限必要なものら
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE);
  resource->ReserveLoad(Asset::Texture::SHADER_NOISE_NORMAL);

  resource->ReserveLoad(Asset::Fbx::STAR);
  resource->ReserveLoad(Asset::Fbx::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Fbx::JET);

  resource->ReserveLoad(Asset::Shader::PLAYER_EYE_LINE);
  resource->ReserveLoad(Asset::Shader::JET);
  resource->ReserveLoad(Asset::Shader::COLLIDER);

	resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK1);
	resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK1_KAI);
	resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK2);
	resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK3);
	resource->ReserveLoad(Asset::Texture::UI_GAME_RANK_RANK4);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK2);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK3);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK4);
  resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK_CP);


	resource->ReserveLoad(Asset::Texture::UI_PLAYER_1P);
	resource->ReserveLoad(Asset::Texture::UI_PLAYER_2P);
	resource->ReserveLoad(Asset::Texture::UI_PLAYER_3P);
	resource->ReserveLoad(Asset::Texture::UI_PLAYER_4P);


	resource->ReserveLoad(Asset::Texture::UI_WHITE);


	//resource->ReserveLoad(Asset::Sound::RESULT);
}

void ResultScene::OnSetup()
{
	const float screen_x = Director::GetInstance()->GetScreenWidth();
	const float screen_y = Director::GetInstance()->GetScreenHeight();

  this->camera_2d_ = new Camera2D();
  this->camera_2d_->SetViewportClear(false);
  this->AddCamera(this->camera_2d_);

  this->main_camera_ = new Camera3D_LookAt();
  this->main_camera_->GetTransform()->Rotate(TVec3f(0, 1, 0), T_FLOAT(MathConstants::PI));
	this->main_camera_->GetTransform()->SetPosition(0,-20,80);
  this->AddCamera(this->main_camera_);

	//Sound::
	img_[IMG_WHITE] = Sprite::CreateWithResource(Asset::Texture::UI_WHITE);
	img_[IMG_RANK1_KAI] = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK1_KAI);
	img_[IMG_RANK1] = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK1);
	img_[IMG_RANK2] = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK2);
	img_[IMG_RANK3] = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK3);
	img_[IMG_RANK4] = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK4);
	img_[IMG_1P] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK);
	img_[IMG_2P] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK2);
	img_[IMG_3P] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK3);
	img_[IMG_4P] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK4);

  this->playeres_.clear();
  const T_UINT8 player_count = GameDirector::GetPlayerResultList()->GetPlayerCount();
  for (T_UINT8 i = 0; i < player_count; ++i)
  {
    this->main_camera_->GetRenderState()->AddTargetLayerId(GameLayer::LAYER_PLAYER_0_BODY + i);
  }
  //順位の種類の数
  const T_UINT8 rank_count = GameDirector::GetPlayerResultList()->GetRankCount();
  this->playeres_.resize(rank_count);
  //iが順位ということになる
	int ninnzuu = -1;
  for (T_UINT8 i = 0; i < rank_count; ++i)
  {
    const std::vector<PlayerResult*>& results = GameDirector::GetPlayerResultList()->GetResultByRank(i);
		int player_id;
    for (PlayerResult* result : results)
    {
			ninnzuu++;
      PlayerActor* actor = new PlayerActor();
			player_id = result->entry->id;
			if (!i) {
				img_[IMG_ICON + number_one_num_] = result->entry->animal_data->CreateIcon();
				img_[IMG_ICON + number_one_num_]->GetTransform()->SetScale(0.5);
				vehicle_id_ = result->entry->vehicle_data->GetId();
			}
      actor->ChangeAnimalData(result->entry->animal_data);
      actor->ChangeVehicleData(result->entry->vehicle_data);
      actor->ChangePlayerId(result->entry->id);

      actor->GetModelMaterial()->Vec3fProperty("_LightDirection") = TVec3f(0.0f, 0.0f, -1.0f);

      actor->GetTransform()->SetX((result->entry->id - (player_count - 1) * 0.5f) * ((i * 50.0f) / player_count));
      actor->GetTransform()->SetZ(30.0f + i * 20.0);
      actor->GetTransform()->SetY(actor->GetColliderRadius() * 0.5f);

      actor->GetTransform()->RotateY(MathConstants::PI);

      this->AddChild(actor);
      this->playeres_[i].push_back(actor);
			switch (i) {
			case 1:{
				rank_[ninnzuu].junni = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK2);
				break;
			}
			case 2: {
				rank_[ninnzuu].junni = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK3);
				break;
			}
			case 3: {
				rank_[ninnzuu].junni = Sprite::CreateWithResource(Asset::Texture::UI_GAME_RANK_RANK4);
				break;
			}
			}
      if (result->entry->entry_kind == PlayerEntry::PLAYER_ENTRY_PLAYER)
      {
        switch (player_id) {
          case 0: {
            if (i == 0) rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_1P);
            else rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK);
            break;
          }
          case 1: {
            if (i == 0) rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_2P);
            else rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK2);
            break;
          }
          case 2: {
            if (i == 0) rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_3P);
            else rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK3);
            break;
          }
          case 3: {
            if (i == 0) rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_4P);
            else rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK4);
            break;
          }
        }
      }
      else if (result->entry->entry_kind == PlayerEntry::PLAYER_ENTRY_COMPUTER)
      {
        rank_[ninnzuu].player_id = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK_CP);
			}
			if (i&&rank_[ninnzuu].player_id&&rank_[ninnzuu].junni)
			{
				rank_[ninnzuu].player_id->GetTransform()->SetPositon(screen_x / 2.1*-1 + 0.5, (screen_y / 2.7) - (170 * ninnzuu) + 0.5);
				rank_[ninnzuu].player_id->GetTransform()->SetScale(0.15);
				rank_[ninnzuu].junni->GetTransform()->SetPositon((screen_x / 2.1*-1) + 20.5, (screen_y / 2.7) - (170 * ninnzuu) + 0.5);
				rank_[ninnzuu].junni->GetTransform()->SetScale(0.15);
				this->AddChild(rank_[ninnzuu].player_id);
				this->AddChild(rank_[ninnzuu].junni);
			}
			else 
			{
				rank_[ninnzuu].player_id->GetTransform()->SetPositon(screen_x*-0.1,screen_y*0.3-(number_one_num_*100));
				rank_[ninnzuu].player_id->GetTransform()->SetScale(0.07);
				this->AddChild(rank_[ninnzuu].player_id);
				number_one_num_++;
			}

		}
		img_[IMG_RANK1_KAI]->GetTransform()->SetPositon(screen_x / -3.7, screen_y / 3.7);
		img_[IMG_RANK1_KAI]->GetTransform()->SetScaleX(0.2);
		img_[IMG_RANK1_KAI]->GetTransform()->SetScaleY(0.3);
		this->AddChild(img_[IMG_RANK1_KAI]);

  }


	img_[IMG_WHITE]->GetTransform()->SetScale(10);
	this->AddChild(img_[IMG_WHITE]);
	for (int n = 0; n < 4; n++) {
		if (img_[IMG_ICON + n]) {
			img_[IMG_ICON + n]->GetTransform()->SetPositon(-n*500, 0);
			icon_parent_.AddChild(img_[IMG_ICON+n]);
		}
	}
	this->AddChild(&icon_parent_);

	{//Modifie		
		const int start_fade_time = 90;
		//最初の白い画面のフェード
		EntityModifier* n0 = EntityModifierFactory::Delay(60);
		EntityModifier* n1 = EntityModifierFactory::ColorTo(start_fade_time,Color4F(1,1,1,0));
		EntityModifier* n2 = EntityModifierFactory::Sequence(n0,n1);
		modifier_[MOD_WHITE] = EntityModifierFactory::Root(n2);
		img_[IMG_WHITE]->RegisterEntityModifier(modifier_[MOD_WHITE]);

		//ICONのうごき
		EntityModifier* m0 = EntityModifierFactory::Delay(60);
		EntityModifier* m1 = EntityModifierFactory::ScaleTo(start_fade_time,0.2);
		EntityModifier* m2 = EntityModifierFactory::TranslateToX(start_fade_time, screen_x*0.4);
		EntityModifier* m3 = EntityModifierFactory::Synchronized(m1, m2);
		EntityModifier* m4 = EntityModifierFactory::TranslateToY(start_fade_time, screen_y*-0.35);
		EntityModifier* m5 = EntityModifierFactory::Synchronized(m3, m4);
		m5->SetEasingFunction(EasingFunction::FK_EXPONENTIAL, EasingFunction::EASE_IN);
		m5->SetEasingFunction(EasingFunction::FK_EXPONENTIAL, EasingFunction::EASE_OUT);
		EntityModifier* m6 = EntityModifierFactory::Sequence(m0, m5);
		modifier_[MOD_ICON] = EntityModifierFactory::Root(m6);
		icon_parent_.RegisterEntityModifier(modifier_[MOD_ICON]);

	}
}

void ResultScene::OnUnload()
{
  for (std::vector<PlayerActor*>& actors : this->playeres_)
  {
    for (PlayerActor* actor : actors)
    {
      delete actor;
    }
  }
	for (int i=0;i<IMG_MAX;i++) {
		delete img_[i];
	}
	for (int i=0;i<MOD_MAX;i++) {
		if(modifier_[i])modifier_[i]->Release();
	}
	for(int i=0 ; i<4;++i){
		delete rank_[i].junni;
		delete rank_[i].player_id;
	}
  delete this->main_camera_;
  delete this->camera_2d_;
}

void ResultScene::OnShow(ISceneShowListener* listener)
{
}

void ResultScene::OnHide(ISceneHideListener* listener)
{
}

void ResultScene::Update()
{
	const float screen_x = Director::GetInstance()->GetScreenWidth();
	const float screen_y = Director::GetInstance()->GetScreenHeight();
	//static float n[3]={};
	//ImGui::SetNextWindowPos(ImVec2(200, 300), ImGuiSetCond_Once);
 // ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiSetCond_Once);
 // ImGui::Begin(u8"テスト");
	//ImGui::SliderFloat3(u8"テスト数値", this->num_, 0.0f, 10.0f, "%.1f");
	//ImGui::SliderFloat3(u8"テスト数値2", n, 0, 1, "%.3f");
	//ImGui::End();

	++rotate_;
	if(rotate_<180)
	{
		main_camera_->GetTransform()->SetPosition(camera_pos[vehicle_id_*3]*((float)rotate_ / 180), 20 * ((float)rotate_ / 180)-20+camera_pos[vehicle_id_*3+1], (-80+camera_pos[vehicle_id_*3+2]) * ((float)rotate_ / 180)+80);
		this->main_camera_->GetTransform()->Rotate(TVec3f(0, 1, 0), -MathConstants::PI / 160);
	}
  //main_camera_->GetTransform()->SetPosition(this->num_[0], this->num_[1], this->num_[2]);
	//main_camera_->GetTransform()->SetPosition(this->num_[0], this->num_[1], this->num_[2]);

	//12 -3 -17
	//12 -6 -5
	//12 -9 -11
	//6  -12 43

	
	//float axis = HalEngine::Input(0)->GetAxis(GameInput::Y_AXIS);
	//if (
	//{
	//	main_camera_->GetTransform()->SetPosition(axis);
	//}
}
