#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemyHandUp.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
ArmEnemyHandUp::ArmEnemyHandUp(int modelHandle,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle)
{
	//�ϐ�������
	rotate = prevRotate;
	moveState = 0;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemyHandUp::~ArmEnemyHandUp()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="camera">�J�������</param>
/// <returns>�����̏I��</returns>
bool ArmEnemyHandUp::Update(Camera* camera)
{
	bool moveEnd = false;

	switch (moveState)
	{
	case 0:
	{
		rotate.x += 0.005f;
		if (rotate.x > 0.8f)
		{
			moveState++;
		}
	}
	break;
	case 1:
	{
		rotate.x -= 0.005f;
		if (rotate.x < 0)
		{
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

	//��]�s��K��
	MV1SetFrameUserLocalMatrix(modelHandle, (int)ArmEnemyFrameIndex::Upperarm, MGetRotX(rotate.x));

	return moveEnd;
}