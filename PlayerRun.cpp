#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
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

	//�ϐ�������
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
/// <param name="position">�|�W�V����</param>
/// <param name="angle">�p�x</param>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
/// <param name="objectCollision">�Փ˃I�u�W�F�N�g���</param>
/// <returns>�����ł͎g��Ȃ�</returns>
bool PlayerRun::Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)
{
	//�ړ�����
	Move(playerData, camera);
	//�A�j���[�V�����Đ�
	PlayAnimation(0.4f, !moveflg);

	return false;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="inputstate">���͏��</param>
/// <param name="stickstate">�X�e�B�b�N���͏��</param>
/// <param name="camera">�J����</param>
void PlayerRun::Move(UsePlayerData playerData, Camera camera)
{
	//������
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//���X�e�B�b�N�̊p�x�����
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//���͂������
	if ((stickX != 0.0f || stickY != 0.0f))
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

	//�J�v�Z��������Ă�����x�N�g���̌�����ύX
	if (playerData.runPlace == RunPlaceKind::capsule && playerData.onFoot)
	{
		//�ΏۃJ�v�Z���̎������
		VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);

		//�J�v�Z���̉������
		float underY;
		if (playerData.capsuleEnd.y <= playerData.capsuleStart.y)
		{
			//�ΏۃJ�v�Z���̎������
			underY = playerData.capsuleEnd.y;
		}
		else
		{
			//�ΏۃJ�v�Z���̎������
			underY = playerData.capsuleStart.y;
		}

		//�J�v�Z���̐����Ƃ̊p�x���Ƃ�
		float cal1 = sqrtf(pow(shaft.x, 2) + pow(shaft.y, 2) + pow(shaft.z, 2));//�J�v�Z���̃x�N�g��
		float cal2 = sqrtf(pow(shaft.x, 2) + pow(underY, 2) + pow(shaft.z, 2));//Y���W���J�v�Z���̉��ɂ����x�N�g��
		float cosTheta = VDot(shaft, VGet(shaft.x, underY, shaft.z)) / (cal1 * cal2);
		float angle = acos(cosTheta);//�p�x�ϊ�

		float deg = angle * (180 / DX_PI_F);//�m�F�p

		//����moveVec�̒���
		float horizonLen = VSize(moveVec);
		//Y���W�ύX
		moveVec.y = sin(angle) * horizonLen;

		if (VSize(moveVec) > 0)
		{
			targetLookDirection = moveVec;
		}
	}
}