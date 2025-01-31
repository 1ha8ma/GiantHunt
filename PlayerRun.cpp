#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
#include"Camera.h"
#include"PlayerRun.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerRun::PlayerRun(int modelHandle,VECTOR prevtargetLookDirection):PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Run);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//変数初期化
	targetLookDirection = prevtargetLookDirection;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRun::~PlayerRun()
{
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
/// <returns>ここでは使わない</returns>
bool PlayerRun::Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)
{
	//移動処理
	Move(playerData, camera);
	//アニメーション再生
	PlayAnimation(0.4f, !moveflg);

	return false;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="inputstate">入力情報</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
void PlayerRun::Move(UsePlayerData playerData, Camera camera)
{
	//初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//左スティックの角度を取る
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//入力があれば
	if ((stickX != 0.0f || stickY != 0.0f))
	{
		float stickAngle = atan2(stickY, stickX);

		moveVec.x = cos(stickAngle + -camera.GetangleH());
		moveVec.z = sin(stickAngle + -camera.GetangleH());

		moveflg = true;
		targetLookDirection = moveVec;
	}

	//正規化
	if (VSize(moveVec) > 0)
	{
		moveVec = VNorm(moveVec);
	}
	//スピード加算
	moveVec = VScale(moveVec, Speed);

	//カプセルを歩いていたらベクトルの向きを変更
	if (playerData.runPlace == RunPlaceKind::capsule && playerData.onFoot)
	{
		//対象カプセルの軸を取る
		VECTOR shaft = VSub(playerData.capsuleStart, playerData.capsuleEnd);

		//カプセルの下を取る
		float underY;
		if (playerData.capsuleEnd.y <= playerData.capsuleStart.y)
		{
			//対象カプセルの軸を取る
			underY = playerData.capsuleEnd.y;
		}
		else
		{
			//対象カプセルの軸を取る
			underY = playerData.capsuleStart.y;
		}

		//カプセルの水平との角度をとる
		float cal1 = sqrtf(pow(shaft.x, 2) + pow(shaft.y, 2) + pow(shaft.z, 2));//カプセルのベクトル
		float cal2 = sqrtf(pow(shaft.x, 2) + pow(underY, 2) + pow(shaft.z, 2));//Y座標をカプセルの下にしたベクトル
		float cosTheta = VDot(shaft, VGet(shaft.x, underY, shaft.z)) / (cal1 * cal2);
		float angle = acos(cosTheta);//角度変換

		float deg = angle * (180 / DX_PI_F);//確認用

		//平面moveVecの長さ
		float horizonLen = VSize(moveVec);
		//Y座標変更
		moveVec.y = sin(angle) * horizonLen;

		if (VSize(moveVec) > 0)
		{
			targetLookDirection = moveVec;
		}
	}
}