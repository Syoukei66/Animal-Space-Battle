#pragma once

#include <HalEngine.h>


class CharaSelectScene : public Scene
{
public:
	virtual void OnLoad(IResourceLoadReserver* resource) override;
	virtual void OnSetup() override;
	virtual void OnUnload() override;
	virtual void OnShow(ISceneShowListener* listener) override;
	virtual void OnHide(ISceneHideListener* listener) override;

private:
	void Update() override;

	Camera2D* camera_;

	typedef enum {
		IMG_BACKGROUND,

		IMG_CHARACTOR_BACKGROUND_NOT,
		IMG_CHARACTOR_BACKGROUND,
		IMG_CHARACTOR_BACKGROUND2,
		IMG_CHARACTOR_BACKGROUND3,
		IMG_CHARACTOR_BACKGROUND4,
		IMG_CHARACTOR_BACKGROUND_CP,
		IMG_CHARACTOR_BACKGROUND_CP_RANDOM,

		IMG_CHARACTER_CAT,
		IMG_CHARACTER_RABIT,
		IMG_CHARACTER_FROG,
		IMG_CHARACTER_HOURSE,

		IMG_ICON_CAT,
		IMG_ICON_RABIT,
		IMG_ICON_FROG,
		IMG_ICON_HOURSE,

		IMG_PLAYER_ICON_CAT,
		IMG_PLAYER_ICON_RABIT,
		IMG_PLAYER_ICON_FROG,
		IMG_PLAYER_ICON_HOURSE,

		IMG_CURSOR,
		IMG_CURSOR2,
		IMG_CURSOR3,
		IMG_CURSOR4,

		IMG_1P,
		IMG_2P,
		IMG_3P,
		IMG_4P,

		IMG_MAX
	} Img;
	Sprite* img_[IMG_MAX];

	struct CharactorDisplay
	{
		int player_type;
		bool cp;
		Sprite* back_ground;
		Sprite* charactor_icon;
		Sprite* charactor_img;

		GameObject2D empty_parent;
		//GameObject3D empty_parent_3d;

		void SetDisplayPos(float x, float y) {
			empty_parent.GetTransform()->SetPositon(x, y);
			//empty_parent_3d.GetTransform()->SetPosition(x,0,y);
		}
		CharactorDisplay()
			: player_type(-1)
			, cp(false)
		{}

	};

	CharactorDisplay *charactor_display_;
};