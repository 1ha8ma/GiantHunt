#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"PlayerRun.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerRun::PlayerRun(int modelHandle,VECTOR prevtargetLookDirection):PlayerStateProcessBase(modelHandle)
{
	//�A�j���[�V�����A�^�b�`
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Run);
	//�A�j���[�V�����̑��Đ����Ԃ����
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	targetLookDirection = prevtargetLookDirection;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRun::~PlayerRun()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
bool PlayerRun::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera)
{
	//�ړ�����
	Move(inputstate, stickstate, camera);
	//�A�j���[�V�����Đ�
	PlayAnimation(0.4f,!moveflg);

	return false;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
void PlayerRun::Move(int inputstate, DINPUT_JOYSTATE stickstate, Camera camera)
{
	//������
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//���X�e�B�b�N�̊p�x�����
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//���͂������
	if (!stickX == 0.0f || !stickY == 0.0f)
	{
		float stickAngle = atan2(stickY, stickX);

		moveVec.x = cos(stickAngle + -camera.GetangleH());
		moveVec.z = sin(stickAngle + -camera.GetangleH());

		moveflg = true;
		targetLookDirection = moveVec;
	}

	//���K��
	if (VSize(moveVec) > 0)
	{
		moveVec = VNorm(moveVec);
	}
	//�X�s�[�h���Z
	moveVec = VScale(moveVec, Speed);
}