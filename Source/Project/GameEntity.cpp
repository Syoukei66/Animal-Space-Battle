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
  //¢ŠE‚Ì•Ç‚ğ‰z‚¦‚È‚¢‚æ‚¤‚É‚·‚éˆ—
  //Œ´“_‚©‚ç‚Ì‹——£‚ª‰F’ˆ‚Ì•Ç‚Ü‚Å‚Ì‹——£ˆÈã‚Å‚ ‚ê‚Î(sqrt‚ªŒÄ‚Î‚ê‚È‚¢‚æ‚¤‚Qæ“¯m‚Å”äŠr)
  const T_FLOAT field_radius = GameLevelParam::GetInstance().GetFieldLevel(Field::FIELD_RADIUS);
  const TVec3f current_world_pos = this->GetTransform()->GetWorldPosition();
  if (current_world_pos.LengthSquare() > field_radius * field_radius)
  {
    //ƒvƒŒƒCƒ„[‚Ì‹óŠÔã‚ÌˆÊ’u‚ğ³‹K‰»‚µA‚»‚ê‚É‰F’ˆ‚Ì•Ç‚Ü‚Å‚Ì‹——£‚ğæZ‚·‚é–‚ÅA‰F’ˆ‚Ì•ÇƒMƒŠƒMƒŠ‚ÌÀ•W‚ğ“¾‚ê‚é
    const TVec3f next_world_pos = current_world_pos.Normalized() * field_radius;
    const TVec3f current_local_pos = this->GetTransform()->GetPosition();
    this->GetTransform()->SetPosition(next_world_pos - current_world_pos + current_local_pos);
  }
}

bool GameEntity::HitCheck(GameEntity* other)
{
  return this->collider_->Collision(*other->collider_);
}
