#include"DxLib.h"
#include"ArmEnemyMove.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemyMove::ArmEnemyMove(int modelHandle)
{
	this->modelHandle = modelHandle;
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemyMove::~ArmEnemyMove()
{

}

/// <summary>
/// 初期化
/// </summary>
void ArmEnemyMove::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="playerRidePlace">プレイヤーが乗っている場所</param>
void ArmEnemyMove::Update(RidePlace playerRidePlace)
{
	switch (playerRidePlace)
	{
	case RidePlace::None:
	{
		
	}
	break;
	case RidePlace::Upperarm:
	{

	}
	break;
	case RidePlace::Forearm:
	{

	}
	break;
	case RidePlace::Hand:
	{

	}
	break;
	}
}