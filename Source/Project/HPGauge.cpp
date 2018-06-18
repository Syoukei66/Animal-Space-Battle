#include "HPGauge.h"
#include "GameDirector.h"
#include "GameSceneVisualParam.h"
#include "Player.h"

HPGauge::HPGauge(Player* player)
{
  T_UINT8 id = player->GetID();
  if (id == 0)
  {
    this->player_id_ = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_1P);
  }
  else if (id == 1)
  {
    this->player_id_ = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_2P);
  }
  else if (id == 2)
  {
    this->player_id_ = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_3P);
  }
  else if (id == 3)
  {
    this->player_id_ = Sprite::CreateWithResource(Asset::Texture::UI_PLAYER_4P);
  }
  else
  {
    this->player_id_ = nullptr;
  }

  this->icon_frame_ = Sprite::CreateWithResource(Asset::Texture::UI_GAME_ANIMAL_ICON_BG);
  this->icon_ = player->GetStatus().GetAnimalData()->CreateIcon();
  this->gauge_frame_ = Sprite::CreateWithResource(Asset::Texture::UI_GAME_HP_GAUGE_FRAME);
  this->gauge_ = new Gauge(Asset::Texture::UI_GAME_HP_GAUGE);

  this->rank_ = Sprite::Create();
  this->rank_->SetTextureRegion(new TextureRegion(), true);

  this->vehicle_icon_ = Sprite::Create();
  this->vehicle_icon_->SetTextureRegion(new TextureRegion(), true);
  this->vehicle_icon_frame_ = Sprite::CreateWithResource(Asset::Texture::UI_GAME_VEHICLE_ICON_BG);

  this->score_ = new NumberView(8);
  this->score_->SetDuration(6);

  this->rank_textures_[0] = Asset::Texture::UI_GAME_RANK_RANK1.GetContents();
  this->rank_textures_[1] = Asset::Texture::UI_GAME_RANK_RANK2.GetContents();
  this->rank_textures_[2] = Asset::Texture::UI_GAME_RANK_RANK3.GetContents();
  this->rank_textures_[3] = Asset::Texture::UI_GAME_RANK_RANK4.GetContents();

  this->AddChild(this->gauge_frame_);
  this->AddChild(this->gauge_);
  this->AddChild(this->icon_frame_);
  this->AddChild(this->icon_);

  this->AddChild(this->rank_);

  this->AddChild(this->vehicle_icon_frame_);
  this->AddChild(this->vehicle_icon_);

  this->AddChild(this->score_);

  if (this->player_id_)
  {
    this->AddChild(this->player_id_);
  }
}

HPGauge::~HPGauge()
{
  delete this->score_;
  delete this->vehicle_icon_frame_;
  delete this->vehicle_icon_;
  delete this->rank_;
  delete this->gauge_;
  delete this->gauge_frame_;
  delete this->icon_;
  delete this->icon_frame_;
  delete this->player_id_;
}

void HPGauge::DesignUpdate(T_FLOAT width, T_FLOAT height)
{
  if (GameSceneVisualParam::GetInstance().IsHpGaugeParamsDirty())
  {
    const GameSceneVisualParam& param = GameSceneVisualParam::GetInstance();

    TAreaf icon_bg_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::ANIMAL_ICON_FRAME).ConvertSize(width, height, &icon_bg_area);
    this->icon_frame_->GetTransform()->SetPositon(icon_bg_area.pos);
    this->icon_frame_->SetSize(icon_bg_area.size);

    TAreaf icon_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::ICON).ConvertSize(width, height, &icon_area);
    this->icon_->GetTransform()->SetPositon(icon_area.pos);
    this->icon_->SetSize(icon_area.size);

    TAreaf gauge_bg_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::GAUGE_FRAME).ConvertSize(width, height, &gauge_bg_area);
    this->gauge_frame_->GetTransform()->SetPositon(gauge_bg_area.pos);
    this->gauge_frame_->SetSize(gauge_bg_area.size);

    TAreaf gauge_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::GAUGE).ConvertSize(width, height, &gauge_area);
    this->gauge_->GetTransform()->SetPositon(gauge_area.pos);
    this->gauge_->SetSize(gauge_area.size.width, gauge_area.size.height);

    this->rank_->FitToTexture();
    TAreaf rank_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::RANK).ConvertSize(width, height, &rank_area);
    this->rank_->GetTransform()->SetPositon(rank_area.pos);
    this->rank_->SetSize(rank_area.size.width, rank_area.size.height);

    this->vehicle_icon_->FitToTexture();
    TAreaf vehicle_icon_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::VEHICLE_ICON).ConvertSize(width, height, &vehicle_icon_area);
    this->vehicle_icon_->GetTransform()->SetPositon(vehicle_icon_area.pos);
    this->vehicle_icon_->SetSize(vehicle_icon_area.size.width, vehicle_icon_area.size.height);

    TAreaf vehicle_icon_frame_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::VEHICLE_ICON_FRAME).ConvertSize(width, height, &vehicle_icon_frame_area);
    this->vehicle_icon_frame_->GetTransform()->SetPositon(vehicle_icon_frame_area.pos);
    this->vehicle_icon_frame_->SetSize(vehicle_icon_frame_area.size.width, vehicle_icon_frame_area.size.height);

    TAreaf score_area = TAreaf();
    param.GetHpGaugeParam(DesignEntity::SCORE).ConvertSize(width, height, &score_area);
    this->score_->GetTransform()->SetPositon(score_area.pos);
    this->score_->SetSize(score_area.size.width, score_area.size.height);

    if (this->player_id_)
    {
      T_FLOAT size = std::min(width, height) * 0.08f;
      this->player_id_->GetTransform()->SetPositon(this->icon_->GetTransform()->GetPosition());
      this->player_id_->GetTransform()->SetY(this->player_id_->GetTransform()->GetY() - height * 0.1f);
      this->player_id_->SetSize(size * 1.5f, size);
    }
  }
}

void HPGauge::SetAllLayerId(T_UINT8 id)
{
  this->gauge_->SetAllLayerId(id);
  this->gauge_frame_->SetLayerId(id);
  this->icon_->SetLayerId(id);
  this->icon_frame_->SetLayerId(id);
  this->rank_->SetLayerId(id);
  this->vehicle_icon_->SetLayerId(id);
  this->vehicle_icon_frame_->SetLayerId(id);
  this->score_->SetAllLayerId(id);
  if (this->player_id_)
  {
    this->player_id_->SetLayerId(id);
  }
}

void HPGauge::UpdateStatus(Player* player)
{
  this->gauge_->SetMaxValue(player->GetMaxHp());
  this->gauge_->SetValue(player->GetHp());

  this->score_->SetValue(player->GetResult()->point);

  const VehicleData* vehicle = player->GetStatus().GetVehcileData();
  this->vehicle_icon_->SetEnabled(vehicle);
  if (vehicle)
  {
    this->vehicle_icon_->SetTexture(player->GetStatus().GetVehcileData()->GetIconTexture());
  }

  T_INT8 rank = GameDirector::GetPlayerResultList()->GetResultById(player->GetID())->rank;
  if (rank == -1)
  {
    this->rank_->SetVisible(false);
  }
  else
  {
    this->rank_->SetVisible(true);
    this->rank_->SetTexture(this->rank_textures_[rank]);
  }
}
