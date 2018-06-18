#include "CharaSelectScene.h"
#include "GameScene.h"
#include "GameDirector.h"

#include "AnimalTable.h"
#include "VehicleTable.h"

#include "TitleScene.h"
#include "ResultScene.h"

#include <windows.h>

static const int kMaxPlayer =										4;
static const int kMaxCharactor =								4;

static const float kCharactorIconPosX =					-100.0f;
static const float kCharactorIconPosY =					+100.0f;
static const float kCharactorIconScale =				0.1f;
static const float kCharactorBackGroundScale =	0.25f;

//キャラクターを選択したときに表示される数字の位置
static const int kNumX = 100;
static const int kNumY = 30;

static const float kPosIndex[] = {
	-1,1,
	1,1,
	-1,-1,
	1,-1,
};



struct CharactorSelectSceneVariable
{

	float cursor_pos_x[kMaxPlayer];
	float cursor_pos_y[kMaxPlayer];
	float select_icon_pos_y[kMaxCharactor];
	CharactorSelectSceneVariable() {
		for (int i=0 ; i<kMaxPlayer ; ++i) {
			cursor_pos_x[i] = 0;//TODOあとで正しい値を入れる
			cursor_pos_y[i] = 0;
		}
	}
};

static CharactorSelectSceneVariable* charselect_var;


void CharaSelectScene::OnLoad(IResourceLoadReserver* resource)
{	

	resource->ReserveLoad(Asset::Texture::UI_CHAR_SELECT_BACK_GROUND);


	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK_NOT);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK2);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK3);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK4);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK_CP);
	resource->ReserveLoad(Asset::Texture::UI_CHAR_BACK_CP_RANDOM);

	resource->ReserveLoad(Asset::Texture::UI_NEKO);
	resource->ReserveLoad(Asset::Texture::UI_USAGI);
	resource->ReserveLoad(Asset::Texture::UI_KAERU);
	resource->ReserveLoad(Asset::Texture::UI_UMA);

	resource->ReserveLoad(Asset::Texture::UI_CURSOR);

	resource->ReserveLoad(Asset::Texture::UI_1P);
	resource->ReserveLoad(Asset::Texture::UI_2P);
	resource->ReserveLoad(Asset::Texture::UI_3P);
	resource->ReserveLoad(Asset::Texture::UI_4P);
}

void CharaSelectScene::OnSetup()
{
	const float kPlayerDisplayPosY = Director::GetInstance()->GetScreenHeight() / 4+0.5;
	const float kPlayerDisplayPosX = Director::GetInstance()->GetScreenWidth() / 4+0.5;

	charselect_var = new CharactorSelectSceneVariable;

	camera_ = new Camera2D();
	AddCamera(camera_);

	img_[IMG_BACKGROUND] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_SELECT_BACK_GROUND);
	img_[IMG_CHARACTOR_BACKGROUND_NOT] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK_NOT);
	img_[IMG_CHARACTOR_BACKGROUND] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK);
	img_[IMG_CHARACTOR_BACKGROUND2] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK2);
	img_[IMG_CHARACTOR_BACKGROUND3] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK3);
	img_[IMG_CHARACTOR_BACKGROUND4] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK4);
	img_[IMG_CHARACTOR_BACKGROUND_CP] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK_CP);
	img_[IMG_CHARACTOR_BACKGROUND_CP_RANDOM] = Sprite::CreateWithResource(Asset::Texture::UI_CHAR_BACK_CP_RANDOM);
	img_[IMG_1P] = Sprite::CreateWithResource(Asset::Texture::UI_1P);
	img_[IMG_2P] = Sprite::CreateWithResource(Asset::Texture::UI_2P);
	img_[IMG_3P] = Sprite::CreateWithResource(Asset::Texture::UI_3P);
	img_[IMG_4P] = Sprite::CreateWithResource(Asset::Texture::UI_4P);
	img_[IMG_CHARACTER_CAT] = Sprite::CreateWithResource(Asset::Texture::UI_NEKO);
	img_[IMG_CHARACTER_RABIT] = Sprite::CreateWithResource(Asset::Texture::UI_USAGI);
	img_[IMG_CHARACTER_FROG] = Sprite::CreateWithResource(Asset::Texture::UI_KAERU);
	img_[IMG_CHARACTER_HOURSE] = Sprite::CreateWithResource(Asset::Texture::UI_UMA);

	//Init charactor background img
	for (int i= 0; i<11 ; ++i) {
		img_[IMG_CHARACTOR_BACKGROUND_NOT+i]->GetTransform()->SetScale(kCharactorBackGroundScale);
	}


	img_[IMG_BACKGROUND]->GetTransform()->SetScale(1.4);
	AddChild(img_[IMG_BACKGROUND]);

	const float base_icon_pos_y = Director::GetInstance()->GetScreenHeight()/3;
	const float gap_size = 160;
	for (int i = 0; i < kMaxCharactor; ++i)
	{
		//キャラクターを選ぶ時のアイコン表示
		img_[IMG_ICON_CAT+i] = AnimalTable::GetInstance().GetData(i)->CreateIcon();
		img_[IMG_ICON_CAT+i]->GetTransform()->SetScale(0.2);
		charselect_var->select_icon_pos_y[i] = base_icon_pos_y - (i*gap_size);
		img_[IMG_ICON_CAT+i]->GetTransform()->SetPositon(0,charselect_var->select_icon_pos_y[i]);
		AddChild(img_[IMG_ICON_CAT+i]);

		img_[IMG_PLAYER_ICON_CAT+i] = AnimalTable::GetInstance().GetData(i)->CreateIcon();
		img_[IMG_PLAYER_ICON_CAT+i]->GetTransform()->SetPositon(kCharactorIconPosX,kCharactorIconPosY);
		img_[IMG_PLAYER_ICON_CAT+i]->GetTransform()->SetScale(kCharactorIconScale);
	}

	charactor_display_ = new CharactorDisplay[kMaxPlayer];

	for (int i=0 ; i<kMaxPlayer ; ++i)
	{
		charactor_display_[i].charactor_icon = img_[IMG_PLAYER_ICON_CAT];
		//charactor_display_[i].model = AnimalTable::GetInstance().GetData(i)->CreateModel();

		charactor_display_[i].back_ground = img_[IMG_CHARACTOR_BACKGROUND_NOT];

		charactor_display_[i].SetDisplayPos(kPlayerDisplayPosX*kPosIndex[i*2],kPlayerDisplayPosY*kPosIndex[i*2+1]);

		charactor_display_[i].empty_parent.AddChild(charactor_display_[i].back_ground);
		//charactor_display_[i].empty_parent.AddChild(charactor_display_[i].charactor_icon);
		//charactor_display_[i].empty_parent_3d.AddChild(charactor_display_[i].model);
		AddChild(&charactor_display_[i].empty_parent);
		//AddChild(&charactor_display_[i].empty_parent_3d);

		//charactor_display_[i].model->GetTransform()->SetPosition(kPlayerDisplayPosX*kPosIndex[i*2],0,kPlayerDisplayPosY*kPosIndex[i*2+1]);
		//AddChild(charactor_display_[i].model);

		img_[IMG_1P+i]->GetTransform()->SetPositon(kNumX * kPosIndex[i*2], kNumY * kPosIndex[i*2+1] + charselect_var->select_icon_pos_y[0]);
		img_[IMG_1P+i]->GetTransform()->SetScale(0.02);
		AddChild(img_[IMG_1P+i]);
		img_[IMG_1P+i]->SetVisible(false);
	}
	for (int i = 0; i < kMaxPlayer; ++i) {
		//カーソル表示
		img_[IMG_CURSOR + i] = Sprite::CreateWithResource(Asset::Texture::UI_CURSOR);
		img_[IMG_CURSOR + i]->GetTransform()->SetScale(0.08);
		img_[IMG_CURSOR + i]->GetTransform()->SetPositon(kPlayerDisplayPosX*kPosIndex[i*2],kPlayerDisplayPosY*kPosIndex[i*2+1]);
		AddChild(img_[IMG_CURSOR + i]);
	}

	//Cursor color
	img_[IMG_CURSOR]->GetMaterial()->SetDiffuse(Color4F(1.0,0.6,0.6));
	img_[IMG_CURSOR2]->GetMaterial()->SetDiffuse(Color4F(0.6,0.6,1.0));
	img_[IMG_CURSOR3]->GetMaterial()->SetDiffuse(Color4F(1.0,1.0,0.6));
	img_[IMG_CURSOR4]->GetMaterial()->SetDiffuse(Color4F(0.6,1.0,0.6));




}

void CharaSelectScene::OnUnload()
{
	//for (int i = 0; i < MOD_MAX; ++i) {
	//	if (modifier_[i])modifier_[i]->Release();
	//}
	delete[] charactor_display_;

	for (int i = 0; i < IMG_MAX; ++i) {
		delete img_[i];
	}

	delete camera_;

	delete charselect_var;
}

void CharaSelectScene::OnShow(ISceneShowListener* listener)
{  

}

void CharaSelectScene::OnHide(ISceneHideListener* listener)
{
}

void CharaSelectScene::Update()
{	



	const float kCoursorSpeed = 5;
	const float icon_r = 60;
	const float disp_r = 80;

	int player_count = 0;
	int computer_count = 0;

	//コントローラー操作
	for(int i=0 ; i<kMaxPlayer ; ++i)
	{
		//キャラクター選択
		TVec2f coursor_pos = img_[IMG_CURSOR+i]->GetTransform()->GetPosition();
		coursor_pos.x += HalEngine::Input(i)->GetAxis(GameInput::X_AXIS)*kCoursorSpeed;
		coursor_pos.y += HalEngine::Input(i)->GetAxis(GameInput::Y_AXIS)*kCoursorSpeed;
		img_[IMG_CURSOR+i]->GetTransform()->SetPositon(coursor_pos.x,coursor_pos.y);
		for(int j=0 ; j<4 ; ++j)
		{
			TVec2f icon_pos = img_[IMG_ICON_CAT+j]->GetTransform()->GetPosition();
			float x = coursor_pos.x - icon_pos.x;
			float y = coursor_pos.y - icon_pos.y;
			if (x*x + y*y <= icon_r*icon_r) 
			{
				if (HalEngine::Input(i)->GetButtonDown(GameInput::ACCEL)) 
				{
					if (charactor_display_[i].player_type>-1 && charactor_display_[i].player_type == j && !charactor_display_[i].cp)
					{
						if (i==3 || charactor_display_[i+1].player_type==-1 || charactor_display_[i+1].cp) {//自分より後のプレイヤーが存在したら抜けられない。
							charactor_display_[i].player_type = -1;
							charactor_display_[i].cp = false;
						}
					}
					else
					{
						if (i==0 || charactor_display_[i-1].player_type>-1 && !charactor_display_[i-1].cp)//自分より前のプレイヤーが存在すれば参加できる。
						{
							charactor_display_[i].player_type = j;
							img_[IMG_1P + i]->GetTransform()->SetPositon(kNumX * kPosIndex[i * 2], kNumY * kPosIndex[i * 2 + 1] + charselect_var->select_icon_pos_y[j]);
							charactor_display_[i].cp = false;
						}
					}
					//charactor_display_[i].charactor_icon = img_[IMG_PLAYER_ICON_CAT+j];
					//charactor_display_[i].empty_parent.AddChild(charactor_display_[i].charactor_icon);
				}
			}
		}//EOキャラクター選択
		
		//コンピューターにしたりする
		const float kPlayerDisplayPosY = Director::GetInstance()->GetScreenHeight() / 4 + 0.5;
		const float kPlayerDisplayPosX = Director::GetInstance()->GetScreenWidth() / 4 + 0.5;
		for (int k = 0; k < 4; ++k)
		{
			float x = coursor_pos.x - kPlayerDisplayPosX*kPosIndex[k * 2];
			float y = coursor_pos.y - kPlayerDisplayPosY*kPosIndex[k * 2 + 1];
			if (x*x + y*y <= disp_r*disp_r)
			{
				if (HalEngine::Input(i)->GetButtonDown(GameInput::ACCEL))
				{
					if(!charactor_display_[k].cp)//コンピューター以外
					{
						if (
									charactor_display_[k].player_type == -1//キャラクタ選択されてない。
							||	k == 3 //4Pである
							||	charactor_display_[k + 1].player_type == -1 //次のキャラクタが選択されていない。
							||	charactor_display_[k + 1].cp//次のキャラクタがCP
							)
						{
							charactor_display_[k].cp = true;
						}
					}
					else if (charactor_display_[k].cp && charactor_display_[k].player_type<3)
					{
						++charactor_display_[k].player_type;
					}
					else
					{
						charactor_display_[k].cp = false;
						charactor_display_[k].player_type = -1;
					}
				}
			}
		}
	}//EOコントローラー操作


	//Update charactoer background
	for (int i = 0; i < kMaxPlayer; ++i)
	{
		switch (charactor_display_[i].player_type)
		{
			case -1: {
				img_[IMG_1P+i]->SetVisible(false);
				charactor_display_[i].charactor_img = nullptr;
				if (charactor_display_[i].cp)
				{
					charactor_display_[i].back_ground = img_[IMG_CHARACTOR_BACKGROUND_CP_RANDOM];
				}
				else
				{
					charactor_display_[i].back_ground = img_[IMG_CHARACTOR_BACKGROUND_NOT];
				}
				break;
			}
			default: {
				charactor_display_[i].charactor_img = img_[IMG_CHARACTER_CAT + charactor_display_[i].player_type];
				if (charactor_display_[i].cp)
				{
					img_[IMG_1P+i]->SetVisible(false);
					charactor_display_[i].back_ground = img_[IMG_CHARACTOR_BACKGROUND_CP];
				}
				else
				{
					img_[IMG_1P+i]->SetVisible(true);
					charactor_display_[i].back_ground = img_[IMG_CHARACTOR_BACKGROUND + i];
				}
			}
		}

		charactor_display_[i].empty_parent.ClearChildren();
		charactor_display_[i].empty_parent.AddChild(charactor_display_[i].back_ground);
		if(charactor_display_[i].charactor_img)charactor_display_[i].empty_parent.AddChild(charactor_display_[i].charactor_img);
	}

	for (int i=0 ; i<kMaxPlayer ; ++i)
	{
		if (charactor_display_[i].player_type>-1) {
			if (charactor_display_[i].cp)
			{
				++computer_count;
			}
			else
			{
				++player_count;
			}
		}
	}

	//プレイヤーの参加状況を決める
  //計9人まで対応(意味無し)
  PlayerEntryList* entries = new PlayerEntryList(player_count+computer_count);

	for (T_UINT8 i = 0; i < player_count; ++i)
	{
    PlayerEntry* entry = entries->AddEntry(PlayerEntry::PLAYER_ENTRY_PLAYER);
    entry->animal_data = AnimalTable::GetInstance().GetData(charactor_display_[i].player_type);
    entry->vehicle_data = VehicleTable::GetInstance().GetData(0);
	}
  for (T_UINT8 i = player_count; i < player_count+computer_count; ++i)
  {
		if(charactor_display_[i].player_type==-1)continue;
    PlayerEntry* entry = entries->AddEntry(PlayerEntry::PLAYER_ENTRY_COMPUTER);
    entry->animal_data = AnimalTable::GetInstance().GetData(charactor_display_[i].player_type);
    entry->vehicle_data = VehicleTable::GetInstance().GetData(0);
  }
  
  //これらの設定を決める過程をプログラム内で行っているが、
  //実際にはゲーム開始までに至る画面でプレイヤー側がある程度設定できるようにするといい
  //（プレイヤーやＣＰＵの人数、ステージの広さなど）

  //実行するシーン、キャラクターの参加状況、ゲームの設定をGameDirectorに渡し、ゲーム開始
	if (HalEngine::Input(0)->GetButtonDown(GameInput::START)||HalEngine::Input(0)->GetButtonDown(GameInput::LOCKON))
	{
		GameDirector::GameStart(new GameScene(), new ResultScene(), entries);
	}
}
