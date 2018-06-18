#include "BulletEmitter_Sandan.h"

static const T_UINT8 BULLET_COUNT = 30;
static const T_UINT16 LIFE_TIME = 60;
static const T_UINT16 BULLET_MAX = BULLET_COUNT * LIFE_TIME;
static const T_FLOAT VELOCITY = 3.0f;

BulletEmitter_Sandan::BulletEmitter_Sandan()
  : BulletEmitter(BULLET_MAX)
{
}

BulletEmitter_Sandan::~BulletEmitter_Sandan()
{
}

T_UINT32 BulletEmitter_Sandan::EmissionProcess()
{
  Player* player = this->GetPlayer();
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();

  // プレイヤーの絶対空間での向きを取得
  // WorldMatrixから現在の向きを基準としたX/Y/Z軸ベクトルを取得できる
  const TVec3f xVec = player->GetTransform()->GetWorldMatrix().GetCameraXVec();
  const TVec3f yVec = player->GetTransform()->GetWorldMatrix().GetCameraYVec();
  const TVec3f zVec = player->GetTransform()->GetWorldMatrix().GetCameraZVec();

  for (T_UINT8 i = 0; i < BULLET_COUNT; ++i)
  {
    Bullet* b = this->Allocate();
    if (!b)
    {
      return LIFE_TIME;
    }
    b->SetPower(1);

    const T_FLOAT rad = Util::GetRandom(-MathConstants::PI, MathConstants::PI);
    const T_FLOAT r = Util::GetRandom(0.0f, 0.25f);
    const T_FLOAT x = cos(rad) * r;
    const T_FLOAT y = sin(rad) * r;
    const T_FLOAT z = 1.0f;

    TVec3f vec = TVec3f();
    vec += xVec * x;
    vec += yVec * y;
    vec += zVec * z;

    b->GetTransform()->SetPosition(player_pos);
    b->SetVector(vec.Normalized());
    b->SetSpeed(VELOCITY);

    b->GetTransform()->SetScale(0.5f);

    // 生存時間を設定
    b->SetLifeTime(LIFE_TIME);
  }

  Asset::Sound::SHOT_SHOT_SANDAN.Play();
  return LIFE_TIME;
}

void BulletEmitter_Sandan::UpdateProcess()
{
}
