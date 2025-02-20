#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemyFallDown.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
/// <param name="modelScale">モデルスケール</param>
ArmEnemyFallDown::ArmEnemyFallDown(int modelHandle) :ArmEnemyMoveBase(modelHandle)
{
	//変数初期化
	moveState = 0;
	rotate = VGet(0, 0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemyFallDown::~ArmEnemyFallDown()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="camera">カメラ</param>
/// <returns>動きの終了</returns>
bool ArmEnemyFallDown::UpdateFallDown(Camera* camera)
{
	bool moveEnd = false;
	switch (moveState)
	{
	case 0:
	{
		rotate.x += 0.0035f;

		if (rotate.x >= 0.7f)
		{
			moveState++;
		}
	}
	break;
	case 1:
	{
		rotate.x -= 0.008f;

		if (rotate.x <= -0.6f)
		{
			camera->PlayShakingVertical(3, 10, 50);
			//振動
			StartJoypadVibration(DX_INPUT_PAD1, 300, 1200, -1);
			moveState++;
		}
	}
	break;
	case 2:
	{
		moveEnd = true;
	}
	break;
	}

	//回転行列適応
	MATRIX Mrotate = MMult(MGetRotX(rotate.x), MGetRotZ(rotate.z));
	MV1SetFrameUserLocalMatrix(modelHandle, (int)ArmEnemyFrameIndex::Upperarm, Mrotate);

	return moveEnd;
}

/// <summary>
/// 描画(確認用)
/// </summary>
void ArmEnemyFallDown::Draw()
{

}