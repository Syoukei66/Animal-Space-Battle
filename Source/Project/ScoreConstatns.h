#pragma once

namespace ScoreConstants
{
//星の取得ポイント
//POINT_GET_STAR_BASE * コンボ数
const T_UINT32 POINT_GET_STAR_BASE = 1000;

//星へダメージを与えた時のポイント
const T_UINT32 POINT_ATTACK_TO_STAR = 0;

//星を破壊した時のポイント
const T_UINT32 POINT_DESTROY_STAR = 1000;

//敵への攻撃時に入るポイント
const T_UINT32 POINT_ATTACK_TO_ENEMY = 100;

//敵の破壊時に手に入るポイント
//POINT_DESTROY_ENEMY * 敵のレア度
const T_UINT32 POINT_DESTROY_ENEMY = 3000;

}