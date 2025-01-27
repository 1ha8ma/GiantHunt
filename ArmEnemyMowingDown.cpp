#include"DxLib.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"SoundEffect.h"
#include"Camera.h"
#include"ArmEnemyMowingDown.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle"></param>
ArmEnemyMowingDown::ArmEnemyMowingDown(int modelHandle,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle)
{
	//�C���X�^���X��
	se = new SoundEffect();

	//�ϐ�������
	moveState = 0;
	moveEnd = false;
	rotate.x = -0.5;
	rotate.z = 0;

	//�����蔻����
	attackCapsuleStart = VGet(0, 0, 0);
	attackCapsuleEnd = VGet(0, 0, 0);
	onAttackCollision = false;
	attackHit = false;
	collisionData.HitProcess = std::bind(&ArmEnemyMowingDown::OnHitObject, this, std::placeholders::_1);

	collisionManager = collisionManager->GetInstance();
	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemyMowingDown::~ArmEnemyMowingDown()
{
	collisionManager->RemoveCollisionData(&collisionData);
}

/// <summary>
/// �X�V
/// </summary>
bool ArmEnemyMowingDown::Update(Camera* camera)
{
	switch (moveState)
	{
	case 0:
	{
		rotate.x += 0.01;
		rotate.z += 0.01;
		onAttackCollision = false;

		if (rotate.x > 0.2)
		{
			moveState++;
		}
	}
	break;
	case 1:
	{
		rotate.x -= 0.01;
		rotate.z -= 0.01;
		if (!attackHit)
		{
			onAttackCollision = true;
		}
		else
		{
			onAttackCollision = false;
		}

		if (rotate.x < -0.7)
		{
			//�㉺�h��
			camera->PlayShakingVertical(1, 10, 50);
			//�U��
			StartJoypadVibration(DX_INPUT_PAD1, 200, 900, -1);
			//se�Đ�
			se->PlaySE(SoundEffect::SEKind::MowinDownAttack);
			moveState++;
		}
	}
	break;
	case 2:
	{
		rotate.x += 0.005;
		onAttackCollision = false;

		if (rotate.x > -0.2)
		{
			moveState++;
			moveEnd = true;
		}
	}
	break;
	}

	MATRIX Mrotate = MMult(MGetRotX(rotate.x), MGetRotZ(rotate.z));
	MV1SetFrameUserLocalMatrix(modelHandle, (int)ArmEnemyFrameIndex::Upperarm, Mrotate);

	//�U�������蔻��
	attackCapsuleStart = MV1GetFramePosition(modelHandle, (int)ArmEnemyFrameIndex::Hand);
	attackCapsuleEnd = MV1GetFramePosition(modelHandle, (int)ArmEnemyFrameIndex::Hand);

	UpdateCollisionData();

	return moveEnd;
}

/// <summary>
/// �`��
/// </summary>
void ArmEnemyMowingDown::Draw()
{
	if (onAttackCollision)
	{
		DrawCapsule3D(attackCapsuleStart, attackCapsuleEnd, AttackCapsuleRadius, 8, GetColor(173, 255, 47), GetColor(173, 255, 47), false);
	}
}

/// <summary>
/// �I�u�W�F�N�g�Փˎ��̏���
/// </summary>
/// <param name="objectData">�Փ˂����I�u�W�F�N�g�̃f�[�^</param>
void ArmEnemyMowingDown::OnHitObject(CollisionData* objectData)
{
	if (objectData->tag == ObjectTag::PlayerWholeBody)
	{
		attackHit = true;
	}
}

/// <summary>
/// �����蔻����
/// </summary>
void ArmEnemyMowingDown::UpdateCollisionData()
{
	collisionData.tag = ObjectTag::EnemyAttack;
	collisionData.startPosition = attackCapsuleStart;
	collisionData.endPosition = attackCapsuleEnd;
	collisionData.radius = AttackCapsuleRadius;
	collisionData.attackPower = AttackPower;
	collisionData.isCollisionActive = onAttackCollision;
}