#include "BulletEmitter_Way.h"

static const T_UINT8 BULLET_COUNT = 3;
static const T_UINT8 DELAY = 30;
static const T_UINT16 LIFE_TIME = 100;
static const T_UINT16 BULLET_MAX = BULLET_COUNT * (T_UINT16)(ceilf((T_FLOAT)LIFE_TIME / (DELAY + 1) + 0.5f));
static const T_FLOAT VELOCITY = 3.0f;

BulletEmitter_Way::BulletEmitter_Way(T_UINT8 power, T_FLOAT length, T_FLOAT count, T_FLOAT rad, T_FLOAT emission_z, T_FLOAT distance, T_FLOAT homing_rate, T_UINT16 homing_life_time)
  : BulletEmitter(BULLET_MAX)
  , power_(power)
  , length_(length)
  , count_(count)
  , rad_(rad)
  , emission_z_(emission_z)
  , distance_(distance)
  , homing_rate_(homing_rate)
  , homing_lifetime_(homing_life_time)
{
}

BulletEmitter_Way::~BulletEmitter_Way()
{
}

T_UINT32 BulletEmitter_Way::EmissionProcess()
{
  Player* player = this->GetPlayer();
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();

  // プレイヤーの絶対空間での向きを取得
  // WorldMatrixから現在の向きを基準としたX/Y/Z軸ベクトルを取得できる
  const TVec3f xVec = player->GetTransform()->GetWorldMatrix().GetCameraXVec();
  const TVec3f yVec = player->GetTransform()->GetWorldMatrix().GetCameraYVec();
  const TVec3f zVec = player->GetTransform()->GetWorldMatrix().GetCameraZVec();

  const T_FLOAT x = this->length_ * sinf(this->rad_);
  const T_FLOAT y = this->length_ * cosf(this->rad_);
  const T_FLOAT z = this->emission_z_;

  const TVec3f v = xVec * x + yVec * y;

  const TVec3f d = v / this->count_;

  const TVec3f offset = player_pos - d * (this->count_ - 1) * 0.5f + zVec * z;

  for (T_UINT8 i = 0; i < this->count_; ++i)
  {
    Bullet* b = this->Allocate();
    if (!b)
    {
      return DELAY;
    }

    b->SetPower(this->power_);

    const TVec3f bullet_pos = offset + d * i;
    b->GetTransform()->SetPosition(bullet_pos);

    const TVec3f target_point = player_pos + zVec * this->distance_;
    b->SetVector((target_point - bullet_pos).Normalized());
    b->SetSpeed(VELOCITY);
    b->SetHomingRate(this->homing_rate_);
    b->SetHomingLifeTime(this->homing_lifetime_);

    b->GetTransform()->SetScale(0.5f);

    b->SetLifeTime(LIFE_TIME);
  }

  Asset::Sound::SHOT_SHOT_WAY.Play();
  return DELAY;
}

void BulletEmitter_Way::UpdateProcess()
{
}
