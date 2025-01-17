#include"DxLib.h"
#include"Input.h"
#include"Camera.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"PlayerPiercing.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
/// <param name="prevtargetLookDirection">前のキャラクターの向き</param>
PlayerPiercing::PlayerPiercing(int modelHandle, VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Squat);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	targetLookDirection = prevtargetLookDirection;

	//private変数初期化
	changeState = false;
	attackPower = 0;
	attackCapsuleStart = VGet(0.0f, -1000.0f, 0.0f);
	attackCapsuleEnd = VGet(0.0f, -1000.0f, 0.0f);
	attackChargeFlame = 0;
	attackEnd = false;
	rotate = VGet(0, 0, 0);
	attack = false;
	canInputX = false;
	attackHit = false;

	//当たり判定情報
	collisionManager = collisionManager->GetInstance();
	attackCollisionData.HitProcess = std::bind(&PlayerPiercing::OnHitObject, this, std::placeholders::_1);
	collisionManager->AddCollisionData(&attackCollisionData);
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerPiercing::~PlayerPiercing()
{
	//当たり判定情報取り除き
	collisionManager->RemoveCollisionData(&attackCollisionData);
	//フレーム初期化
	MV1ResetFrameUserLocalMatrix(modelHandle, RightArmFrameNumber);
	//アニメーション終了
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="angle">角度</param>
/// <param name="inputstate">入力状態</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
/// <param name="objectCollision">衝突オブジェクト情報</param>
/// <returns>ステート変更</returns>
bool PlayerPiercing::Update(VECTOR position,float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)
{
	moveVec = VGet(0, 0, 0);

	//連続入力防止
	if (!canInputX && (Input::InputNumber::XButton & inputstate) != Input::InputNumber::XButton)
	{
		canInputX = true;
	}

	PiercingAttack(inputstate);
	UpdateCollisionData();

	//離すとステート変更
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1 || attackEnd)
	{
		changeState = true;
	}

	return changeState;
}

void PlayerPiercing::Draw()
{
	DrawCapsule3D(attackCapsuleStart, attackCapsuleEnd, AttackCapsuleRadius, 8, GetColor(255, 105, 180), GetColor(255, 105, 180), false);
}

/// <summary>
/// 突き刺し攻撃
/// </summary>
void PlayerPiercing::PiercingAttack(int inputstate)
{
	if (!attack)
	{
		//フレーム加算
		attackChargeFlame++;

		//腕を上げる
		if (rotate.z < MaxSwingUp)
		{
			rotate.z += SwingUpSpeed;
		}
	}

	//Xボタンが押されると攻撃
	if (canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		attackPower = LowestAttackPower + attackChargeFlame / 5;

		attack = true;
	}

	//攻撃カプセル設定
	if (attack)
	{
		VECTOR capsuleCenter = MV1GetFramePosition(modelHandle, RightHandFrameNumber);
		attackCapsuleStart = VAdd(capsuleCenter, VGet(0.0f, -50.0f, 0.0f));
		attackCapsuleEnd = VAdd(capsuleCenter, VGet(0.0f, 0.0f, 0.0f));
	}

	//腕を振り下ろす
	if (attack)
	{
		rotate.z -= SwingDownSpeed;

		if (rotate.z < 0.0f)
		{
			attackEnd = true;
		}
	}

	//攻撃が当たっていたら
	if (attackHit)
	{
		attack = false;
	}

	//腕フレーム回転
	MV1SetFrameUserLocalMatrix(modelHandle, RightArmFrameNumber, MGetRotZ(rotate.z));
}

/// <summary>
/// 衝突後処理
/// </summary>
/// <param name="objectData">衝突したオブジェクト</param>
void PlayerPiercing::OnHitObject(CollisionData objectData)
{
	if (/*腕の敵*/
		objectData.tag == ObjectTag::Upperarm_E1 ||
		objectData.tag == ObjectTag::Forearm_E1 ||
		objectData.tag == ObjectTag::Hand_E1)
	{
		attackHit = true;
	}
}

/// <summary>
/// 当たり判定情報更新
/// </summary>
void PlayerPiercing::UpdateCollisionData()
{
	attackCollisionData.tag = ObjectTag::Attack_P;
	attackCollisionData.startPosition = attackCapsuleStart;
	attackCollisionData.endPosition = attackCapsuleEnd;
	attackCollisionData.radius = AttackCapsuleRadius;
	attackCollisionData.attackPower = attackPower;
	attackCollisionData.isCollisionActive = attack;
}