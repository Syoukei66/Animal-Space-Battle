
#pragma once

#include "BulletEmitter.h"

/*
�e��x�������Ĕ��˂�����Ƃǂ��������o���\�ɂȂ邩�̃T���v��
���łɒe�̐������֐������Ă����Ƃ�����������Ƃ����T���v��
*/

class BulletEmitter_Sandan : public BulletEmitter
{
public:
  BulletEmitter_Sandan();
  ~BulletEmitter_Sandan();

public:
  virtual T_UINT32 EmissionProcess() override;
  virtual void UpdateProcess() override;

private:

};