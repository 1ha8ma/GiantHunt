#pragma once
#include"CollisionData.h"

class CollisionManager;
class Effect;

class EnemyParts
{
public:
	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex,int formerFrameIndex,float capsuleRadius);
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
	void UpdateCollisionData();

	Effect* effect;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;			//���f���n���h��
	int frameIndex;				//�t���[���ԍ�
	int formerFrameIndex;		//�J�v�Z���̌��ɂȂ�t���[��
	ObjectTag tag;				//�ꏊ�̃^�O
	VECTOR capsuleStart;		//�J�v�Z���n�_
	VECTOR capsuleEnd;			//�J�v�Z���I�_
	float capsuleRadius;		//�J�v�Z�����a
	bool isPlayerRide;			//�v���C���[������Ă��邩
	int damage;					//�^����_���[�W
};