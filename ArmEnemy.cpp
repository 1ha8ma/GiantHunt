#include"DxLib.h"
#include"Loader.h"
#include"Calculation.h"
#include"Camera.h"
#include"EnemyParts.h"
#include"ArmEnemyMoveBase.h"
#include"ArmEnemyIdle.h"
#include"ArmEnemyMowingDown.h"
#include"ArmEnemySwing.h"
#include"ArmEnemyFallDown.h"
#include"ArmEnemyHandUp.h"
#include"ArmEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemy::ArmEnemy()
{
	Loader* loader = loader->GetInstance();
	//���f�����[�h
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//�X�e�[�^�X������
	HP = MaxHP;

	//private�ϐ�������
	calclation = new Calculation();
	position = VGet(2000.0f, -5000.0f, 6550.0f);
	playerRidePlace = RidePlace::None;
	moveChangeflg = false;
	playerRideFlame = 0;
	playerRideflg = false;
	playerRideMoveStartflg = false;

	//�`�惂�f��
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//���ʓ����蔻��
	parts.clear();
	parts.push_back(new EnemyParts(ObjectTag::Upperarm_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm-1, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm, 600));
	parts.push_back(new EnemyParts(ObjectTag::Forearm_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm - 1, 500));
	parts.push_back(new EnemyParts(ObjectTag::Hand_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm, 300));
	parts.push_back(new EnemyParts(ObjectTag::WeakPoint_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand - 1, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand - 1, 320));

	move = new ArmEnemyIdle(modelHandle, VGet(0, 0, 0));
	nowMoveKind = MoveKind::Idle;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemy::~ArmEnemy()
{
	for (int i = 0; i < parts.size(); i++)
	{
		delete parts[i];
	}

	parts.clear();
}

/// <summary>
/// ������
/// </summary>
void ArmEnemy::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
bool ArmEnemy::Update(VECTOR playerPos,Camera* camera)
{
	//�v���C���[�̏���Ă���֌W������
	playerRidePlace = RidePlace::None;
	playerRideflg = false;

	//HP�������Ȃ�����
	bool HPoutflg = false;

	for (int i = 0; i < parts.size(); i++)
	{
		if (parts[i]->GetIsPlayerRide())
		{
			playerRideflg = true;
			if (i == 0)
			{
				playerRidePlace = RidePlace::Upperarm;
			}
			else if (i == 1)
			{
				playerRidePlace = RidePlace::Forearm;
			}
			else if (i == 2)
			{
				playerRidePlace = RidePlace::Hand;
			}
		}
	}

	//�v���C���[������Ă�����
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && playerRideflg)
	{
		playerRideFlame++;

		if (playerRideFlame > PlayerRideMoveStateFlame)
		{
			playerRideFlame = 0;
			playerRideMoveStartflg = true;
		}
	}

	//�X�V
	for (int i = 0; i < parts.size(); i++)
	{
		HP -= parts[i]->TakeDamage();
		parts[i]->Update();
	}
	if (HP < 0)
	{
		HP = 0;
	}

	//HP�m�F
	if (HP == 0)
	{
		HPoutflg = true;
	}

	//����^�[�Q�b�g�J�����ɐݒ�
	targetCameraPosition = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);
	//�����X�V
	moveChangeflg = move->Update(camera);
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->CalculationMoveVec();
	}

	//�����̕ύX�m�F
	ChangeMove(playerPos);

	MV1SetPosition(modelHandle, position);

	return HPoutflg;
}

/// <summary>
/// �|���ꂽ��̏�����
/// </summary>
void ArmEnemy::InitializeFallDown()
{
	VECTOR prevRotate = move->GetRotate();
	delete move;
	nowMoveKind = MoveKind::FallDown;
	move = new ArmEnemyFallDown(modelHandle);
}

/// <summary>
/// �|���ꂽ��̍X�V
/// </summary>
/// <returns>�������I�������</returns>
bool ArmEnemy::UpdateFallDown(Camera* camera)
{
	bool moveEnd = false;
	moveEnd = move->UpdateFallDown(camera);

	//�p�[�c�A�G�t�F�N�g�̍X�V
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}

	//����^�[�Q�b�g�J�����ɐݒ�
	targetCameraPosition = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);

	MV1SetPosition(modelHandle, position);
	return moveEnd;
}

/// <summary>
/// �`��
/// </summary>
void ArmEnemy::Draw()
{
	MV1DrawModel(modelHandle);

	//�����蔻��m�F�p
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}
	//move->Draw();
}

/// <summary>
/// �����̕ύX
/// </summary>
/// <param name="playerPos">�v���C���[�|�W�V����</param>
void ArmEnemy::ChangeMove(VECTOR playerPos)
{
	VECTOR handpos = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);
	float handForPlayerDistance = calclation->LengthTwoPoint3D(handpos, playerPos);

	//�ҋ@
	if (nowMoveKind == MoveKind::MowingDown && moveChangeflg ||
		nowMoveKind == MoveKind::Swing && moveChangeflg ||
		nowMoveKind == MoveKind::HandUp && moveChangeflg
		)
	{
		//�v���C���[������Ă��鎞�̓����̃t���O��������
		if (nowMoveKind == MoveKind::Swing || nowMoveKind == MoveKind::HandUp)
		{
			playerRideMoveStartflg = false;
		}
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::Idle;
		move = new ArmEnemyIdle(modelHandle, prevRotate);
	}

	//�ガ����
	if (nowMoveKind == MoveKind::Idle && handForPlayerDistance < 2500 && playerRidePlace == RidePlace::None && playerPos.y < handpos.y)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::MowingDown;
		move = new ArmEnemyMowingDown(modelHandle,prevRotate);
	}

	//�U���...�v���C���[����r���O�r�ɏ���Ă���ꍇ
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && playerRideMoveStartflg && (playerRidePlace == RidePlace::Upperarm || playerRidePlace == RidePlace::Forearm))
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::Swing;
		move = new ArmEnemySwing(modelHandle, prevRotate);
	}

	//�r���グ��...�v���C���[����ɏ���Ă���ꍇ
	if (nowMoveKind != MoveKind::HandUp && nowMoveKind != MoveKind::Swing && playerRideMoveStartflg && playerRidePlace == RidePlace::Hand)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::HandUp;
		move = new ArmEnemyHandUp(modelHandle, prevRotate);
	}
}