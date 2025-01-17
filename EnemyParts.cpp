#include"DxLib.h"
#include"CollisionManager.h"
#include"Effect.h"
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
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int formerFrameIndex, int frameIndex,float capsuleRadius)
{
	//�n���h���R�s�[
	this->modelHandle = modelHandle;
	//�^�O�ݒ�
	this->tag = tag;

	//�t���[���ԍ��擾
	this->frameIndex = frameIndex;
	this->formerFrameIndex = formerFrameIndex;

	//�J�v�Z���ݒ�
	this->capsuleRadius = capsuleRadius;
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex);
	capsuleEnd = MV1GetFramePosition(modelHandle, formerFrameIndex);
	
	//private�ϐ�������
	isPlayerRide = false;

	//�����蔻����ǉ�
	collisionManager = collisionManager->GetInstance();
	collisionData.HitProcess = std::bind(&EnemyParts::OnHitObject, this, std::placeholders::_1);
	UpdateCollisionData();
	collisionManager->AddCollisionData(&collisionData);

	//��_�Ȃ�G�t�F�N�g��t����
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect = new Effect();

		effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(10, 10, 10), VGet(0, 0, 0), 1.0f);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyParts::~EnemyParts()
{
	collisionManager->RemoveCollisionData(&collisionData);
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
	//�J�v�Z���ݒ�
	//�t���[���Ɛe�t���[���̊�
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex);
	capsuleEnd = MV1GetFramePosition(modelHandle, formerFrameIndex);

	//�����蔻����X�V
	UpdateCollisionData();

	//��_�Ȃ�G�t�F�N�g��t����
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		bool playing = effect->IsPlayEffect(Effect::EffectKind::WeakPoint);

		if (!playing)
		{
			effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(50, 50, 50), VGet(0, 0, 0), 1.0f);
		}

		effect->Update(capsuleStart, VGet(0, 0, 0));
	}

	damage = 0;
	isPlayerRide = false;
}

/// <summary>
/// �`��
/// </summary>
void EnemyParts::Draw()
{
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//�|�W�V�����̓_

	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->Draw();
	}
}

/// <summary>
/// �Փˌ�̏���
/// </summary>
/// <param name="hitObjectData">�Փ˂����I�u�W�F�N�g</param>
void EnemyParts::OnHitObject(CollisionData hitObjectData)
{
	//�v���C���[������Ă��鎞�̏���
	if (hitObjectData.tag == ObjectTag::PlayerWholeBody)
	{
		isPlayerRide = true;
	}

	//�v���C���[�̍U���������ꍇ
	if (hitObjectData.tag == ObjectTag::Attack_P)
	{
		damage = hitObjectData.attackPower;
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