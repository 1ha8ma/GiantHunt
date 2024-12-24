#include<math.h>
#include"DxLib.h"
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

	//private変数初期化
	moveflg = false;

	targetLookDirection = lookDir;
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
/// <param name="stickstate">スティック入力状態</param>
/// <param name="camera">カメラ</param>
/// <returns>ステート変更指示</returns>
bool PlayerClimb::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	bool stateChange = false;

	Move(stickstate, camera);
	PlayAnimation(0.5f, moveflg);

	//R1を離すとステート変更
	if ((Input::InputNumber::R1 & inputstate) != Input::InputNumber::R1)
	{
		stateChange = true;
	}

	return stateChange;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="stickstate">スティック入力状態</param>
/// <param name="camera">カメラ</param>
void PlayerClimb::Move(DINPUT_JOYSTATE stickstate, Camera camera)
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	moveflg = false;

	//左スティックの角度を取る
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;
}