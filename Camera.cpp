#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
	input = new Input();

	Initialize();
}

/// <summary>
/// ������
/// </summary>
void Camera::Initialize()
{
	//�����ݒ�
	SetCameraNearFar(10.0f, 6000.0f);

	position = VGet(0, 2000, -1500);
	lookPosition = VGet(0, 100, 0);
	lookAngleXZ = 0.0f;
	lookAngleY = 0.0f;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update(VECTOR playerPosition,float angle)
{
	position.x += 100;
	position.y += 100;
	position.z += 100;

	if ((Input::InputNumber::Right_R & input->GetInputState()) == Input::InputNumber::Right_R)
	{
		lookAngleXZ += 0.02;
	}
	if ((Input::InputNumber::Left_R & input->GetInputState()) == Input::InputNumber::Left_R)
	{
		lookAngleXZ -= 0.02;
	}
	if ((Input::InputNumber::Up_R & input->GetInputState()) == Input::InputNumber::Up_R)
	{
		lookAngleY += 0.02;
	}
	if ((Input::InputNumber::Down_R & input->GetInputState()) == Input::InputNumber::Down_R)
	{
		lookAngleY += 0.02;
	}

	lookPosition.x = sin(lookAngleXZ) * 10000.0f;
	lookPosition.z = cos(lookAngleXZ) * 10000.0f;

	//�|�W�V�����E�����_���f
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}