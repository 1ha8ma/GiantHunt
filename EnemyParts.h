#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;
class SoundEffect;

class EnemyParts
{
public:
	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex1,int frameIndex2,float capsuleRadius);
	~EnemyParts();

	void Initialize();
	void Update();
	void Draw();

	void OnHitObject(CollisionData hitObjectData);

	//�_���[�W��n��
	int TakeDamage() { return damage; }

	//Get.Set
	bool GetIsPlayerRide() { return isPlayerRide; }

private:
	const int PlayHitWeakPointEffectFlame = 300;

	//�����蔻����X�V
	void UpdateCollisionData();

	Effect* effect;
	SoundEffect* se;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;					//���f���n���h��
	int frameIndex1;						//�t���[���ԍ�
	int frameIndex2;				//�J�v�Z���̌��ɂȂ�t���[��
	ObjectTag tag;						//�ꏊ�̃^�O
	VECTOR capsuleStart;				//�J�v�Z���n�_
	VECTOR capsuleEnd;					//�J�v�Z���I�_
	float capsuleRadius;				//�J�v�Z�����a
	bool isPlayerRide;					//�v���C���[������Ă��邩
	int damage;							//�^����_���[�W

	//��_�̏ꍇ
	bool hitWeakPointEffectflg;			//��_�q�b�g�G�t�F�N�g�t���O
	int hitWeakPointEffectflame;		//��_�q�b�g�G�t�F�N�g�t���[��
};