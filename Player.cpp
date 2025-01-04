#include"DxLib.h"
#include"CollisionData.h"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"CollisionManager.h"
#include"CollisionData.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
#include"PlayerClimb.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);
	position = VGet(0.0f, 0.0f, 0.0f);
	drawPosition = position;
	angle = 0.0f;

	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();
	nowstateKind = State::Run;
	collisionManager = collisionManager->GetInstance();

	//private変数初期化
	onGround = true;
	isCatch = false;
	isStand = false;
	fallSpeed = 0.0f;
	hitObjectCapStart = VGet(0.0f, 0.0f, 0.0f);
	hitObjectCapEnd = VGet(0.0f, 0.0f, 0.0f);
	runPlace = PlayerStateProcessBase::RunPlaceKind::ground;

	//当たり判定
	//衝突後の処理を渡す
	collisionData.HitProcess = std::bind(&Player::OnHitObject, this, std::placeholders::_1);
	//当たり判定に必要なデータを渡す
	collisionManager->AddCollisionData(&collisionData);

	//ポジション反映
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	delete nowstate;
	delete input;
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
	changeStateflg = nowstate->Update(position, inputstate, stickstate, camera, hitObjectCapStart, hitObjectCapEnd);

	//移動
	moveVec = nowstate->GetmoveVec();
	//足がついているか確認
	CheckOnGround();
	//落下速度追加
	moveVec = VSub(moveVec, VGet(0.0f, fallSpeed, 0.0f));
	//ポジション反映
	position = VAdd(position, moveVec);

	//描画位置修正
	CorrectionDrawPosition();
	
	//角度更新
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	nowstate->SetRunPlace(runPlace);

	//ポジション等更新
	UpdateCapsule();
	UpdateCollisionData();

	//フラグ初期化
	isCatch = false;
	isStand = false;
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1SetPosition(modelHandle, drawPosition);
	MV1DrawModel(modelHandle);

	DrawCapsule3D(capStart, capEnd, CapsuleRadius, 8, GetColor(220, 20, 60),GetColor(220,20,60), FALSE);
}

/// <summary>
/// 衝突した時の処理
/// </summary>
/// <param name="hitObjectData">衝突したもの</param>
void Player::OnHitObject(CollisionData hitObjectData)
{
	hitObjectCapStart = hitObjectData.startPosition;
	hitObjectCapEnd = hitObjectData.endPosition;

	//衝突したオブジェクトごとに処理を変更
	//敵の攻撃
	if (hitObjectData.tag == ObjectTag::Attack_E1 ||
		hitObjectData.tag == ObjectTag::Attack_E2)
	{
		//HP減少
		HP -= hitObjectData.attackPower;
	}

	//カプセル
	if (hitObjectData.tag == ObjectTag::Wood1 || hitObjectData.tag == ObjectTag::Wood2 ||	//木
		hitObjectData.tag == ObjectTag::Upperarm_E1 || hitObjectData.tag == ObjectTag::Forearm_E1 || hitObjectData.tag == ObjectTag::Hand_E1)	//腕の敵
	{
		if (nowstateKind != State::Climb)
		{
			CollisionPushBack(hitObjectData);
		}
		//オブジェクトの半分より上にいたら

		isCatch = true;
		runPlace= PlayerStateProcessBase::RunPlaceKind::capsule;
	}
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

	//反映
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

	//登りモーションの時は反転
	if (nowstateKind == State::Climb)
	{
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle, 0.0f));
	}
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
		nowstateKind == State::NormalAttack && changeStateflg ||
		nowstateKind == State::Climb && changeStateflg || nowstateKind == State::Climb && !isCatch)
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//通常攻撃
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Jump && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}

	//掴まり
	if (nowstateKind != State::Climb && isCatch&& (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1)
	{
		delete nowstate;
		nowstateKind = State::Climb;
		nowstate = new PlayerClimb(modelHandle,targetLookDirection);
	}
}

/// <summary>
/// 足がついているか確認
/// </summary>
void Player::CheckOnGround()
{
	//着地したとき
	if (!onGround && position.y < 0.0f || !onGround && isCatch)
	{
		onGround = true;
		moveVec.y = 0.0f;

		//振動
		StartJoypadVibration(DX_INPUT_PAD1, 500, 100, -1);
	}

	//ついているか
	if (position.y > 0.0f && !isCatch)
	{
		onGround = false;
		runPlace = PlayerStateProcessBase::RunPlaceKind::air;
	}

	//足がついていなければ落下
	if (!onGround)
	{
		fallSpeed += Gravity;
	}
	else
	{
		fallSpeed = 0.0f;
	}

	//下まで行かないように
	if (position.y < 0.0f)
	{
		runPlace = PlayerStateProcessBase::RunPlaceKind::ground;
		position.y = 0.0f;
	}
}

/// <summary>
/// カプセル更新
/// </summary>
void Player::UpdateCapsule()
{
	capStart = VAdd(position, VGet(0.0f, 100.0f, 0.0f));
	capEnd = VAdd(position, VGet(0.0f, 50.0f, 0.0f));
}

/// <summary>
/// 当たり判定情報更新
/// </summary>
void Player::UpdateCollisionData()
{
	collisionData.tag = ObjectTag::Player;
	collisionData.position = position;
	collisionData.startPosition = capStart;
	collisionData.endPosition = capEnd;
	collisionData.radius = CapsuleRadius;
	collisionData.attackPower = AttackPower;
	collisionData.isCollisionActive = true;
}

/// <summary>
/// 描画位置修正
/// </summary>
void Player::CorrectionDrawPosition()
{
	//基本
	drawPosition = position;

	//ジャンプ
	if (nowstateKind == State::Jump)
	{
		drawPosition.y -= 60.0f;
	}

	//登り
	if (nowstateKind == State::Climb)
	{
		drawPosition.y -= 90.0f;
		drawPosition.x -= cos(angle) * 100.0f;
		drawPosition.z -= sin(-angle) * 100.0f;
	}
}

/// <summary>
/// 衝突後の押し戻し
/// </summary>
void Player::CollisionPushBack(CollisionData hitObjectData)
{
	//半径の合計
	float radiusSum = hitObjectData.radius + collisionData.radius;

	//ベクトルのサイズを計算
	//2つの線分の最短距離を求める
	float len = Segment_Segment_MinLength(capStart, capEnd, hitObjectData.startPosition, hitObjectData.endPosition);
	float distance = radiusSum - len;

	//衝突したものとプレイヤーの向きのベクトルを取る
	VECTOR dir = VSub(hitObjectData.position, position);

	//押し戻し
	dir = VNorm(dir);
	VECTOR pushBackVec = VScale(dir, -distance);

	position = VAdd(position, pushBackVec);

	if (position.y < 0.0f)
	{
		position.y = 0.0f;
	}
}