#pragma once
#include<vector>

class CollisionManager final
{
public:
	virtual ~CollisionManager();

	//������
	void Initialize();
	//�X�V
	void Update();

	//�C���X�^���X�쐻
	static void CreateInstance();

	//�C���X�^���X�Q�b�g
	static CollisionManager* GetInstance();

	//�C���X�^���X�폜
	static void DeleteInstance();

	//�����蔻����ǂݍ���
	static void RegisterCollisionData(CollisionData data);

private:
	CollisionManager();

	static CollisionManager* collisionmanager;//�C���X�^���X
	
	std::vector<CapsuleCollisionData*> capsuleCollisionData;//�J�v�Z���̓����蔻����s�����X�g

	//�J�v�Z���ǂ����̓����蔻��
	bool CapsuleWithCapsule(VECTOR capsuleStart1, VECTOR capsuleEnd1, float capsuleRadius1, VECTOR capsuleStart2, VECTOR capsuleEnd2, float capsuleRadius2);
};