#pragma once

#include <vector>
#include <HalEngine.h>



class TitleScene : public Scene
{
public:
  virtual void OnLoad(IResourceLoadReserver* order) override;
  virtual void OnSetup();
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;

public:
	void Update() override;

private:
	Camera2D* camera_;

	struct Star{
		Sprite* img;
		EntityModifierRoot* modifier;
		float speed;
		~Star() {
			delete img;
			if(modifier)modifier->Release();
		}
	};
	Star* star_;

	typedef enum {
		IMG_TITLE,
		IMG_CHARACTOR,
		IMG_PRESS_X_BUTTON,
		IMG_GAME,
		IMG_SETTING,
		IMG_CREDIT,
		IMG_MINNADE,
		IMG_HITORIDE,

		IMG_MAX
	} Img;
	Sprite* img_[IMG_MAX];

	typedef enum {
		MOD_TITLE,
		MOD_TITLE_ROTATE,
		MOD_CHARACTOR,
		MOD_CHARACTOR_ENTRY,
		MOD_ZENTAI,
		MOD_START_TENMETU,
		MOD_GAME_TENMETU,
		MOD_SETTING_TENMETU,
		MOD_CREDIT_TENMETU,
		MOD_SELECT_MODE_IN,

		MOD_MAX
	} Modifier;
	EntityModifierRoot* modifier_[MOD_MAX];

	GameObject2D mode_select_;
};