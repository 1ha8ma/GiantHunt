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
	calculation = new Calculation();
}

/// <summary>
/// �X�^�[�g�V�[��������
/// </summary>
/// <param name="position">�J�����|�W�V����</param>
/// <param name="lookPosition">�J���������_</param>
void Camera::StartSceneInitialize(VECTOR position,VECTOR lookPosition)
{
	//�����ݒ�
	SetCameraNearFar(100.0f, 20000.0f);

	this->position = position;
	this->lookPosition = lookPosition;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(this->position, this->lookPosition);
}

/// <summary>
/// �X�^�[�g�V�[���X�V
/// </summary>
/// <param name="position">�J�����|�W�V����</param>
/// <param name="lookPosition">�J���������_</param>
void Camera::UpdateStartScene(VECTOR position,VECTOR lookPosition)
{
	this->position = position;
	this->lookPosition = lookPosition;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ������
/// </summary>
void Camera::GameInitialize(VECTOR playerPosition)
{
	//�����ݒ�
	SetCameraNearFar(100.0f, 20000.0f);

	//private�ϐ�
	position = VGet(0, 2000, -1500);
	lookPosition = playerPosition;
	lookPosition.y += CameraPlayerTargetHeight;
	angleH = 0.0f;
	angleV = 0.0f;
	productionflg = false;
	shakingDirection = true;
	t = 0;
	lerpflg = false;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="playerPosition">�v���C���[�|�W�V����</param>
/// <param name="targetCameraPosition">�^�[�Q�b�g�J�����|�W�V����</param>
void Camera::UpdateGame(VECTOR playerPosition, VECTOR targetCameraPosition)
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
			angleH -= DX_TWO_PI_F;
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
			angleH += DX_TWO_PI_F;
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

		lookPosition = calculation->Lerp(targetCameraPosition, lookPosition, 0.01, t);
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
	else if (productionflg)
	{
		
	}
	//���_�ړ��Ȃ��^�[�Q�b�g�J�����Ȃ��̒ʏ펞
	else if (!lerpflg && !productionflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
	}

	//0����v���C���[�Ɨ�������������X�������ɂ��炷��Z����]�ō������遨Y����]�ŏꏊ�ړ����v���C���[��Y���W�������������̂𑫂�
	//NOTE:�Ō�v���C���[��Y���W�������������̂𑫂��悤�ɂ����̂�lookPosition�𑫂��ƃ^�[�Q�b�g�J�����ɂ����Ƃ��Ƀ^�[�Q�b�g�̏ꏊ�Ɉړ����Ă��܂�����
	MATRIX rotY = MGetRotY(angleH + DX_PI_F / 2);
	MATRIX rotZ = MGetRotZ(angleV);
	
	position = VAdd(VTransform(VTransform(VGet(PlayerDistance, 0.0f, 0.0f), rotZ), rotY), VAdd(playerPosition, VGet(0.0f, CameraPlayerTargetHeight, 0.0f)));
	//���o�X�V
	UpdateProduction(playerPosition);

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �Q�[���I�[�o�[�V�[��������
/// </summary>
/// <param name="playerPosition"></param>
void Camera::InitializeGameOver(VECTOR playerPosition)
{
	//�����ݒ�
	SetCameraNearFar(10.0f, 10000.0f);

	//XXX:�|�W�V�����ƒ����_�̃|�W�V������XZ�𓯂��ɂ���Ɖ�ʂ������Ȃ��ĉ����f��Ȃ��Ȃ邪�������炷�Ɖf��
	position = playerPosition;
	position.x += 10;
	position.z += 10;
	position.y += 100;

	//�����_
	lookPosition = playerPosition;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �Q�[���I�[�o�[�V�[���X�V
/// </summary>
void Camera::UpdateGameOver()
{
	position.y += 3.0f;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �Q�[���N���A�V�[��������
/// </summary>
/// <param name="cameraPosition">�ݒu����J�����|�W�V����</param>
/// <param name="enemyPosition">�����_�ɂȂ�G�̃|�W�V����</param>
void Camera::InitializeGameClear(VECTOR cameraPosition, VECTOR enemyPosition)
{
	//�����ݒ�
	SetCameraNearFar(100.0f, 20000.0f);

	position = cameraPosition;
	lookPosition = enemyPosition;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �Q�[���N���A�V�[���X�V
/// </summary>
/// <param name="enemyPosition">�����_�ɂȂ�G�̃|�W�V����</param>
void Camera::UpdateGameClear(VECTOR enemyPosition)
{
	lookPosition = enemyPosition;

	//���o�X�V
	UpdateProduction(enemyPosition);

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ���o�X�V
/// </summary>
void Camera::UpdateProduction(VECTOR playerPosition)
{
	ShakingVertical(playerPosition);
}

/// <summary>
/// �c�h��
/// </summary>
/// <param name="shakingPower">�h��̋���</param>
/// <param name="shakingDirectionChangeflame">�h��������ύX����t���[��</param>
/// <param name="flame">�Đ��t���[��</param>
void Camera::PlayShakingVertical(float shakingPower, int shakingDirectionChangeflame, int flame)
{
	//���o���łȂ���ΊJ�n
	if (!productionflg)
	{
		totalflame = 0;
		changeflame = 0;
		this->shakingPower = shakingPower;
		this->shakingDirectionChangeflame = shakingDirectionChangeflame;
		this->playflame = flame;
		shakingDirection = true;

		productionflg = true;
		shakingVerticalflg = true;
	}
}

/// <summary>
/// �c�h��
/// </summary>
/// <param name="shakingPower">�h��̋���</param>
/// <param name="shakingDirectionChangeflame">�h��������ύX����t���[��</param>
/// <param name="flame">�Đ�����</param>
void Camera::ShakingVertical(VECTOR playerPosition)
{
	if (shakingVerticalflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
		//�h��
		if (shakingDirection)
		{
			lookPosition.y += shakingPower * changeflame;
		}
		else
		{
			lookPosition.y -= shakingPower * changeflame;
		}

		//�h�������ύX
		if (changeflame != 0 && changeflame % shakingDirectionChangeflame == 0)
		{
			shakingDirection = !shakingDirection;
			changeflame = 0;
		}

		//�t���[�����Z
		changeflame++;
		totalflame++;

		//�I��
		if (totalflame >= playflame)
		{
			productionflg = false;
			shakingVerticalflg = false;
		}
	}
}