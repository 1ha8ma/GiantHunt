#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Calculation.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	input = new Input();
}

/// <summary>
/// ������
/// </summary>
void Camera::Initialize(VECTOR playerPosition)
{
	//�����ݒ�
	SetCameraNearFar(10.0f, 10000.0f);

	position = VGet(0, 2000, -1500);
	lookPosition = playerPosition;
	lookPosition.y += CameraPlayerTargetHeight;
	angleH = 0.0f;
	angleV = 0.0f;

	t = 0;
	lerpflg = false;
	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update(VECTOR playerPosition, float angle, VECTOR enemyPosition)
{
	//�����_�ړ�
	bool inputflg = false;
	DINPUT_JOYSTATE stickinput = input->GetStickInput();//�X�e�B�b�N���͏��

	//�E
	if (stickinput.Rx > 0.0f)
	{
		angleH += AngleSpeed;
		//180�x�𒴂�����߂�
		if (angleH > DX_PI_F)
		{
			angleH -= DX_PI_F;
		}
		inputflg = true;
	}
	//��
	if (stickinput.Rx < 0.0f)
	{
		angleH -= AngleSpeed;
		//-180�x�𒴂�����߂�
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
		inputflg = true;
	}
	//��
	if (stickinput.Ry < 0.0f)
	{
		angleV -= AngleSpeed;
		//���
		if (angleV < -DX_PI_F / 8)
		{
			angleV = -DX_PI_F / 8;
		}
		inputflg = true;
	}
	//��
	if (stickinput.Ry > 0.0f)
	{
		angleV += AngleSpeed;
		//���
		if (angleV > DX_PI_F / 2 - 0.6f)
		{
			angleV = DX_PI_F / 2 - 0.6f;
		}
		inputflg = true;
	}

	//�^�[�Q�b�g�J����
	if ((Input::InputNumber::L1 & input->GetInputState()) == Input::InputNumber::L1)
	{
		if (!lerpflg)
		{
			t = 0;
			lerpflg = true;
		}
		lookTargetPos = enemyPosition;

		lookPosition = Calculation::Lerp(lookTargetPos, lookPosition, 0.01, t);
	}
	else
	{
		lerpflg = false;
	}

	//�E�X�e�B�b�N���_�ړ����������ꍇ
	if (!lerpflg && inputflg)
	{
		lookPosition = playerPosition;
		lookPosition.x += cos(angleH);
		lookPosition.y = playerPosition.y + CameraPlayerTargetHeight;
		lookPosition.z += sin(angleH);
	}
	//���_�ړ��Ȃ��^�[�Q�b�g�J�����Ȃ��̒ʏ펞
	else if (!lerpflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
	}

	//0����v���C���[�Ƃ̋�����X�������ɂ��炷��Z����]�ō������遨Y����]�ŏꏊ�ړ����v���C���[��Y���W�������������̂𑫂�
	//NOTE:�Ō�v���C���[��Y���W�������������̂𑫂��悤�ɂ����̂�lookPosition�𑫂��ƃ^�[�Q�b�g�J�����ɂ����Ƃ��Ƀ^�[�Q�b�g�̏ꏊ�Ɉړ����Ă��܂�����
	MATRIX rotY = MGetRotY(angleH + DX_PI_F / 2);//XXX:90�x�����Ȃ���Ό�납��ł͂Ȃ������猩����悤�ɂȂ���
	MATRIX rotZ = MGetRotZ(angleV);
	position = VAdd(VTransform(VTransform(VGet(PlayerDistance, 0.0f, 0.0f), rotZ), rotY), VAdd(playerPosition, VGet(0.0f, CameraPlayerTargetHeight, 0.0f)));

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}