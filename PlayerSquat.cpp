#include"DxLib.h"
#include"CollisionData.h"
#include"Input.h"
#include"Camera.h"
#include"PlayerSquat.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerSquat::PlayerSquat(int modelHandle,VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Squat);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//���f���̌����ݒ�
	targetLookDirection = prevtargetLookDirection;

	//private�ϐ�������
	changeState = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerSquat::~PlayerSquat()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="position">�|�W�V����</param>
/// <param name="angle">�p�x</param>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˃I�u�W�F�N�g���</param>
/// <returns>�X�e�[�g�ύX</returns>
bool PlayerSquat::Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)
{
	moveVec = VGet(0, 0, 0);

	PlayAnimation(1.0f, false);

	//R1�𗣂��ƃX�e�[�g�ύX
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1)
	{
		changeState = true;
	}

	return changeState;
}