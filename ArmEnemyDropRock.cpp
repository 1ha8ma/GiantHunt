#include"DxLib.h"
#include"CollisionData.h"
#include"CollisionManager.h"
#include"SoundEffect.h"
#include"Camera.h"
#include"ArmEnemyAttackRock.h"
#include"ArmEnemyDropRock.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="modelHandle"></param>
ArmEnemyDropRock::ArmEnemyDropRock(int modelHandle,VECTOR prevRotate) :ArmEnemyMoveBase(modelHandle)
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
	collisionData.HitProcess = std::bind(&ArmEnemyDropRock::OnHitObject, this, std::placeholders::_1);

	collisionManager = collisionManager->GetInstance();
	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemyDropRock::~ArmEnemyDropRock()
{
	collisionManager->RemoveCollisionData(&collisionData);
	delete se;
	delete rock;
}

/// <summary>
/// �X�V
/// </summary>
bool ArmEnemyDropRock::Update(Camera* camera,VECTOR playerPosition)
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
		rotate.x -= 0.02f;
		rotate.z -= 0.005f;
		if (!attackHit)
		{
			onAttackCollision = true;
		}
		else
		{
			onAttackCollision = false;
		}

		if (rotate.x < -1.4f)
		{
			//�㉺�h��
			camera->PlayShakingVertical(1, 10, 50);
			//�U��
			StartJoypadVibration(DX_INPUT_PAD1, 200, 900, -1);
			//se�Đ�
			se->PlaySE(SoundEffect::SEKind::MowinDownAttack);
			rock = new ArmEnemyAttackRock(playerPosition, camera);
			moveState++;
		}
	}
	break;
	case 2:
	{
		onAttackCollision = false;
		rock->Update();

		if (rotate.x < -0.2)
		{
			rotate.x += 0.005;
		}
		else
		{
			moveState++;
		}
	}
	break;
	case 3:
	{
		rock->Update();

		if (rock->GetEnd())
		{
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
void ArmEnemyDropRock::Draw()
{
	if (moveState >= 2)
	{
		rock->Draw();
	}

	//�m�F�p
	if (onAttackCollision)
	{
		DrawCapsule3D(attackCapsuleStart, attackCapsuleEnd, AttackCapsuleRadius, 8, GetColor(173, 255, 47), GetColor(173, 255, 47), false);
	}
}

/// <summary>
/// �I�u�W�F�N�g�Փˎ��̏���
/// </summary>
/// <param name="objectData">�Փ˂����I�u�W�F�N�g�̃f�[�^</param>
void ArmEnemyDropRock::OnHitObject(CollisionData* objectData)
{
	if (objectData->tag == ObjectTag::PlayerWholeBody)
	{
		attackHit = true;
	}
}

/// <summary>
/// �����蔻����
/// </summary>
void ArmEnemyDropRock::UpdateCollisionData()
{
	collisionData.tag = ObjectTag::EnemyAttack;
	collisionData.startPosition = attackCapsuleStart;
	collisionData.endPosition = attackCapsuleEnd;
	collisionData.radius = AttackCapsuleRadius;
	collisionData.attackPower = AttackPower;
	collisionData.isCollisionActive = onAttackCollision;
}