#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemySwing.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelHandle">モデルハンドル</param>
/// <param name="modelScale">モデルサイズ</param>
ArmEnemySwing::ArmEnemySwing(int modelHandle, float modelScale,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle, modelScale)
{
	//private変数初期化
	rotate = prevRotate;
	moveEnd = false;
	moveState = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemySwing::~ArmEnemySwing()
{

}

/// <summary>
/// 更新
/// </summary>
/// <returns>状態変更</returns>
bool ArmEnemySwing::Update(Camera* camera)
{
	switch (moveState)
	{
	case 0:
	{
		rotate.z += 0.01;

		if (rotate.z > 1)
		{
			moveState++;
		}
	}
	break;
	case 1:
	{
		rotate.z -= 0.01f;
		if (rotate.z < -1)
		{
			moveState++;
		}
	}
	break;
	case 2:
	{
		rotate.z += 0.01f;
		if (rotate.z >= BasicRotate.z)
		{
			rotate.z = BasicRotate.z;
			moveEnd = true;
		}
	}
	break;
	}

	MATRIX Mrotate = MGetRotZ(rotate.z);
	//Mrotate = MMult(Mrotate, MGetRotX(rotate.x));

	MV1SetFrameUserLocalMatrix(modelHandle, (int)ArmEnemyFrameIndex::Upperarm, Mrotate);

	return moveEnd;
}