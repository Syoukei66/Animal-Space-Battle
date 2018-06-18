#pragma once

//GameInput
//ゲームの入力を定義する
namespace GameInput
{

//新しいボタン入力を定義したい時はこの列挙型に追加していく
//追加した場合、cppファイル側にボタンの詳細を定義していく
enum
{
  X_AXIS, //X軸入力
  Y_AXIS, //Y軸入力
  LOCKON, //ロックオン
  ACCEL,  //アクセル
  BRAKE,  //ブレーキ
  FIRE,   //ショット
	START,

  DEBUG_GACHA,  //デバッグ用ガチャ

  DEBUG_MOUSE_CLICK, //デバッグマウス入力Ｙ
  DEBUG_SCREEN_X, //デバッグマウス入力Ｘ
  DEBUG_SCREEN_Y, //デバッグマウス入力Ｙ

  GAME_INPUT_DATANUM, //ここは触らない
};

//ここは触らない
const InputEntity* GetInputEntities();

}