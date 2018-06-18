#pragma once

//GameInput
//�Q�[���̓��͂��`����
namespace GameInput
{

//�V�����{�^�����͂��`���������͂��̗񋓌^�ɒǉ����Ă���
//�ǉ������ꍇ�Acpp�t�@�C�����Ƀ{�^���̏ڍׂ��`���Ă���
enum
{
  X_AXIS, //X������
  Y_AXIS, //Y������
  LOCKON, //���b�N�I��
  ACCEL,  //�A�N�Z��
  BRAKE,  //�u���[�L
  FIRE,   //�V���b�g
	START,

  DEBUG_GACHA,  //�f�o�b�O�p�K�`��

  DEBUG_MOUSE_CLICK, //�f�o�b�O�}�E�X���͂x
  DEBUG_SCREEN_X, //�f�o�b�O�}�E�X���͂w
  DEBUG_SCREEN_Y, //�f�o�b�O�}�E�X���͂x

  GAME_INPUT_DATANUM, //�����͐G��Ȃ�
};

//�����͐G��Ȃ�
const InputEntity* GetInputEntities();

}