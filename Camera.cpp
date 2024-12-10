#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	input = new Input();

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize()
{
	//距離設定
	SetCameraNearFar(10.0f, 6000.0f);

	position = VGet(0, 2000, -1500);
	lookPosition = VGet(0, 100, 0);
	lookAngleXZ = 0.0f;
	lookAngleY = 0.0f;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// 更新
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

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}