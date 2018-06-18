
#pragma once

#include "BulletEmitter.h"

/*
弾を遅延させて発射させるとどういう演出が可能になるかのサンプル
ついでに弾の生成を関数化しておくといい事があるというサンプル
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
  //T_UINT〇みたいな書き方は別にしなくていい。
  //普通にintでOK

  //弾の発射からの経過フレーム数(ほぼ直訳)
  //長い名前に見えるけどこれくらいの長さは
  //色んなプロジェクトで普通に見かけるので慣れよう
  //コメントが無くても何の変数なのかが分かる事が重要
  T_UINT16 frame_elapsed_from_emission_;

  T_UINT16 need_emit_bullet_count_;

};