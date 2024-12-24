#include<math.h>
#include"DxLib.h"
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

	runPlace = false;

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
/// <param name="inputstate">入力情報</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
bool PlayerRun::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	//移動処理
	Move(inputstate, stickstate, camera, objectCapsuleStart, objectCapsuleEnd);
	//アニメーション再生
	PlayAnimation(0.4f,!moveflg);

	return false;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="inputstate">入力情報</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
void PlayerRun::Move(int inputstate, DINPUT_JOYSTATE stickstate, Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	//初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//左スティックの角度を取る
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//入力があれば
	if (stickX != 0.0f || stickY != 0.0f)
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

	//もし斜めを歩いていたらベクトルの向きを変更
	if (runPlace)
	{
		//対象カプセルの軸を取る
		VECTOR shaft = VSub(objectCapsuleStart, objectCapsuleEnd);

		//カプセルの下を取る
		float underY;
		if (objectCapsuleEnd.y <= objectCapsuleStart.y)
		{
			//対象カプセルの軸を取る
			underY = objectCapsuleEnd.y;
		}
		else
		{
			//対象カプセルの軸を取る
			underY = objectCapsuleStart.y;
		}

		//角度をとる
		float cal1 = sqrtf(pow(shaft.x, 2) + pow(shaft.y, 2) + pow(shaft.z, 2));//カプセルのベクトル
		float cal2 = sqrtf(pow(shaft.x, 2) + pow(underY, 2) + pow(shaft.z, 2));//Y座標をカプセルの下にしたベクトル
		float cosTheta = VDot(shaft, VGet(shaft.x, underY, shaft.z)) / (cal1 * cal2);
		float angle = acos(cosTheta);//角度変換

		float deg = angle * (180 / DX_PI_F);//確認用

		//平面の長さ
		float horizonLen = sqrt(pow(moveVec.x, 2) + pow(moveVec.z, 2));
		//y座標変更
		moveVec.y = sin(angle) * horizonLen;
		
		if (VSize(moveVec) > 0)
		{
			targetLookDirection = moveVec;
		}
	}
}