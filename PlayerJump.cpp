#include<math.h>
#include"DxLib.h"
#include"CollisionData.h"
#include"Camera.h"
#include"PlayerJump.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
PlayerJump::PlayerJump(int modelHandle,VECTOR prevmoveVec) :PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Jump);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	//水平方向のベクトルを前までの移動ベクトルの向きにする
	moveVecV = prevmoveVec;
	moveVecV.y = 0.0f;

	jumpPower = FirstJumpPower;
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerJump::~PlayerJump()
{
	DetachAnimation(nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
void PlayerJump::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerData">プレイヤーデータ</param>
/// <param name="camera">カメラ</param>
/// <param name="objectCollision">衝突したオブジェクト</param>
/// <returns>終了</returns>
bool PlayerJump::Update(UsePlayerData playerData, const Camera& camera, CollisionData objectCollision)
{
	Move();
	//アニメーション再生
	PlayAnimationOnce(1.3f);

	return false;
}

/// <summary>
/// 移動処理
/// </summary>
void PlayerJump::Move()
{
	//初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	//水平方向を追加
	moveVec = VAdd(moveVec, moveVecV);

	//高さ加算
	moveVec.y += jumpPower;

	targetLookDirection = moveVec;
}