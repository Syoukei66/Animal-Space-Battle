#include "BulletEmitter_Circle.h"

//�~���\������e�̐�
static const T_UINT16 CIRCLE_BULLET_COUNT = 6;
//�~�̐�
static const T_UINT16 CIRCLE_COUNT = 5;

//�e�̐�
static const T_UINT16 BULLET_MAX = CIRCLE_BULLET_COUNT * CIRCLE_COUNT;

//�~�̍ŏ����a
static const T_FLOAT CIRCLE_RADIUS_BASE = 3.0f;

//�e�P�������������̂ɂ�����t���[��
static const T_UINT16 BULLET_EMISSION_NEED_FRAME = 1;
//�e�S�Ă����������̂ɂ�����t���[��
static const T_UINT16 BULLET_EMISSION_NEED_FRAME_SUM = CIRCLE_BULLET_COUNT * CIRCLE_COUNT * BULLET_EMISSION_NEED_FRAME;

//�e����������Ă��甭�˂����܂ł̊Ԋu
static const T_UINT16 DELAY = BULLET_EMISSION_NEED_FRAME_SUM;
//�e�̐�������
static const T_UINT16 LIFE_TIME = 100;
//�e�̑��x
static const T_FLOAT VELOCITY = 5.0f;
//�e����������܂ł̋���
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
  //�e�̔��˃{�^���������ꂽ���A
  //��������K�v������e�̐���BULLET_EXAMPLE_MAX�ɃZ�b�g
  this->need_emit_bullet_count_ = BULLET_MAX;

  //�e�̔��˃{�^���������ꂽ������̌o�߃t���[�������J�E���g���Ă���
  this->frame_elapsed_from_emission_ = 0;

  //�S�Ă̒e�̐������Ԃ��I���܂Ŏ��̒e�͌��ĂȂ�
  return BULLET_EMISSION_NEED_FRAME_SUM + LIFE_TIME + DELAY;
}

void BulletEmitter_Circle::UpdateProcess()
{
  //��������K�v������e�����邩�`�F�b�N�B0�Ȃ牽���������Ȃ��B
  if (this->need_emit_bullet_count_ == 0)
  {
    return;
  }
  //�o�߃t���[��������[�c��̒e��]���v�Z
  const T_UINT16 rest_emit_bullet_count = BULLET_MAX - (T_FLOAT)this->frame_elapsed_from_emission_ / BULLET_EMISSION_NEED_FRAME;

  //�v�Z���ꂽ[�c��̒e��]��[��������K�v������e��]��������Ă����ꍇ�A
  //�v�Z���ꂽ[�c��̒e��]��[��������K�v������e��]����v����܂Œe�𐶐�����B
  while (rest_emit_bullet_count < this->need_emit_bullet_count_)
  {
    this->need_emit_bullet_count_--;
    const T_UINT8 current_circle = this->need_emit_bullet_count_ / CIRCLE_BULLET_COUNT;
    const T_UINT8 current_order = this->need_emit_bullet_count_ % CIRCLE_BULLET_COUNT;
    //�e�̉~����̈ʒu�̊p�x���v�Z
    const T_FLOAT rad = (T_FLOAT)current_order / CIRCLE_BULLET_COUNT * MathConstants::PI_2;
    this->CircularEmission(CIRCLE_RADIUS_BASE * (current_circle + 1), rad, current_order);
  }
  //�o�߃t���[�������P���₷
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

  // �v���C���[�̐�΋�Ԃł̌������擾
  // WorldMatrix���猻�݂̌�������Ƃ���X/Y/Z���x�N�g�����擾�ł���
  const TVec3f xVec = player->GetTransform()->GetWorldMatrix().GetCameraXVec();
  const TVec3f yVec = player->GetTransform()->GetWorldMatrix().GetCameraYVec();
  const TVec3f zVec = player->GetTransform()->GetWorldMatrix().GetCameraZVec();

  const T_FLOAT x =  radius * sinf(rad);//radius * cosf(rad);
  const T_FLOAT y =  radius * cosf(rad); //radius * sinf(rad);
  const T_FLOAT z = 0;

  // �x�N�g�����|���鎖�Ō��݌����Ă��������Ƃ������W�n�ł̍��W�v�Z���ł���
  TVec3f bullet_pos = player_pos;
  bullet_pos += xVec * x;
  bullet_pos += yVec * y;
  bullet_pos += zVec * z;

  b->GetTransform()->SetPosition(bullet_pos);

  // �I���_�����߁A�I���_�ƌ��݂̈ʒu�̍�����x�N�g�������߁A
  // ���K�������x���|���鎖�ŏI���_�Ɍ����Ė��t���[������VELOCITY�����ړ������鎖���ł���

  const TVec3f target_point = player_pos + zVec * TARGET_DISTANCE;
  b->SetVector((target_point - bullet_pos).Normalized());
  b->SetSpeed(VELOCITY);
  b->SetHomingRate(0.05f);
  b->SetHomingLifeTime(80);

  // ���Â炢�̂ŃX�P�[����ύX(�X�P�[���̕ύX�͓����蔻��̑傫���ɂ����f�����)
  b->GetTransform()->SetScale(0.5f);

  // �����~���ɂ���e�͓����ɔ��˂����悤��
  b->SetDelay(DELAY - (CIRCLE_BULLET_COUNT - order) * BULLET_EMISSION_NEED_FRAME);

  // �������Ԃ�ݒ�
  b->SetLifeTime(LIFE_TIME);

}
