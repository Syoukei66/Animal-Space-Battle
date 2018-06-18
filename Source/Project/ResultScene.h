#pragma once

#include <vector>
#include "PlayerActor.h"

class ResultScene : public Scene
{
public:
  virtual void OnLoad(IResourceLoadReserver* resource) override;
  virtual void OnSetup() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;
  
public:
  void Update() override;

private:
  bool debug_flag_;
  Camera3D_LookAt* main_camera_;
  Camera2D* camera_2d_;
  //“¯ˆê‡ˆÊ‚ª‘¶İ‚·‚éê‡‚ª‚ ‚é
  //playeres_[‡ˆÊ]‚Å‚»‚Ì‡ˆÊ‚ÌPlayer‚ÌW‡‚ğ“¾‚ê‚é
  //playeres_[‡ˆÊ].size()‚Å‚»‚Ì‡ˆÊ‚ÌPlayer‚Ì”‚ª’m‚ê‚é
	std::vector<std::vector<PlayerActor*>> playeres_;

	typedef enum {
		IMG_RANK1_KAI,
		IMG_RANK1,
		IMG_RANK2,
		IMG_RANK3,
		IMG_RANK4,
		IMG_WHITE,
		IMG_1P,
		IMG_2P,
		IMG_3P,
		IMG_4P,
		IMG_ICON,

		IMG_MAX
	} Img;
	Sprite* img_[IMG_MAX];

	typedef enum {
		MOD_WHITE,
		MOD_ICON,
		MOD_ICON2,
		MOD_ICON3,
		MOD_ICON4,

		MOD_MAX
	} Modifier;
	EntityModifierRoot* modifier_[MOD_MAX];

	struct Rank{
		Sprite *player_id;
		Sprite *junni;
	};
	Rank rank_[4];

	T_FLOAT num_[3];
	T_FLOAT num2_[3];


	int rotate_;
	int vehicle_id_;
	int number_one_num_;
	GameObject2D icon_parent_;
};