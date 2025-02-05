#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
#include"Camera.h"
#include"Input.h"
#include"PlayerClimb.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerClimb::PlayerClimb(int modelHandle,VECTOR lookDir) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Climb);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);
	animTotalTime *= 2;

	//変数初期化
	calculation = new Calculation();
	stopanimflg = false;
	targetLookDirection = lookDir;
	rotateY = 0.0f;
	rotateH = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerClimb::~PlayerClimb()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
void PlayerClimb::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="inputstate">入力状態</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
/// <param name="objectCapsuleStart">衝突しているカプセル始点</param>
/// <param name="objectCapsuleEnd">カプセル終点</param>
/// <returns>状態を変更するか</returns>
bool PlayerClimb::Update(UsePlayerData playerData, const Camera& camera,CollisionData objectCollision)
{
	bool stateChange = false;//状態変更フラグ

	Move(playerData, camera, objectCollision);
	PlayAnimation(0.5f, stopanimflg);

	//R1を離すとステート変更
	if ((Input::InputNumber::R1 & playerData.inputState) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="playerData">プレイヤーデータ</param>
/// <param name="camera"></param>
/// <param name="objectCollision"></param>
void PlayerClimb::Move(UsePlayerData playerData, Camera camera, CollisionData objectCollision )
{
	stopanimflg = true;										//アニメーション停止フラグ初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);						//moveVec初期化
	VECTOR afterPos = VGet(0.0f, 0.0f, 0.0f);				//計算後ポジション
	VECTOR positionFromShaftstart = VGet(0.0f, 0.0f, 0.0f);	//軸の始点からのポジションまでのベクトル
	
	//左スティックの角度を取る
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//対象カプセルの軸を取る
	VECTOR shaft = VSub(objectCollision.startPosition, objectCollision.endPosition);

	//登っている場所がカプセルの筒の部分か先端の球の部分か判定
	int capsuleRidePlace;	//0:筒 1:カプセル始点 2:カプセル終点

	//カプセルの両端のどちらに近いか
	float sphere1 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.startPosition);
	float sphere2 = calculation->LengthTwoPoint3D(playerData.position, objectCollision.endPosition);

	//始点に近い場合
	if (sphere1 < sphere2)
	{
		VECTOR OA = VSub(objectCollision.endPosition, objectCollision.startPosition);		//始点→終点
		VECTOR OB = VSub(playerData.position, objectCollision.startPosition);				//始点→プレイヤーポジション
		VECTOR tipPoint = VNorm(OA);														//終点→始点ベクトルの正規化 * 半径 = カプセルの先端ポジション
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);					//カプセルの先端と垂線の距離
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 1;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}
	else //終点に近い場合
	{
		VECTOR OA = VSub(objectCollision.startPosition, objectCollision.endPosition);
		VECTOR OB = VSub(playerData.position, objectCollision.endPosition);
		VECTOR tipPoint = VNorm(OA);
		tipPoint = VScale(tipPoint, -1);
		tipPoint = VScale(tipPoint, objectCollision.radius);
		VECTOR OH = calculation->OrthogonalProjectionVector(OA, OB);
		float distanceForH = calculation->LengthTwoPoint3D(OH, tipPoint);	//カプセルの先端と垂線の距離
		if (distanceForH < objectCollision.radius)
		{
			capsuleRidePlace = 2;
		}
		else
		{
			capsuleRidePlace = 0;
		}
	}

	//球にいる場合の球とプレイヤーの角度計算
	if (capsuleRidePlace == 1)
	{
		CalculationAngle(playerData.position, objectCollision.startPosition);
	}
	if (capsuleRidePlace == 2)
	{
		CalculationAngle(playerData.position, objectCollision.endPosition);
	}

	//上
	if (stickY > 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//軸の垂直方向に回転
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, -RotateSpeed, positionFromShaftstart);
			//計算前と計算後の差
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;
			
			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//下
	if (stickY < 0)
	{
		if (capsuleRidePlace == 0)
		{
			stopanimflg = false;
			//軸の垂直方向に回転
			positionFromShaftstart = VSub(playerData.position, objectCollision.startPosition);
			afterPos = calculation->RodriguesRotationFormula(shaft, RotateSpeed, positionFromShaftstart);
			//計算前と計算後の差
			moveVec = VSub(afterPos, positionFromShaftstart);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateY -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//左
	if (stickX < 0)
	{
		if (capsuleRidePlace == 0)
		{
			//軸の方向に移動
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH -= RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}
	//右
	if (stickX > 0)
	{
		if (capsuleRidePlace == 0)
		{
			//軸の方向に移動
			stopanimflg = false;

			VECTOR shaftVec = VNorm(shaft);
			VECTOR speedVec = VScale(shaftVec, -Speed);
			moveVec = VAdd(moveVec, speedVec);
		}
		if (capsuleRidePlace == 1)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.startPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.startPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.startPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
		if (capsuleRidePlace == 2)
		{
			stopanimflg = false;

			rotateH += RotateSpeed;

			afterPos.x = objectCollision.endPosition.x + objectCollision.radius * cos(rotateY) * cos(rotateH);
			afterPos.y = objectCollision.endPosition.y + objectCollision.radius * sin(rotateY);
			afterPos.z = objectCollision.endPosition.z + objectCollision.radius * cos(rotateY) * sin(rotateH);

			//計算前と計算後の差
			moveVec = VSub(afterPos, playerData.position);
		}
	}

	//オブジェクトのmoveVecを加算
	moveVec = VAdd(moveVec, objectCollision.moveVec);
}

/// <summary>
/// 角度計算
/// </summary>
/// <param name="playerPosition">プレイヤーポジション</param>
/// <param name="objectPosition">判定対象のポジション</param>
void PlayerClimb::CalculationAngle(VECTOR playerPosition, VECTOR objectPosition)
{
	//差分
	float dx = playerPosition.x - objectPosition.x;
	float dy = playerPosition.y - objectPosition.y;
	float dz = playerPosition.z - objectPosition.z;

	//半径
	float r = sqrt(dx * dx + dy * dy + dz * dz);

	//角度計算
	rotateY = asinf(dy / r);
	rotateH = atan2f(dz, dx);
}