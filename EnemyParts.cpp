#include"DxLib.h"
#include"CollisionManager.h"
#include"EnemyParts.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="tag">�I�u�W�F�N�g�^�O</param>
/// <param name="modelHandle">���f���n���h��</param>
/// <param name="frameIndex">�t���[���ԍ�</param>
/// <param name="capsuleLength">�J�v�Z���̒���</param>
/// <param name="capsuleRadius">�J�v�Z�����a</param>
/// <param name="frameVec">�t���[���̍��W����̌���</param>
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int frameIndex, float capsuleLength, float capsuleRadius,VECTOR frameVec)
{
	this->modelHandle = modelHandle;
	//�^�O�ݒ�
	this->tag = tag;
	//�{�[���̃|�W�V�����擾
	this->frameIndex = frameIndex;
	framePosition = MV1GetFramePosition(modelHandle, frameIndex);
	initFramePosition = framePosition;

	//�t���[���̌������R�s�[
	this->frameVec = frameVec;
	
	//�J�v�Z���ݒ�
	this->capsuleRadius = capsuleRadius;
	this->capsuleLength = capsuleLength;
	capsuleStart = VScale(frameVec, capsuleLength);
	capsuleStart = VAdd(capsuleStart, framePosition);
	capsuleEnd = VScale(frameVec, -capsuleLength);
	capsuleEnd = VAdd(capsuleEnd, framePosition);
	
	collisionManager = collisionManager->GetInstance();

	//private�ϐ�������
	isPlayerRide = false;

	//�����蔻����ǉ�
	collisionData.HitProcess = std::bind(&EnemyParts::OnHitObject, this, std::placeholders::_1);
	UpdateCollisionData();
	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyParts::~EnemyParts()
{

}

/// <summary>
/// ������
/// </summary>
void EnemyParts::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void EnemyParts::Update()
{
	//�{�[���̃x�N�g���擾
	framePosition = MV1GetFramePosition(modelHandle, frameIndex);

	//�J�v�Z���ݒ�
	capsuleStart = VScale(frameVec, capsuleLength);
	capsuleStart = VAdd(capsuleStart, framePosition);
	capsuleEnd = VScale(frameVec, -capsuleLength);
	capsuleEnd = VAdd(capsuleEnd, framePosition);

	//�����蔻����X�V
	UpdateCollisionData();

	isPlayerRide = false;
}

/// <summary>
/// �`��(�����蔻��m�F�p)
/// </summary>
void EnemyParts::Draw()
{
	DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//�|�W�V�����̓_
}

/// <summary>
/// �Փˌ�̏���
/// </summary>
/// <param name="hitObjectData">�Փ˂����I�u�W�F�N�g</param>
void EnemyParts::OnHitObject(CollisionData hitObjectData)
{
	//�v���C���[������Ă��鎞�̏���
	if (hitObjectData.tag == ObjectTag::Player)
	{
		isPlayerRide = true;
	}
}

/// <summary>
/// �����蔻��X�V
/// </summary>
void EnemyParts::UpdateCollisionData()
{
	collisionData.tag = tag;
	collisionData.startPosition = capsuleStart;
	collisionData.endPosition = capsuleEnd;
	collisionData.radius = capsuleRadius;
	collisionData.attackPower = 0;
	collisionData.isCollisionActive = true;
}