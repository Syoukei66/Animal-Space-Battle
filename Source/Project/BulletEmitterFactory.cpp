#include "stdafx.h"
#include "BulletEmitterFactory.h"

#include "BulletEmitter_Way.h"
#include "BulletEmitter_Sandan.h"
#include "BulletEmitter_Self.h"
#include "BulletEmitter_Circle.h"

BaseBulletEmitter* BulletEmitterFactory::Create(const std::string& name_id)
{
  if (name_id == "x_3way") //‰¡‚R‚Â
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
  if (name_id == "sandan") //U’e
  {
    return new BulletEmitter_Sandan();
  }
  if (name_id == "x_homing") //–¢’è
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
  if (name_id == "self") //–¢’è
  {
    return new BulletEmitter_Self(8.0f);
  }
  if (name_id == "self_l") //–¢’è
  {
    return new BulletEmitter_Self(12.0f);
  }
  if (name_id == "circle2") //–¢’è
  {
    return new BulletEmitter_Circle();
  }

  //case EMITTER_ID_TEST:
  //  //return new BulletEmitter_Example();//‰~Œ`ó‚ÌU’e
  //  return new BulletEmitter_Test1();
  //  //return new BulletEmitter_Test();//‹ß‹——£U’e—\’è
  //case EMITTER_ID_TEST2:
  //  return new BulletEmitter_Test();
  NATIVE_ASSERT(false, "bulletEmitterTable.csv‚Ìname_id‘S‚Ä‚É‘Î‚µ‚ÄBulletEmitter‚ğİ’è‚µ‚Ä‚­‚¾‚³‚¢B");
  return nullptr;
}
