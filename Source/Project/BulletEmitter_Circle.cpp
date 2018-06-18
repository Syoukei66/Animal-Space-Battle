#include "BulletEmitter_Circle.h"

//円を構成する弾の数
static const T_UINT16 CIRCLE_BULLET_COUNT = 6;
//円の数
static const T_UINT16 CIRCLE_COUNT = 5;

//弾の数
static const T_UINT16 BULLET_MAX = CIRCLE_BULLET_COUNT * CIRCLE_COUNT;

//円の最小半径
static const T_FLOAT CIRCLE_RADIUS_BASE = 3.0f;

//弾１発が生成されるのにかかるフレーム
static const T_UINT16 BULLET_EMISSION_NEED_FRAME = 1;
//弾全てが生成されるのにかかるフレーム
static const T_UINT16 BULLET_EMISSION_NEED_FRAME_SUM = CIRCLE_BULLET_COUNT * CIRCLE_COUNT * BULLET_EMISSION_NEED_FRAME;

//弾が生成されてから発射されるまでの間隔
static const T_UINT16 DELAY = BULLET_EMISSION_NEED_FRAME_SUM;
//弾の生存時間
static const T_UINT16 LIFE_TIME = 100;
//弾の速度
static const T_FLOAT VELOCITY = 5.0f;
//弾が収束するまでの距離
static const T_FLOAT TARGET_DISTANCE = VELOCITY * 200;

BulletEmitter_Circle::BulletEmitter_Circle()
  : BulletEmitter(BULLET_MAX)
{
}

BulletEmitter_Circle::~BulletEmitter_Circle()
{
}

T_UINT32 BulletEmitter_Circle::EmissionProcess()
{
  Asset::Sound::SHOT_SHOT_CIRCLE.Play();
  //弾の発射ボタンが押された時、
  //生成する必要がある弾の数をBULLET_EXAMPLE_MAXにセット
  this->need_emit_bullet_count_ = BULLET_MAX;

  //弾の発射ボタンが押された時からの経過フレーム数をカウントしておく
  this->frame_elapsed_from_emission_ = 0;

  //全ての弾の生存期間が終わるまで次の弾は撃てない
  return BULLET_EMISSION_NEED_FRAME_SUM + LIFE_TIME + DELAY;
}

void BulletEmitter_Circle::UpdateProcess()
{
  //生成する必要がある弾があるかチェック。0なら何も処理しない。
  if (this->need_emit_bullet_count_ == 0)
  {
    return;
  }
  //経過フレーム数から[残りの弾数]を計算
  const T_UINT16 rest_emit_bullet_count = BULLET_MAX - (T_FLOAT)this->frame_elapsed_from_emission_ / BULLET_EMISSION_NEED_FRAME;

  //計算された[残りの弾数]が[生成する必要がある弾数]を下回っていた場合、
  //計算された[残りの弾数]と[生成する必要がある弾数]が一致するまで弾を生成する。
  while (rest_emit_bullet_count < this->need_emit_bullet_count_)
  {
    this->need_emit_bullet_count_--;
    const T_UINT8 current_circle = this->need_emit_bullet_count_ / CIRCLE_BULLET_COUNT;
    const T_UINT8 current_order = this->need_emit_bullet_count_ % CIRCLE_BULLET_COUNT;
    //弾の円周上の位置の角度を計算
    const T_FLOAT rad = (T_FLOAT)current_order / CIRCLE_BULLET_COUNT * MathConstants::PI_2;
    this->CircularEmission(CIRCLE_RADIUS_BASE * (current_circle + 1), rad, current_order);
  }
  //経過フレーム数を１増やす
  this->frame_elapsed_from_emission_++;
}

void BulletEmitter_Circle::CircularEmission(T_FLOAT radius, T_FLOAT rad, T_UINT8 order)
{
  Bullet* b = this->Allocate();
  if (!b)
  {
    return;
  }
  b->SetPower(1);

  Player* player = this->GetPlayer();
  const TVec3f player_pos = player->GetTransform()->GetWorldPosition();

  // プレイヤーの絶対空間での向きを取得
  // WorldMatrixから現在の向きを基準としたX/Y/Z軸ベクトルを取得できる
  const TVec3f xVec = player->GetTransform()->GetWorldMatrix().GetCameraXVec();
  const TVec3f yVec = player->GetTransform()->GetWorldMatrix().GetCameraYVec();
  const TVec3f zVec = player->GetTransform()->GetWorldMatrix().GetCameraZVec();

  const T_FLOAT x =  radius * sinf(rad);//radius * cosf(rad);
  const T_FLOAT y =  radius * cosf(rad); //radius * sinf(rad);
  const T_FLOAT z = 0;

  // ベクトルを掛ける事で現在向いてる向きを基準とした座標系での座標計算ができる
  TVec3f bullet_pos = player_pos;
  bullet_pos += xVec * x;
  bullet_pos += yVec * y;
  bullet_pos += zVec * z;

  b->GetTransform()->SetPosition(bullet_pos);

  // 終着点を決め、終着点と現在の位置の差からベクトルを求め、
  // 正規化し速度を掛ける事で終着点に向けて毎フレーム長さVELOCITYだけ移動させる事ができる

  const TVec3f target_point = player_pos + zVec * TARGET_DISTANCE;
  b->SetVector((target_point - bullet_pos).Normalized());
  b->SetSpeed(VELOCITY);
  b->SetHomingRate(0.05f);
  b->SetHomingLifeTime(80);

  // 見づらいのでスケールを変更(スケールの変更は当たり判定の大きさにも反映される)
  b->GetTransform()->SetScale(0.5f);

  // 同じ円周にある弾は同時に発射されるように
  b->SetDelay(DELAY - (CIRCLE_BULLET_COUNT - order) * BULLET_EMISSION_NEED_FRAME);

  // 生存時間を設定
  b->SetLifeTime(LIFE_TIME);

}
