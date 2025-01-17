#include"DxLib.h"
#include"CollisionData.h"
#include"Input.h"
#include"Camera.h"
#include"PlayerSquat.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerSquat::PlayerSquat(int modelHandle,VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Squat);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//モデルの向き設定
	targetLookDirection = prevtargetLookDirection;

	//private変数初期化
	changeState = false;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerSquat::~PlayerSquat()
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
/// <returns>ステート変更</returns>
bool PlayerSquat::Update(VECTOR position, float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)
{
	moveVec = VGet(0, 0, 0);

	PlayAnimation(1.0f, false);

	//R1を離すとステート変更
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1)
	{
		changeState = true;
	}

	return changeState;
}