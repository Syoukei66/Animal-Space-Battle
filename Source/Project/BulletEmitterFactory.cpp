#include "stdafx.h"
#include "BulletEmitterFactory.h"

#include "BulletEmitter_Way.h"
#include "BulletEmitter_Sandan.h"
#include "BulletEmitter_Self.h"
#include "BulletEmitter_Circle.h"

BaseBulletEmitter* BulletEmitterFactory::Create(const std::string& name_id)
{
  if (name_id == "x_3way") //横３つ
  {
    return new BulletEmitter_Way(
      10,
      20.0f,
      3,
      MathConstants::PI_1_2,
      -10.0f,
      200.0f,
      0.05f,
      50
    );
  }
  if (name_id == "sandan") //散弾
  {
    return new BulletEmitter_Sandan();
  }
  if (name_id == "x_homing") //未定
  {
    return new BulletEmitter_Way(
      10,
      20.0f,
      3,
      MathConstants::PI_1_2,
      -10.0f,
      200.0f,
      0.05f,
      80
    );
  }
  if (name_id == "self") //未定
  {
    return new BulletEmitter_Self(8.0f);
  }
  if (name_id == "self_l") //未定
  {
    return new BulletEmitter_Self(12.0f);
  }
  if (name_id == "circle2") //未定
  {
    return new BulletEmitter_Circle();
  }

  //case EMITTER_ID_TEST:
  //  //return new BulletEmitter_Example();//円形状の散弾
  //  return new BulletEmitter_Test1();
  //  //return new BulletEmitter_Test();//近距離散弾予定
  //case EMITTER_ID_TEST2:
  //  return new BulletEmitter_Test();
  NATIVE_ASSERT(false, "bulletEmitterTable.csvのname_id全てに対してBulletEmitterを設定してください。");
  return nullptr;
}
