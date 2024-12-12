#include<math.h>
#include"DxLib.h"
#include"Input.h"
#include"Camera.h"
#include"PlayerRun.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerRun::PlayerRun(int modelHandle):PlayerStateProcessBase(modelHandle)
{
	//アニメーションアタッチ
	nowPlayAnim = MV1AttachAnim(modelHandle, PlayerAnimationNumber::Run);
	//アニメーションの総再生時間を取る
	animTotalTime = MV1GetAnimTotalTime(modelHandle, nowPlayAnim);

	input = new Input();
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
/// <param name="cameralookAngleXZ">カメラの平面角度</param>
/// <returns>次のステート</returns>
PlayerStateProcessBase* PlayerRun::Update(const Camera& camera)
{
	Move(camera);
	PlayAnimation(0.4f,!moveflg);

	return this;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="cameralookAngleXZ"></param>
void PlayerRun::Move(Camera camera)
{
	moveVec = VGet(0, 0, 0);
	moveflg = false;

	//左スティックの角度を取る
	float inputX = input->GetStickInput().X;
	float inputY = -input->GetStickInput().Y;

	//入力があれば
	if (!inputX == 0 || !inputY == 0)
	{
		float ang = atan2(inputY, inputX);

		moveVec.x = cos(ang + -camera.GetangleH());
		moveVec.z = sin(ang + -camera.GetangleH());

		moveflg = true;
		targetLookDirection = moveVec;
	}

	//移動量
	if (VSize(moveVec) > 0)
	{
		moveVec = VNorm(moveVec);
	}
	moveVec = VScale(moveVec, Speed);
}

void PlayerRun::Draw()
{
	input->Draw();
}