#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemySwing.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="modelScale">���f���T�C�Y</param>
ArmEnemySwing::ArmEnemySwing(int modelHandle, float modelScale,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle, modelScale)
{
	//private�ϐ�������
	rotate = prevRotate;
	moveEnd = false;
	moveState = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemySwing::~ArmEnemySwing()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <returns>��ԕύX</returns>
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