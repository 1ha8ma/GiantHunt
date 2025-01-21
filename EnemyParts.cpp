#include"DxLib.h"
#include"CollisionManager.h"
#include"SoundEffect.h"
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
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int frameIndex1, int frameIndex2,float capsuleRadius)
{
	//�n���h���R�s�[
	this->modelHandle = modelHandle;
	//�^�O�ݒ�
	this->tag = tag;

	//�t���[���ԍ��擾
	this->frameIndex1 = frameIndex1;
	this->frameIndex2 = frameIndex2;

	//�J�v�Z���ݒ�
	this->capsuleRadius = capsuleRadius;
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex1);
	capsuleEnd = MV1GetFramePosition(modelHandle, frameIndex2);
	
	//�C���X�^���X��
	se = new SoundEffect();

	//private�ϐ�������
	isPlayerRide = false;
	hitWeakPointEffectflg = false;
	hitWeakPointEffectflame = 0;

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
	MV1ResetFrameUserLocalMatrix(modelHandle, frameIndex1);
	MV1ResetFrameUserLocalMatrix(modelHandle, frameIndex2);
	collisionManager->RemoveCollisionData(&collisionData);
	delete se;
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->RemoveEffect(Effect::EffectKind::WeakPoint);
		delete effect;
	}
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
	capsuleStart = MV1GetFramePosition(modelHandle, frameIndex1);
	capsuleEnd = MV1GetFramePosition(modelHandle, frameIndex2);

	//�����蔻����X�V
	UpdateCollisionData();

	//��_�Ȃ�G�t�F�N�g��t����
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		bool playing = effect->IsPlayEffect(Effect::EffectKind::WeakPoint);

		//�I�����Ă�����܂��Đ�
		if (!playing)
		{
			effect->PlayEffect(Effect::EffectKind::WeakPoint, capsuleStart, VGet(50, 50, 50), VGet(0, 0, 0), 1.0f);
		}

		effect->Update(Effect::EffectKind::WeakPoint, capsuleStart, VGet(0, 0, 0));
	}

	//��_�q�b�g�̃G�t�F�N�g�X�V
	if (hitWeakPointEffectflg)
	{
		effect->Update(Effect::EffectKind::HitWeakPoint, capsuleStart, VGet(0, 0, 0));

		if (hitWeakPointEffectflame == PlayHitWeakPointEffectFlame)
		{
			effect->RemoveEffect(Effect::EffectKind::HitWeakPoint);
			hitWeakPointEffectflg = false;
		}

		//�t���[�����Z
		hitWeakPointEffectflame++;
	}

	damage = 0;
	isPlayerRide = false;
}

/// <summary>
/// �`��
/// </summary>
void EnemyParts::Draw()
{
	if (tag == ObjectTag::WeakPoint_E1 || tag == ObjectTag::WeakPoint_E2)
	{
		effect->Draw();
	}

	//�m�F�p
	//DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//�|�W�V�����̓_
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
		//��_�̏ꍇ
		if (tag == ObjectTag::WeakPoint_E1)
		{
			effect->PlayEffect(Effect::EffectKind::HitWeakPoint, capsuleStart, VGet(120.0f, 120.0f, 120.0f), VGet(0, 0, 0), 1.0f);
			se->PlaySE(SoundEffect::SEKind::HitWeakPoint);
			damage = hitObjectData.attackPower * 2;
			if (!hitWeakPointEffectflg)
			{
				hitWeakPointEffectflame = 0;
				hitWeakPointEffectflg = true;
			}
		}
		//���̑�
		else
		{
			damage = hitObjectData.attackPower;
		}
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