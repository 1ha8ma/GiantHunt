#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"PlayerStateProcessBase.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);
	position = VGet(0.0f, 0.0f, 0.0f);
	angle = 0.0f;

	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();
	nowstateKind = State::Run;

	onGround = true;

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
void Player::Update(const Camera& camera)
{
	//入力
	inputstate = input->GetInputState();
	stickstate = input->GetStickInput();

	//入力によってステート変更
	ChangeState();

	//ステート更新
	changeStateflg = nowstate->Update(inputstate, stickstate, camera);

	//移動
	moveVec = nowstate->GetmoveVec();
	position = VAdd(position, moveVec);

	//足がついているか確認
	CheckOnGround();

	//角度更新
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	//ポジション反映
	MV1SetPosition(modelHandle, position);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
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

/// <summary>
/// ステート変更
/// </summary>
void Player::ChangeState()
{
	//ジャンプ
	if (nowstateKind != State::Jump && nowstateKind != State::NormalAttack && (Input::InputNumber::AButton & inputstate) == Input::InputNumber::AButton)
	{
		delete nowstate;
		onGround = false;
		nowstateKind = State::Jump;
		nowstate = new PlayerJump(modelHandle, moveVec);
	}

	//走る
	if (nowstateKind == State::Jump && onGround ||
		nowstateKind == State::NormalAttack && changeStateflg)
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//通常攻撃
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Jump && (Input::InputNumber::BButton & inputstate) == Input::InputNumber::BButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}
}

/// <summary>
/// 足がついているか確認
/// </summary>
void Player::CheckOnGround()
{
	if (position.y <= 0.0f)
	{
		onGround = true;
		position.y = 0.0f;
	}
}