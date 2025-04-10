#include<fstream>
#include"DxLib.h"
#include"nlohmann/json.hpp"
#include"Loader.h"
#include"Calculation.h"
#include"Camera.h"
#include"WeakPoint.h"
#include"ArmEnemyMoveBase.h"
#include"ArmEnemyIdle.h"
#include"ArmEnemyDropRock.h"
#include"ArmEnemySwing.h"
#include"ArmEnemyFallDown.h"
#include"ArmEnemyHandUp.h"
#include"ArmEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemy::ArmEnemy()
{
	//�C���X�^���X��
	calclation = new Calculation();
	Loader* loader = loader->GetInstance();

	//���f�����[�h
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//�t�@�C���ǂݍ���
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/ArmEnemyData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//�ϐ�������
	//�X�e�[�^�X������
	MaxHP = jsonData["MaxHP"];
	HP = MaxHP;
	//�U���֌W
	PlayerRideMoveStartFlame = jsonData["PlayerRideMoveStartFlame"];
	AttackCoolTime = jsonData["AttackCoolTime"];
	DropRockStartPlayerHeight = jsonData["DropRockStartPlayerHeight"];
	//�|�W�V�����֌W
	position = VGet(jsonData["InitPositionX"], jsonData["InitPositionY"], jsonData["InitPositionZ"]);
	moveChangeflg = false;
	playerRideFlame = 0;
	isPlayerRide = false;
	playerRideMoveStartflg = false;
	attackCoolTimeFlame = 0;
	attackCoolTimeflg = false;

	//�`�惂�f��
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//�|���S����񏉊���
	InitializePolygonData();
	//�����蔻���񏉊���
	capsuleStart = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm);
	capsuleEnd = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle);
	capsuleRadius = CapsuleRadius;
	InitializeCollisionData();

	//���ʓ����蔻��
	weakPoint = new WeakPoint(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle - 1, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle - 1, WeakPointRadius);

	//����������
	move = new ArmEnemyIdle(modelHandle, VGet(0, 0, 0));
	nowMoveKind = MoveKind::Idle;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ArmEnemy::~ArmEnemy()
{
	DeleteCollisionData();
	delete weakPoint;
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
/// <param name="playerPos">�v���C���[�|�W�V����</param>
/// <param name="camera">�J����</param>
/// <returns>����ł��邩</returns>
bool ArmEnemy::Update(VECTOR playerPos, Camera* camera)
{
	//�t���[���Ɛe�t���[���̊�
	capsuleStart = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm);
	capsuleEnd = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle);
	VECTOR movePrevPos = VScale(VAdd(capsuleStart, capsuleEnd), 0.5f);

	//����ł��邩
	bool isDead = false;

	//�v���C���[������Ă�����
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && isPlayerRide)
	{
		playerRideFlame++;

		if (playerRideFlame > PlayerRideMoveStartFlame)
		{
			playerRideFlame = 0;
			playerRideMoveStartflg = true;
		}
	}

	//��_�X�V	
	weakPoint->Update();
	HP -= weakPoint->TakeDamage();

	//HP�m�F
	if (HP <= 0)
	{
		HP = 0;
		isDead = true;
	}

	//�U�����I����Ă���ꍇ�N�[���^�C����i�߂�
	if (attackCoolTimeflg && nowMoveKind != MoveKind::DropRock)
	{
		attackCoolTimeFlame++;

		if (attackCoolTimeFlame == AttackCoolTime)
		{
			attackCoolTimeflg = false;
		}
	}

	//����^�[�Q�b�g�J�����ɐݒ�
	targetCameraPosition = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);

	//�����X�V
	moveChangeflg = move->Update(camera, playerPos);
	if (moveChangeflg && nowMoveKind != MoveKind::Idle && nowMoveKind != MoveKind::FallDown)
	{
		attackCoolTimeflg = true;
		attackCoolTimeFlame = 0;
	}

	//�v���C���[�̋߂��̕��ʂ𔻒�
	CheckPlayerNearParts(playerPos);
	
	//�����̕ύX�m�F
	ChangeMove(playerPos);

	//�|�W�V�������f
	MV1SetPosition(modelHandle, position);
	
	//moveVec�擾
	UpdateMoveVec(movePrevPos);

	//���b�V�����X�V
	MV1SetupReferenceMesh(modelHandle, -1, TRUE);
	polygonList = MV1GetReferenceMesh(modelHandle, -1, TRUE);

	//�����蔻����X�V
	UpdateCollisionData();

	//�v���C���[�̏���Ă���֌W������
	isPlayerRide = false;

	return isDead;
}

/// <summary>
/// �Փˌ�̏���
/// </summary>
/// <param name="hitObjectData">�Փ˂����I�u�W�F�N�g�̏��</param>
void ArmEnemy::OnHitObject(CollisionData* hitObjectData)
{
	//�v���C���[������Ă��鎞�̏���
	if (hitObjectData->tag == ObjectTag::PlayerWholeBody ||
		hitObjectData->tag == ObjectTag::PlayerFoot)
	{
		isPlayerRide = true;
	}

	//�v���C���[�̍U���������ꍇ
	if (hitObjectData->tag == ObjectTag::Attack_P)
	{
		HP -= hitObjectData->attackPower;
	}
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
	weakPoint->Update();

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
	weakPoint->Draw();

	//�����蔻��m�F�p
	//DrawPolygon();
	DrawCapsule();
	//move->Draw();
}

/// <summary>
/// �v���C���[���r�̂ǂ̕��ʂɋ߂�������
/// </summary>
/// <param name="playerPos">�v���C���[�|�W�V����</param>
void ArmEnemy::CheckPlayerNearParts(VECTOR playerPos)
{
	float nearDistance = -1;		//��ԋ߂�����
	std::vector<VECTOR> partsPos;	//���ʃ|�W�V����

	//�|�W�V�����ݒ�
	partsPos.push_back(VScale(VAdd(MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm), MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm)), 0.5f));	//��r
	partsPos.push_back(VScale(VAdd(MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm), MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm)), 0.5f));		//�O�r
	partsPos.push_back(VScale(VAdd(MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand), MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle)), 0.5f));	//��

	//��������
	for (int i = 0; i < 3; i++)
	{
		float distance = calclation->LengthTwoPoint3D(playerPos, partsPos[i]);
		if (nearDistance > distance || nearDistance == -1)
		{
			nearDistance = distance;
			playerRidePlace = i;
		}
	}

	partsPos.clear();
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
	if (nowMoveKind == MoveKind::DropRock && moveChangeflg ||
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

	//�◎�Ƃ�
	if (nowMoveKind == MoveKind::Idle && !isPlayerRide && playerPos.y < handpos.y && playerPos.y>DropRockStartPlayerHeight && !attackCoolTimeflg)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::DropRock;
		move = new ArmEnemyDropRock(modelHandle, prevRotate);
	}

	//�U���...�v���C���[����r���O�r�ɏ���Ă���ꍇ
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && playerRideMoveStartflg && (playerRidePlace == (int)PartsName::Upperarm || playerRidePlace == (int)PartsName::Forearm))
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::Swing;
		move = new ArmEnemySwing(modelHandle, prevRotate);
	}

	//�r���グ��...�v���C���[����ɏ���Ă���ꍇ
	if (nowMoveKind != MoveKind::HandUp && nowMoveKind != MoveKind::Swing && playerRideMoveStartflg && playerRidePlace == (int)PartsName::Hand || playerRidePlace == (int)PartsName::WeakPoint)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::HandUp;
		move = new ArmEnemyHandUp(modelHandle, prevRotate);
	}
}

/// <summary>
/// moveVec�X�V
/// </summary>
/// <param name="movePrevPos">�����O�̃|�W�V����</param>
void ArmEnemy::UpdateMoveVec(VECTOR movePrevPos)
{
	capsuleStart = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm);
	capsuleEnd = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::LeftHandMiddle);
	VECTOR moveAfterPos = VAdd(capsuleStart, capsuleEnd);
	moveAfterPos = VScale(moveAfterPos, 0.5f);

	moveVec = VSub(moveAfterPos, movePrevPos);
}