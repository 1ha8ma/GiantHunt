#pragma once
#include"CollisionData.h"

class CollisionManager;

class EnemyParts
{
public:

	EnemyParts(ObjectTag tag, int modelHandle,int frameIndex,float capsuleLength,float capsuleRadius,VECTOR frameVec);
	~EnemyParts();

	void Initialize();
	void Update();
	void Draw();

	void OnHitObject(CollisionData hitObjectData);

	//Get.Set
	bool GetIsPlayerRid() { return isPlayerRide; }

private:
	void UpdateCollisionData();

	CollisionManager* collisionManager;
	CollisionData collisionData;

	int modelHandle;			//���f���n���h��
	int frameIndex;				//�t���[���ԍ�
	float capsuleLength;		//�J�v�Z���̒���
	ObjectTag tag;				//�ꏊ�̃^�O
	VECTOR initFramePosition;	//�ŏ��̃t���[���̃|�W�V����
	VECTOR framePosition;		//�t���[���̃|�W�V����
	VECTOR frameVec;			//�t���[���̃x�N�g��
	VECTOR capsuleStart;		//�J�v�Z���n�_
	VECTOR capsuleEnd;			//�J�v�Z���I�_
	float capsuleRadius;		//�J�v�Z�����a
	bool isPlayerRide;			//�v���C���[������Ă��邩
};