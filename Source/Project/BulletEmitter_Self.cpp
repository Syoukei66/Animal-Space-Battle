#include "BulletEmitter_Self.h"

static const T_UINT8 BULLET_COUNT = 1;
static const T_UINT16 LIFE_TIME = 10;
static const T_UINT16 BULLET_MAX = BULLET_COUNT * LIFE_TIME;

BulletEmitter_Self::BulletEmitter_Self(T_FLOAT speed)
  : BulletEmitter(BULLET_COUNT * LIFE_TIME)
  , speed_(speed)
{
}

BulletEmitter_Self::~BulletEmitter_Self()
{
}

T_UINT32 BulletEmitter_Self::EmissionProcess()
{
  for (int i = 0; i < BULLET_COUNT; ++i)
  {
    //新しい弾を生成
    Bullet* b = this->Allocate();

    //弾がNULLだったら弾をこれ以上生成できないので何もしない
    if (!b)
    {
      return 1;
    }

    b->SetPower(30);
    //GetPlayerでプレイヤーのクラスを取得
    Player* player = this->GetPlayer();

    //これらのクラスを使って弾の軌道を書いていこう

    //弾の寿命(フレーム)を指定
    b->SetLifeTime(LIFE_TIME);

    b->SetRadius(player->GetColliderRadius());

    //プレイヤーの位置に座標を合わせる
    b->GetTransform()->SetPosition(player->GetTransform()->GetWorldPosition());

    TVec3f direction = TVec3f();

    direction.x += Util::GetRandom(-1.0f, 1.0f);
    direction.y += Util::GetRandom(-1.0f, 1.0f);
    direction.z += Util::GetRandom(-1.0f, 1.0f);

    //プレイヤーの向きをそのまま弾の速度に(=毎フレームプレイヤーが向いてる方向に１ずつ進む)
    b->SetVector(direction.Normalized());
    b->SetSpeed(this->speed_);
  }

  Asset::Sound::SHOT_SHOT_ZIBAKU.Play();
  return 1;
}

void BulletEmitter_Self::UpdateProcess()
{
}
