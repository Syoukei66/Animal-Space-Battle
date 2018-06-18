
#pragma once

#include "BulletEmitter.h"

/*
弾を遅延させて発射させるとどういう演出が可能になるかのサンプル
ついでに弾の生成を関数化しておくといい事があるというサンプル
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