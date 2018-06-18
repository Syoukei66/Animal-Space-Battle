
#pragma once

#include "BulletEmitter.h"

/*
�e��x�������Ĕ��˂�����Ƃǂ��������o���\�ɂȂ邩�̃T���v��
���łɒe�̐������֐������Ă����Ƃ�����������Ƃ����T���v��
*/

class BulletEmitter_Circle : public BulletEmitter
{
public:
  BulletEmitter_Circle();
  ~BulletEmitter_Circle();

public:
  virtual T_UINT32 EmissionProcess() override;
  virtual void UpdateProcess() override;

private:
  void CircularEmission(T_FLOAT radius, T_FLOAT rad, T_UINT8 order);

private:
  //T_UINT�Z�݂����ȏ������͕ʂɂ��Ȃ��Ă����B
  //���ʂ�int��OK

  //�e�̔��˂���̌o�߃t���[����(�قڒ���)
  //�������O�Ɍ����邯�ǂ��ꂭ�炢�̒�����
  //�F��ȃv���W�F�N�g�ŕ��ʂɌ�������̂Ŋ���悤
  //�R�����g�������Ă����̕ϐ��Ȃ̂��������鎖���d�v
  T_UINT16 frame_elapsed_from_emission_;

  T_UINT16 need_emit_bullet_count_;

};