#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Calculation.h"
#include"Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	input = new Input();
}

/// <summary>
/// 初期化
/// </summary>
void Camera::Initialize(VECTOR playerPosition)
{
	//距離設定
	SetCameraNearFar(10.0f, 10000.0f);

	position = VGet(0, 2000, -1500);
	lookPosition = playerPosition;
	lookPosition.y += CameraPlayerTargetHeight;
	angleH = 0.0f;
	angleV = 0.0f;

	t = 0;
	lerpflg = false;
	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(VECTOR playerPosition, float angle, VECTOR enemyPosition)
{
	//注視点移動
	bool inputflg = false;
	if ((Input::InputNumber::Right_R & input->GetInputState()) == Input::InputNumber::Right_R)
	{
		angleH += AngleSpeed;
		if (angleH > DX_PI_F)
		{
			angleH -= DX_PI_F;
		}
		inputflg = true;
	}
	if ((Input::InputNumber::Left_R & input->GetInputState()) == Input::InputNumber::Left_R)
	{
		angleH -= AngleSpeed;
		if (angleH < -DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
		inputflg = true;
	}
	if ((Input::InputNumber::Up_R & input->GetInputState()) == Input::InputNumber::Up_R)
	{
		angleV -= AngleSpeed;
		if (angleV < -DX_PI_F / 8)
		{
			angleV = -DX_PI_F / 8;
		}
		inputflg = true;
	}
	if ((Input::InputNumber::Down_R & input->GetInputState()) == Input::InputNumber::Down_R)
	{
		angleV += AngleSpeed;
		if (angleV > DX_PI_F / 2 - 0.6f)
		{
			angleV = DX_PI_F / 2 - 0.6f;
		}
		inputflg = true;
	}

	//ターゲットカメラ
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

	//右スティック視点移動があった場合
	if (!lerpflg && inputflg)
	{
		lookPosition = playerPosition;
		lookPosition.x += cos(angleH);
		lookPosition.y = playerPosition.y + CameraPlayerTargetHeight;
		lookPosition.z += sin(angleH);
	}
	//視点移動なしターゲットカメラなしの通常時
	else if (!lerpflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
	}

	//0基準→プレイヤーとの距離分X軸方向にずらす→Z軸回転で高くする→Y軸回転で場所移動→プレイヤーのY座標を高くしたものを足す
	//NOTE:最後プレイヤーのY座標を高くしたものを足すようにしたのはlookPositionを足すとターゲットカメラにしたときにターゲットの場所に移動してしまうから
	MATRIX rotY = MGetRotY(angleH + DX_PI_F / 2);//XXX:90度足さなければ後ろからではなく横から見えるようになった
	MATRIX rotZ = MGetRotZ(angleV);
	position = VAdd(VTransform(VTransform(VGet(PlayerDistance, 0.0f, 0.0f), rotZ), rotY), VAdd(playerPosition, VGet(0.0f, CameraPlayerTargetHeight, 0.0f)));

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}