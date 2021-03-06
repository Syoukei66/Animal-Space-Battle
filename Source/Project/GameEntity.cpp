#include "GameEntity.h"
#include "GameLevelParam.h"

GameEntity::GameEntity()
  : ignore_space_wall_(false)
{
  this->collider_ = new GameEntityCollider(this);
  this->collider_->SetRadius(1.0f);
}

GameEntity::~GameEntity()
{
  delete this->collider_;
}

void GameEntity::PostUpdate()
{
  if (this->ignore_space_wall_)
  {
    return;
  }
  //世界の壁を越えないようにする処理
  //原点からの距離が宇宙の壁までの距離以上であれば(sqrtが呼ばれないよう２乗同士で比較)
  const T_FLOAT field_radius = GameLevelParam::GetInstance().GetFieldLevel(Field::FIELD_RADIUS);
  const TVec3f current_world_pos = this->GetTransform()->GetWorldPosition();
  if (current_world_pos.LengthSquare() > field_radius * field_radius)
  {
    //プレイヤーの空間上の位置を正規化し、それに宇宙の壁までの距離を乗算する事で、宇宙の壁ギリギリの座標を得れる
    const TVec3f next_world_pos = current_world_pos.Normalized() * field_radius;
    const TVec3f current_local_pos = this->GetTransform()->GetPosition();
    this->GetTransform()->SetPosition(next_world_pos - current_world_pos + current_local_pos);
  }
}

bool GameEntity::HitCheck(GameEntity* other)
{
  return this->collider_->Collision(*other->collider_);
}
