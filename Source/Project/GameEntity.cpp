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
  //���E�̕ǂ��z���Ȃ��悤�ɂ��鏈��
  //���_����̋������F���̕ǂ܂ł̋����ȏ�ł����(sqrt���Ă΂�Ȃ��悤�Q�擯�m�Ŕ�r)
  const T_FLOAT field_radius = GameLevelParam::GetInstance().GetFieldLevel(Field::FIELD_RADIUS);
  const TVec3f current_world_pos = this->GetTransform()->GetWorldPosition();
  if (current_world_pos.LengthSquare() > field_radius * field_radius)
  {
    //�v���C���[�̋�ԏ�̈ʒu�𐳋K�����A����ɉF���̕ǂ܂ł̋�������Z���鎖�ŁA�F���̕ǃM���M���̍��W�𓾂��
    const TVec3f next_world_pos = current_world_pos.Normalized() * field_radius;
    const TVec3f current_local_pos = this->GetTransform()->GetPosition();
    this->GetTransform()->SetPosition(next_world_pos - current_world_pos + current_local_pos);
  }
}

bool GameEntity::HitCheck(GameEntity* other)
{
  return this->collider_->Collision(*other->collider_);
}
