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

	runPlace = false;

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
bool PlayerRun::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	//�ړ�����
	Move(inputstate, stickstate, camera, objectCapsuleStart, objectCapsuleEnd);
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
void PlayerRun::Move(int inputstate, DINPUT_JOYSTATE stickstate, Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	//������
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//���X�e�B�b�N�̊p�x�����
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//���͂������
	if (stickX != 0.0f || stickY != 0.0f)
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

	//�����΂߂�����Ă�����x�N�g���̌�����ύX
	if (runPlace)
	{
		//�ΏۃJ�v�Z���̎������
		VECTOR shaft = VSub(objectCapsuleStart, objectCapsuleEnd);

		//�J�v�Z���̉������
		float underY;
		if (objectCapsuleEnd.y <= objectCapsuleStart.y)
		{
			//�ΏۃJ�v�Z���̎������
			underY = objectCapsuleEnd.y;
		}
		else
		{
			//�ΏۃJ�v�Z���̎������
			underY = objectCapsuleStart.y;
		}

		//�p�x���Ƃ�
		float cal1 = sqrtf(pow(shaft.x, 2) + pow(shaft.y, 2) + pow(shaft.z, 2));//�J�v�Z���̃x�N�g��
		float cal2 = sqrtf(pow(shaft.x, 2) + pow(underY, 2) + pow(shaft.z, 2));//Y���W���J�v�Z���̉��ɂ����x�N�g��
		float cosTheta = VDot(shaft, VGet(shaft.x, underY, shaft.z)) / (cal1 * cal2);
		float angle = acos(cosTheta);//�p�x�ϊ�

		float deg = angle * (180 / DX_PI_F);//�m�F�p

		//���ʂ̒���
		float horizonLen = sqrt(pow(moveVec.x, 2) + pow(moveVec.z, 2));
		//y���W�ύX
		moveVec.y = sin(angle) * horizonLen;
		
		if (VSize(moveVec) > 0)
		{
			targetLookDirection = moveVec;
		}
	}
}