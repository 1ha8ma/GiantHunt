#include"DxLib.h"
#include"ArmEnemyMove.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemyMove::ArmEnemyMove(int modelHandle)
{
	this->modelHandle = modelHandle;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemyMove::~ArmEnemyMove()
{

}

/// <summary>
/// ������
/// </summary>
void ArmEnemyMove::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="playerRidePlace">�v���C���[������Ă���ꏊ</param>
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