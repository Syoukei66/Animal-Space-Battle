#include "StarManager.h"
#include "GameLevelParam.h"

StarManager::StarManager()
  : AllocatableGameEntityManager(GameLevelParam::GetInstance().GetStarLevel(COUNT))
{
  const GameLevelParam& level = GameLevelParam::GetInstance();
  const T_UINT16 star_count = level.GetStarLevel(COUNT);
  for (T_UINT8 i = 0; i < star_count; ++i)
  {
    Star* star = this->Allocate();
    const T_FLOAT scale_min = level.GetStarLevel(SCALE_MIN);
    const T_FLOAT scale_max = level.GetStarLevel(SCALE_MAX);
    const T_FLOAT scale = Util::GetRandom(scale_min, scale_max);
    star->GetTransform()->SetScale(scale);
    T_FLOAT padding_rate = 10.0f;
    do
    {
      const T_FLOAT rad_x = Util::GetRandom(-1.0f, 1.0f);
      const T_FLOAT rad_y = Util::GetRandom(-1.0f, 1.0f);
      const T_FLOAT rad_z = Util::GetRandom(-1.0f, 1.0f);
      const T_FLOAT radius_begin = level.GetStarLevel(SPAWN_RADIUS_BEGIN);
      const T_FLOAT radius_end = level.GetStarLevel(SPAWN_RADIUS_END);
      const T_FLOAT distance = Util::GetRandom(radius_begin, radius_end);
      star->GetTransform()->SetPosition(TVec3f(rad_x, rad_y, rad_z).Normalized() * distance);
      padding_rate = std::max(1.0f, padding_rate * 0.99f);
    } while (star != this->Select([&](Star* s) {
        const TVec3f a = star->GetTransform()->GetPosition();
        const TVec3f b = s->GetTransform()->GetPosition();
        return (a - b).Length() < (star->GetTransform()->GetScaleMax() + s->GetTransform()->GetScaleMax()) * padding_rate;
      }
    ));
  }
}
