#include "TitleScene.h"

#include "GameDirector.h"
#include "GameInput.h"
#include "CharaSelectScene.h"


static const int		kStarNum =						50;
static const float	kStarScaleMin =				0.05f;
static const float	kStarScaleMax =				0.3f;
static const float	kStarSpeedMin =				0.1f;
static const float	kStarSpeedMax =				0.4f;

static const float  kModeTextScaleMin =		0.1f;
static const float  kModeTextScaleMax =		0.13f;

struct TitleVariable 
{
	bool entried;
	bool rotated;
	int cnt;
	int mode;
	TitleVariable()
		: entried(false)
		, rotated(false)
		, cnt(0)
		, mode(-1)
	{}
};

static TitleVariable *title_var;



static EntityModifierRoot* CreateSindouModifier()
{
	const T_UINT8 duration = 3;
	const T_FLOAT yure = 4.0f;
	const TVec2f gra0 = TVec2f(1.0f, 1.0f) * yure;
	const TVec2f gra1 = TVec2f(-1.0f, -1.0f) * yure;
	const TVec2f gra2 = TVec2f(2.0f, 1.0f) * yure;
	const TVec2f gra3 = TVec2f(0.0f, 0.0f) * yure;
	EntityModifier* m0 = EntityModifierFactory::ScaleFromTo(5, 3.0f, 1.0f);
	m0->SetEasingFunction(EasingFunction::FK_EXPONENTIAL, EasingFunction::EASE_IN);
	EntityModifier* m10 = EntityModifierFactory::TranslateFromTo(duration, gra0, gra1);
	EntityModifier* m11 = EntityModifierFactory::TranslateFromTo(duration, gra1, gra2);
	EntityModifier* m12 = EntityModifierFactory::TranslateFromTo(duration, gra2, gra3);
	EntityModifier* m1 = EntityModifierFactory::Sequence(m0, m10, m11, m12);
	EntityModifierRoot* ret = EntityModifierFactory::Root(m1);
	ret->Retain();
	ret->Stop();
	return ret;
}
static EntityModifierRoot* CreateTenmetuModifier(T_UINT32 duraition ,float brightness) {
	EntityModifier* m00 = EntityModifierFactory::ColorFromTo(duraition, Color4F(brightness, brightness, brightness, 1.0f), Color4F::WHITE);
	EntityModifier* m01 = EntityModifierFactory::Round(m00);
	m01->SetEasingFunction(EasingFunction::FK_CIRCULAR, EasingFunction::EASE_IN_OUT);
	EntityModifierRoot* ret = EntityModifierFactory::Root(m01);
	ret->Retain();
	ret->SetLoop(true);
	return ret;
}

EntityModifier* CharactorEntry(float char_x,float char_y) {
	EntityModifier* m0 = EntityModifierFactory::TranslateFromToX(40, Director::GetInstance()->GetScreenWidth()*0.6,char_x);
	EntityModifier* m1 = EntityModifierFactory::TranslateFromToY(40, Director::GetInstance()->GetScreenHeight()*0.3, char_y);
	EntityModifier* m2 = EntityModifierFactory::Synchronized(m0, m1);
	m2->SetEasingFunction(EasingFunction::FK_CUBIC, EasingFunction::EASE_IN_OUT);
	return m2;
}
EntityModifier* Rotation() {
	EntityModifier* m0 = EntityModifierFactory::RotationTo(120,MathConstants::PI*2);
	return m0;
}


void TitleScene::OnLoad(IResourceLoadReserver* resource)
{
	resource->ReserveLoad(Asset::Texture::UI_TITLE);
	resource->ReserveLoad(Asset::Texture::UI_TITLE_CHARACTOR);
	resource->ReserveLoad(Asset::Texture::UI_TITLE_MESSAGE);
	resource->ReserveLoad(Asset::Texture::TEST_BULLET);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_PRESSXBUTTON);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_GAME);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_SETTING);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_CREDIT);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_MINNA);
	resource->ReserveLoad(Asset::Texture::UI_TEXT_HITORI);
}
void TitleScene::OnSetup()
{
	title_var = new TitleVariable;

	int screen_width = Director::GetInstance()->GetScreenWidth();
	int screen_height = Director::GetInstance()->GetScreenHeight();

	camera_ = new Camera2D();
	AddCamera(camera_);

	img_[IMG_TITLE] =						Sprite::CreateWithResource(Asset::Texture::UI_TITLE);
	img_[IMG_CHARACTOR] =				Sprite::CreateWithResource(Asset::Texture::UI_TITLE_CHARACTOR); 
	img_[IMG_PRESS_X_BUTTON] =	Sprite::CreateWithResource(Asset::Texture::UI_TEXT_PRESSXBUTTON);
	img_[IMG_GAME] =						Sprite::CreateWithResource(Asset::Texture::UI_TEXT_GAME);
	img_[IMG_SETTING] =					Sprite::CreateWithResource(Asset::Texture::UI_TEXT_SETTING);
	img_[IMG_CREDIT] =					Sprite::CreateWithResource(Asset::Texture::UI_TEXT_CREDIT);
	img_[IMG_HITORIDE] =				Sprite::CreateWithResource(Asset::Texture::UI_TEXT_HITORI);
	img_[IMG_MINNADE] =					Sprite::CreateWithResource(Asset::Texture::UI_TEXT_MINNA);

	EntityModifier* m0[kStarNum];
	EntityModifier* m1[kStarNum];
	EntityModifier* m2[kStarNum];
	EntityModifier* m3[kStarNum];

	star_ = new Star[kStarNum];
	for(int i = 0 ; i<kStarNum ; i++)
	{
		star_[i].img = Sprite::CreateWithResource(Asset::Texture::TEST_BULLET);
		AddChild(star_[i].img);

		star_[i].speed = Util::GetRandom(kStarSpeedMin, kStarSpeedMax);
		star_[i].img->GetTransform()->SetScale(Util::GetRandom(kStarScaleMin, kStarScaleMax));

		int x = rand()%screen_width-screen_width/2;
		int y = rand()%screen_height-screen_height/2;

		star_[i].img->GetTransform()->
			SetPositon(x,y);

		m0[i] = EntityModifierFactory::ColorToBlue(20, 0.5f );
		m1[i] = EntityModifierFactory::ColorToRed(20, 0.5f );
		m2[i] = EntityModifierFactory::Synchronized(m0[i], m1[i]);
		m3[i] = EntityModifierFactory::Loop(m2[i], 100);
		star_[i].modifier = EntityModifierFactory::Root(m3[i]);
		star_[i].modifier->Retain();

		star_[i].img->RegisterEntityModifier(star_[i].modifier);

	}
	AddChild(img_[IMG_CHARACTOR]);

	img_[IMG_TITLE]->GetTransform()->SetPositon((screen_width/5)*-1,(screen_height/5));
	img_[IMG_TITLE]->GetTransform()->SetScale(0.8);

	float char_x = (screen_width/4);
	float char_y = (screen_height/7)*-1;
	img_[IMG_CHARACTOR]->GetTransform()->SetPositon(char_x,char_y);
	img_[IMG_CHARACTOR]->GetTransform()->SetScale(0.5);


	img_[IMG_PRESS_X_BUTTON]->GetTransform()->SetPositon(0,(screen_height/3)*-1);
	img_[IMG_PRESS_X_BUTTON]->GetTransform()->SetScale(0.1);


	//タイトル点滅
	modifier_[MOD_TITLE] = CreateTenmetuModifier(60,0.6);
	img_[IMG_TITLE]->RegisterEntityModifier(modifier_[MOD_TITLE]);


	//タイトル回転
	modifier_[MOD_TITLE_ROTATE] = EntityModifierFactory::Root(Rotation());
	modifier_[MOD_TITLE_ROTATE]->Stop();
	modifier_[MOD_TITLE_ROTATE]->Retain();
	img_[IMG_TITLE]->RegisterEntityModifier(modifier_[MOD_TITLE_ROTATE]);


	EntityModifier* m21 = CharactorEntry(char_x,char_y);
	modifier_[MOD_CHARACTOR_ENTRY] = EntityModifierFactory::Root(m21);
	modifier_[MOD_CHARACTOR_ENTRY]->Retain();
	img_[IMG_CHARACTOR]->RegisterEntityModifier(modifier_[MOD_CHARACTOR_ENTRY]);

	EntityModifier* m10 = EntityModifierFactory::TranslateFromToX(180, char_x, screen_width*-0.6);
	EntityModifier* m11 = EntityModifierFactory::TranslateFromToY(180, char_y, screen_height*-0.5);
	EntityModifier* m12 = EntityModifierFactory::Synchronized(m10, m11);

	EntityModifier* m13 = CharactorEntry(char_x,char_y);

	EntityModifier* m14 = EntityModifierFactory::Sequence(m12, m13);
	modifier_[MOD_CHARACTOR] = EntityModifierFactory::Root(m14);

	modifier_[MOD_CHARACTOR]->Stop();
	modifier_[MOD_CHARACTOR]->Retain();

	img_[IMG_CHARACTOR]->RegisterEntityModifier(modifier_[MOD_CHARACTOR]);

	this->modifier_[MOD_ZENTAI] = CreateSindouModifier();
	this->GetRoot2d()->RegisterEntityModifier(this->modifier_[MOD_ZENTAI]);


	//終了フラグ処理
	modifier_[MOD_CHARACTOR_ENTRY]->AddEntityModifierListener([&]() {
		title_var->entried = true;
	});
	modifier_[MOD_CHARACTOR_ENTRY]->AddEntityModifierListener([&]() {
		title_var->rotated = true;
	});

	//PressXButton点滅
	modifier_[MOD_START_TENMETU] = CreateTenmetuModifier(20,0.3);
	img_[IMG_PRESS_X_BUTTON]->RegisterEntityModifier(modifier_[MOD_START_TENMETU]);


	//===ModeSelect=========
	img_[IMG_GAME]->GetTransform()->SetPositon((screen_width/4),0);
	img_[IMG_SETTING]->GetTransform()->SetPositon((screen_width/4),-130);
	img_[IMG_CREDIT]->GetTransform()->SetPositon((screen_width/4),-250);
	img_[IMG_GAME]->GetTransform()->SetScale(kModeTextScaleMax);
	img_[IMG_SETTING]->GetTransform()->SetScale(kModeTextScaleMin);
	img_[IMG_CREDIT]->GetTransform()->SetScale(kModeTextScaleMin);

	mode_select_.AddChild(img_[IMG_GAME]);
	mode_select_.AddChild(img_[IMG_SETTING]);
	mode_select_.AddChild(img_[IMG_CREDIT]);
	AddChild(&mode_select_);

	mode_select_.GetTransform()->SetPositon(500,0);
	EntityModifier* selectin0 = EntityModifierFactory::TranslateFromToX(15, 500,0);
	modifier_[MOD_SELECT_MODE_IN] = EntityModifierFactory::Root(selectin0);
	mode_select_.RegisterEntityModifier(modifier_[MOD_SELECT_MODE_IN]);

	modifier_[MOD_SELECT_MODE_IN]->Retain();
	modifier_[MOD_SELECT_MODE_IN]->Stop();


	modifier_[MOD_GAME_TENMETU] = CreateTenmetuModifier(5,0.7);
	img_[IMG_GAME]->RegisterEntityModifier(modifier_[MOD_GAME_TENMETU]);
	modifier_[MOD_SETTING_TENMETU] = CreateTenmetuModifier(5,0.7);
	modifier_[MOD_SETTING_TENMETU]->Stop();
	img_[IMG_SETTING]->RegisterEntityModifier(modifier_[MOD_SETTING_TENMETU]);
	modifier_[MOD_CREDIT_TENMETU] = CreateTenmetuModifier(5,0.7);
	modifier_[MOD_CREDIT_TENMETU]->Stop();
	img_[IMG_CREDIT]->RegisterEntityModifier(modifier_[MOD_CREDIT_TENMETU]);

}

void TitleScene::OnUnload()
{
	for (int i = 0; i < MOD_MAX; ++i) {
		if(modifier_[i])modifier_[i]->Release();
	}


	for (int i=0 ; i<IMG_MAX ; ++i) {
		delete img_[i];
	}

	delete[] star_;


	delete camera_;

	delete title_var;
}

void TitleScene::OnShow(ISceneShowListener* listener)
{
}

void TitleScene::OnHide(ISceneHideListener* listener)
{
}


void TitleScene::Update()
{
	static int frame_cnt = 0;
	frame_cnt++;

	if((frame_cnt == (60*5)))
		modifier_[MOD_CHARACTOR]->Play();

	static bool test_init = false;//TODO 消す
	if (HalEngine::Input(0)->GetButtonDown(GameInput::ACCEL)&&test_init)
	{
		if (title_var->mode == -1) {
			img_[IMG_PRESS_X_BUTTON]->SetVisible(false);
			modifier_[MOD_SELECT_MODE_IN]->Play();
			title_var->mode = 0;
		}
		else if (title_var->mode == 0) {
			Director::GetInstance()->ChangeScene(new CharaSelectScene());
		}
	}
	static int old_mode = title_var->mode;
	if (old_mode != title_var->mode) 
	{
		modifier_[MOD_GAME_TENMETU+old_mode]->Stop();
		img_[IMG_GAME+old_mode]->GetTransform()->SetScale(kModeTextScaleMin);
		modifier_[MOD_GAME_TENMETU+title_var->mode]->Play();
		img_[IMG_GAME+title_var->mode]->GetTransform()->SetScale(kModeTextScaleMax);
		old_mode = title_var->mode;
	}
	test_init = true;//TODO 消す

	if (title_var->entried)
	{
		title_var->entried=false;
		AddChild(img_[IMG_PRESS_X_BUTTON]);
		AddChild(img_[IMG_TITLE]);
		modifier_[MOD_TITLE_ROTATE]->Play();
		title_var->cnt = 1;
	}
	//if (HalEngine::Input(0)->GetButtonDown(GameInput::)) {
	//	title_var->mode = ((--title_var->mode)+3)%3;
	//}
	if (title_var->mode >= 0)
	{
		float axis = HalEngine::Input(0)->GetAxis(GameInput::Y_AXIS);
		static int vec = 0;
		const int nagaosi_cnt = 60;
		if (axis < 0) {
			if (vec == 0 || vec > nagaosi_cnt) {
				title_var->mode = (++title_var->mode) % 3;
				if (vec > nagaosi_cnt)vec -= 10;
			}
			++vec;
		}
		else if (axis > 0) {
			if (vec == 0 || vec > nagaosi_cnt) {
				title_var->mode = ((--title_var->mode) + 3) % 3;
				if (vec > nagaosi_cnt)vec -= 10;
			}
			++vec;
		}
		else {
			vec = 0;
		}
	}

	if(title_var->cnt)++title_var->cnt;
	if (title_var->cnt>30)
	{
		title_var->cnt =0;
		title_var->rotated = false;
		modifier_[MOD_ZENTAI]->Play();
	}

	float screen_width = Director::GetInstance()->GetScreenWidth()/2;
	float screen_height = Director::GetInstance()->GetScreenHeight()/2;
	float pos[4];
	pos[1] = (float)(screen_width)*-1-10;
	pos[3] = (float)(screen_height)*-1-10;




	//星の動き
	for (int i = 0; i < kStarNum; i++) {
		pos[0] = star_[i].img->GetTransform()->GetPosition().x + star_[i].speed;
		pos[2] = star_[i].img->GetTransform()->GetPosition().y + star_[i].speed;
		pos[0] = pos[(pos[0] > screen_width + 10)];
		pos[2] = pos[(pos[2] > screen_height + 10)+2];
		star_[i].img->GetTransform()->SetPositon(pos[0],pos[2]);
	}

#ifdef _DEBUG
	if (HalEngine::Input(0)->GetButtonDown(GameInput::BRAKE)&&test_init)
	{
		Director::GetInstance()->ChangeScene(new TitleScene());
	}
#endif
}
