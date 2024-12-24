#include"DxLib.h"
#include"Camera.h"
#include"PlayerNormalAttack.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">通常攻撃</param>
PlayerNormalAttack::PlayerNormalAttack(int modelHandle, VECTOR prevtargetLookDirection) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::NormalAttack);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//移動ベクトル初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);
	//目標の方向を前の方向にする
	targetLookDirection = prevtargetLookDirection;

	//private変数初期化
	stateChangeflg = false;
	animEndflg = false;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerNormalAttack::~PlayerNormalAttack()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
void PlayerNormalAttack::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="inputstate">入力情報</param>
/// <param name="stickstate">スティック入力情報</param>
/// <param name="camera">カメラ</param>
bool PlayerNormalAttack::Update(int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, VECTOR objectCapsuleStart, VECTOR objectCapsuleEnd)
{
	if (!animEndflg)//再生
	{
		animEndflg = PlayAnimationOnce(0.7f);
	}
	else//逆再生
	{
		stateChangeflg = ReversePlaybackAnimation(0.4f, 0.6);
	}

	//移動はしない
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	return stateChangeflg;
}