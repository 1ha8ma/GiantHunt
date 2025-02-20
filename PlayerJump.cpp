#include<fstream>
#include<math.h>
#include"DxLib.h"
#include"nlohmann/json.hpp"
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

	//ファイル読み込み
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//変数初期化
	moveVecV = prevmoveVec;
	moveVecV.y = 0.0f;
	targetLookDirection = prevmoveVec;
	FirstJumpPower = jsonData["JumpPower"];
	MoveSpeedHorizon = jsonData["FallingHorizonMoveSpeed"];
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
	Move(playerData, camera);
	//アニメーション再生
	PlayAnimationOnce(1.3f);

	return false;
}

/// <summary>
/// 移動処理
/// </summary>
void PlayerJump::Move(UsePlayerData playerData, Camera camera)
{
	//初期化
	moveVec = VGet(0.0f, 0.0f, 0.0f);

	//左スティックの角度を取る
	float stickX = playerData.stickState.X;
	float stickY = -playerData.stickState.Y;

	//入力があれば
	if ((stickX != 0.0f || stickY != 0.0f))
	{
		float stickAngle = atan2(stickY, stickX);

		moveVec.x = cos(stickAngle + -camera.GetangleH());
		moveVec.z = sin(stickAngle + -camera.GetangleH());

		moveVec = VScale(moveVec, MoveSpeedHorizon);
	}

	//水平方向を追加
	moveVec = VAdd(moveVec, moveVecV);

	//高さ加算
	moveVec.y += jumpPower;
}