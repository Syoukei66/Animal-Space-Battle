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
    //�V�����e�𐶐�
    Bullet* b = this->Allocate();

    //�e��NULL��������e������ȏ㐶���ł��Ȃ��̂ŉ������Ȃ�
    if (!b)
    {
      return 1;
    }

    b->SetPower(30);
    //GetPlayer�Ńv���C���[�̃N���X���擾
    Player* player = this->GetPlayer();

    //�����̃N���X���g���Ēe�̋O���������Ă�����

    //�e�̎���(�t���[��)���w��
    b->SetLifeTime(LIFE_TIME);

    b->SetRadius(player->GetColliderRadius());

    //�v���C���[�̈ʒu�ɍ��W�����킹��
    b->GetTransform()->SetPosition(player->GetTransform()->GetWorldPosition());

    TVec3f direction = TVec3f();

    direction.x += Util::GetRandom(-1.0f, 1.0f);
    direction.y += Util::GetRandom(-1.0f, 1.0f);
    direction.z += Util::GetRandom(-1.0f, 1.0f);

    //�v���C���[�̌��������̂܂ܒe�̑��x��(=���t���[���v���C���[�������Ă�����ɂP���i��)
    b->SetVector(direction.Normalized());
    b->SetSpeed(this->speed_);
  }

  Asset::Sound::SHOT_SHOT_ZIBAKU.Play();
  return 1;
}

void BulletEmitter_Self::UpdateProcess()
{
}
