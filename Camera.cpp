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
	calculation = new Calculation();
}

/// <summary>
/// スタートシーン初期化
/// </summary>
/// <param name="position">カメラポジション</param>
/// <param name="lookPosition">カメラ注視点</param>
void Camera::StartSceneInitialize(VECTOR position,VECTOR lookPosition)
{
	//距離設定
	SetCameraNearFar(100.0f, 20000.0f);

	this->position = position;
	this->lookPosition = lookPosition;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(this->position, this->lookPosition);
}

/// <summary>
/// スタートシーン更新
/// </summary>
/// <param name="position">カメラポジション</param>
/// <param name="lookPosition">カメラ注視点</param>
void Camera::UpdateStartScene(VECTOR position,VECTOR lookPosition)
{
	this->position = position;
	this->lookPosition = lookPosition;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// 初期化
/// </summary>
void Camera::GameInitialize(VECTOR playerPosition)
{
	//距離設定
	SetCameraNearFar(100.0f, 20000.0f);

	//private変数
	position = VGet(0, 2000, -1500);
	lookPosition = playerPosition;
	lookPosition.y += CameraPlayerTargetHeight;
	angleH = 0.0f;
	angleV = 0.0f;
	productionflg = false;
	shakingDirection = true;
	t = 0;
	lerpflg = false;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="playerPosition">プレイヤーポジション</param>
/// <param name="targetCameraPosition">ターゲットカメラポジション</param>
void Camera::UpdateGame(VECTOR playerPosition, VECTOR targetCameraPosition)
{
	//注視点移動
	bool inputflg = false;
	DINPUT_JOYSTATE stickinput = input->GetStickInput();//スティック入力情報

	//右
	if (stickinput.Rx > 0.0f)
	{
		angleH += AngleSpeed;
		//180度を超えたら戻す
		if (angleH > DX_PI_F)
		{
			angleH -= DX_TWO_PI_F;
		}
		inputflg = true;
	}
	//左
	if (stickinput.Rx < 0.0f)
	{
		angleH -= AngleSpeed;
		//-180度を超えたら戻す
		if (angleH < -DX_PI_F)
		{
			angleH += DX_TWO_PI_F;
		}
		inputflg = true;
	}
	//上
	if (stickinput.Ry < 0.0f)
	{
		angleV -= AngleSpeed;
		//上限
		if (angleV < -DX_PI_F / 8)
		{
			angleV = -DX_PI_F / 8;
		}
		inputflg = true;
	}
	//下
	if (stickinput.Ry > 0.0f)
	{
		angleV += AngleSpeed;
		//上限
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

		lookPosition = calculation->Lerp(targetCameraPosition, lookPosition, 0.01, t);
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
	else if (productionflg)
	{
		
	}
	//視点移動なしターゲットカメラなしの通常時
	else if (!lerpflg && !productionflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
	}

	//0基準→プレイヤーと離したい距離分X軸方向にずらす→Z軸回転で高くする→Y軸回転で場所移動→プレイヤーのY座標を高くしたものを足す
	//NOTE:最後プレイヤーのY座標を高くしたものを足すようにしたのはlookPositionを足すとターゲットカメラにしたときにターゲットの場所に移動してしまうから
	MATRIX rotY = MGetRotY(angleH + DX_PI_F / 2);
	MATRIX rotZ = MGetRotZ(angleV);
	
	position = VAdd(VTransform(VTransform(VGet(PlayerDistance, 0.0f, 0.0f), rotZ), rotY), VAdd(playerPosition, VGet(0.0f, CameraPlayerTargetHeight, 0.0f)));
	//演出更新
	UpdateProduction(playerPosition);

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ゲームオーバーシーン初期化
/// </summary>
/// <param name="playerPosition"></param>
void Camera::InitializeGameOver(VECTOR playerPosition)
{
	//距離設定
	SetCameraNearFar(10.0f, 10000.0f);

	//XXX:ポジションと注視点のポジションのXZを同じにすると画面が黒くなって何も映らなくなるが少しずらすと映る
	position = playerPosition;
	position.x += 10;
	position.z += 10;
	position.y += 100;

	//注視点
	lookPosition = playerPosition;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ゲームオーバーシーン更新
/// </summary>
void Camera::UpdateGameOver()
{
	position.y += 3.0f;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ゲームクリアシーン初期化
/// </summary>
/// <param name="cameraPosition">設置するカメラポジション</param>
/// <param name="enemyPosition">注視点になる敵のポジション</param>
void Camera::InitializeGameClear(VECTOR cameraPosition, VECTOR enemyPosition)
{
	//距離設定
	SetCameraNearFar(100.0f, 20000.0f);

	position = cameraPosition;
	lookPosition = enemyPosition;

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// ゲームクリアシーン更新
/// </summary>
/// <param name="enemyPosition">注視点になる敵のポジション</param>
void Camera::UpdateGameClear(VECTOR enemyPosition)
{
	lookPosition = enemyPosition;

	//演出更新
	UpdateProduction(enemyPosition);

	//ポジション・注視点反映
	SetCameraPositionAndTarget_UpVecY(position, lookPosition);
}

/// <summary>
/// 演出更新
/// </summary>
void Camera::UpdateProduction(VECTOR playerPosition)
{
	ShakingVertical(playerPosition);
}

/// <summary>
/// 縦揺れ
/// </summary>
/// <param name="shakingPower">揺れの強さ</param>
/// <param name="shakingDirectionChangeflame">揺れる方向を変更するフレーム</param>
/// <param name="flame">再生フレーム</param>
void Camera::PlayShakingVertical(float shakingPower, int shakingDirectionChangeflame, int flame)
{
	//演出中でなければ開始
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
/// 縦揺れ
/// </summary>
/// <param name="shakingPower">揺れの強さ</param>
/// <param name="shakingDirectionChangeflame">揺れる方向を変更するフレーム</param>
/// <param name="flame">再生時間</param>
void Camera::ShakingVertical(VECTOR playerPosition)
{
	if (shakingVerticalflg)
	{
		lookPosition = playerPosition;
		lookPosition.y += CameraPlayerTargetHeight;
		//揺れ
		if (shakingDirection)
		{
			lookPosition.y += shakingPower * changeflame;
		}
		else
		{
			lookPosition.y -= shakingPower * changeflame;
		}

		//揺れる方向変更
		if (changeflame != 0 && changeflame % shakingDirectionChangeflame == 0)
		{
			shakingDirection = !shakingDirection;
			changeflame = 0;
		}

		//フレーム加算
		changeflame++;
		totalflame++;

		//終了
		if (totalflame >= playflame)
		{
			productionflg = false;
			shakingVerticalflg = false;
		}
	}
}