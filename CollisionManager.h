#pragma once
#include"CollisionData.h"
#include<vector>

class CollisionManager final
{
public:
	virtual ~CollisionManager();

	//������
	void Initialize();
	//�X�V
	void Update();

	//�C���X�^���X�Q�b�g
	static CollisionManager* GetInstance();

	//�C���X�^���X�폜
	static void DeleteInstance();

	//�����蔻����ǉ�
	static void AddCollisionData(CollisionData* data);

	static void RemoveCollisionData(CollisionData* data);

private:
	CollisionManager();

	static CollisionManager* collisionManager;				//�C���X�^���X

	static std::vector<CollisionData*> collisionDataList;	//�����蔻���񃊃X�g

	//�J�v�Z���ǂ����̓����蔻��
	bool CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2);
};