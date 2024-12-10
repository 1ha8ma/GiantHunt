#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Input.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);
	position = VGet(0.0f, 200.0f, 0.0f);
	angle = 0.0f;

	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	Move();
	UpdateAngle();
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);

	DrawFormatString(100, 100, GetColor(128, 127, 128), "X:%d Y:%d Z:%d", position.x, position.y, position.z);
}

/// <summary>
/// 移動
/// </summary>
void Player::Move()
{
	moveVec = VGet(0, 0, 0);

	if ((Input::InputNumber::Right_L & input->GetInputState()) == Input::InputNumber::Right_L)
	{
		moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
	}
	if ((Input::InputNumber::Left_L & input->GetInputState()) == Input::InputNumber::Left_L)
	{
		moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
	}
	if ((Input::InputNumber::Up_L & input->GetInputState()) == Input::InputNumber::Up_L)
	{
		moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
	}
	if ((Input::InputNumber::Down_L & input->GetInputState()) == Input::InputNumber::Down_L)
	{
		moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -1.0f));
	}

	targetLookDirection = moveVec;

	//移動量
	if (VSize(moveVec) > 0)
	{
		moveVec = VNorm(moveVec);
	}
	moveVec = VScale(moveVec, Speed);

	position = VAdd(position, moveVec);
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 角度更新
/// </summary>
void Player::UpdateAngle()
{
	//移動方向にモデルの方向を近づける
	float targetAngle;//目標の角度
	float difference;//目標角度と現在の角度の差

	//目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	//目標の角度と現在の角度との差を割り出す
	//最初は引き算
	difference = targetAngle - angle;

	//ある方向からある方向の差が180度以上になることはないので差が180度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//角度の差を0に近づける
	if (difference > 0.0f)//差がマイナスの場合
	{
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//差がプラスの場合
	{
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//モデルの角度を更新
	angle = targetAngle - difference;

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
}