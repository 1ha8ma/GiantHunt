#include"DxLib.h"
#include"SoundEffect.h"
#include"Camera.h"
#include"ArmEnemySwing.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="modelScale">���f���T�C�Y</param>
ArmEnemySwing::ArmEnemySwing(int modelHandle, float modelScale,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle, modelScale)
{
	//�C���X�^���X��
	se = new SoundEffect();
	
	//private�ϐ�������
	//rotate = prevRotate;
	rotate = VGet(0, 0, 0);
	moveEnd = false;
	moveState = 0;

	//se�Đ�
	se->PlaySE(SoundEffect::SEKind::Swing);

	//�U��
	StartJoypadVibration(DX_INPUT_PAD1, 150, -1, -1);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemySwing::~ArmEnemySwing()
{
	//�U�����~�߂�
	StopJoypadVibration(DX_INPUT_PAD1, -1);
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
		rotate.z += 0.007;

		if (rotate.z > 1)
		{
			moveState++;
		}
	}
	break;
	case 1:
	{
		rotate.z -= 0.007f;
		if (rotate.z < -1)
		{
			moveState++;
		}
	}
	break;
	case 2:
	{
		rotate.z += 0.007f;
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