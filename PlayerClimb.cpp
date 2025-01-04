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
	calculation = new Calculation();
	stopanimflg = false;

	targetLookDirection = lookDir;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerClimb::~PlayerClimb()
{
	//delete calculation;
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
bool PlayerClimb::Update(VECTOR position,int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	bool stateChange = false;//状態変更フラグ

	Move(position,stickstate, camera,objectCapsuleStart,objectCapsuleEnd);
	PlayAnimation(0.5f, stopanimflg);

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
void PlayerClimb::Move(VECTOR position, DINPUT_JOYSTATE stickstate, Camera camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	VECTOR afterPos = VGet(0.0f, 0.0f, 0.0f);				//計算後ポジション
	VECTOR positionFromShaftstart = VGet(0.0f, 0.0f, 0.0f);	//軸の始点からのポジションまでのベクトル	
	stopanimflg = true;

	//左スティックの角度を取る
	float stickX = stickstate.X;
	float stickY = -stickstate.Y;

	//対象カプセルの軸を取る
	VECTOR shaft = VSub(objectCapsuleStart, objectCapsuleEnd);

	//上
	if (stickY > 0)
	{
		stopanimflg = false;
		//軸の垂直方向に回転
		positionFromShaftstart = VSub(position, objectCapsuleStart);
		afterPos = calculation->RodriguesRotationFormula(shaft, -RotateSpeed, positionFromShaftstart);
		//計算前と計算後の差
		moveVec = VSub(afterPos, positionFromShaftstart);
	}
	//下
	if (stickY < 0)
	{
		stopanimflg = false;
		//軸の垂直方向に回転
		positionFromShaftstart = VSub(position, objectCapsuleStart);
		afterPos = calculation->RodriguesRotationFormula(shaft, RotateSpeed, positionFromShaftstart);
		//計算前と計算後の差
		moveVec = VSub(afterPos, positionFromShaftstart);
	}
	//左
	if (stickX < 0)
	{
		//軸の方向に移動
		stopanimflg = false;

		VECTOR shaftVec = VNorm(shaft);
		VECTOR speedVec = VScale(shaftVec, Speed);
		moveVec = VAdd(moveVec, speedVec);
		
	}
	//右
	if (stickX > 0)
	{
		//軸の方向に移動
		stopanimflg = false;

		VECTOR shaftVec = VNorm(shaft);
		VECTOR speedVec = VScale(shaftVec, -Speed);
		moveVec = VAdd(moveVec, speedVec);
	}
}