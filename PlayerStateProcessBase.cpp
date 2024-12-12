#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"PlayerStateProcessBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
PlayerStateProcessBase::PlayerStateProcessBase(int modelHandle)
{
	this->modelHandle = modelHandle;

	nowAnimPlayTime = 0.0f;
}

/// <summary>
/// �A�j���[�V�����Đ�
/// </summary>
/// <param name="playSpeed">�Đ����x</param>
/// <param name="stop">�ꎞ��~</param>
void PlayerStateProcessBase::PlayAnimation(float playSpeed,bool stop)
{
	if (!stop)
	{
		nowAnimPlayTime += playSpeed;
	}

	//�A�j���[�V�������Ԃ����Đ����ԂɒB���Ă����ꍇ
	if (nowAnimPlayTime >= animTotalTime)
	{
		nowAnimPlayTime = 0.0f;
	}

	//�A�j���[�V�������f
	MV1SetAttachAnimTime(modelHandle, nowPlayAnim, nowAnimPlayTime);
}

/// <summary>
/// �A�j���[�V�����̏I��
/// </summary>
void PlayerStateProcessBase::DetachAnimation(int attachIndex)
{
	MV1DetachAnim(modelHandle, attachIndex);
}