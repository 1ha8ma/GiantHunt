#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;
class SoundEffect;

class WeakPoint
{
public:
	WeakPoint(int modelHandle, int frameIndex1, int frameIndex2, float capsuleRadius);
	~WeakPoint();

	void Initialize();
	void Update();
	void Draw();

	//�I�u�W�F�N�g�ɏՓ˂������̏���
	void OnHitObject(CollisionData* hitObjectData);
	//�_���[�W��n��
	int TakeDamage() { return damage; }

private:
	const int PlayHitWeakPointEffectFlame = 300;	//��_�q�b�g�G�t�F�N�g�̍Đ�����
	const int WeakPointDamageMultiplier = 2;		//��_�̃_���[�W�{��

	//�����蔻����X�V
	void UpdateCollisionData();

	Effect* effect;
	SoundEffect* se;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;					//���f���n���h��
	int frameIndex1;					//�t���[���ԍ�1
	int frameIndex2;					//�t���[���ԍ�2   1��2�̍��W����J�v�Z�������
	ObjectTag tag;						//�^�O
	VECTOR capsuleStart;				//�J�v�Z���n�_
	VECTOR capsuleEnd;					//�J�v�Z���I�_
	float capsuleRadius;				//�J�v�Z�����a
	int damage;							//�^����_���[�W
	
	//��_�̏ꍇ
	bool hitWeakPointEffectflg;			//��_�q�b�g�G�t�F�N�g�t���O
	int hitWeakPointEffectflame;		//��_�q�b�g�G�t�F�N�g�t���[��
};