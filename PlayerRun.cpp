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
bool PlayerRun::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera)
{
	//移動処理
	Move(inputstate, stickstate, camera);
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
void PlayerRun::Move(int inputstate, DINPUT_JOYSTATE stickstate, Camera camera)
{
	//初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//左スティックの角度を取る
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//入力があれば
	if (!stickX == 0.0f || !stickY == 0.0f)
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
}