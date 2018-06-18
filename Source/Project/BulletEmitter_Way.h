
#pragma once

#include "BulletEmitter.h"

/*
�e��x�������Ĕ��˂�����Ƃǂ��������o���\�ɂȂ邩�̃T���v��
���łɒe�̐������֐������Ă����Ƃ�����������Ƃ����T���v��
*/

class BulletEmitter_Way: public BulletEmitter
{
public:
  BulletEmitter_Way(T_UINT8 power, T_FLOAT length, T_FLOAT count, T_FLOAT rad, T_FLOAT emission_z, T_FLOAT distance, T_FLOAT homing_rate, T_UINT16 homing_life_time);
  ~BulletEmitter_Way();

public:
  virtual T_UINT32 EmissionProcess() override;
  virtual void UpdateProcess() override;

private:
  const T_UINT8 power_;
  const T_FLOAT length_;
  const T_UINT8 count_;
  const T_FLOAT rad_;
  const T_FLOAT emission_z_;
  const T_FLOAT distance_;
  const T_FLOAT homing_rate_;
  const T_UINT16 homing_lifetime_;

};