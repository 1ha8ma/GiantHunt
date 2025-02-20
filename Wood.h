#pragma once
#include<vector>

class CollisionManager;
struct CollisionData;

class Wood
{
public:
	Wood();
	~Wood();

	//�`��
	void Draw();

private:
	const float CapsuleRadius = 400.0f;								//�J�v�Z�����a
	const VECTOR drawPosition = VGet(4500.0f, 1000.0f, 4300.0f);	//�`��|�W�V����

	//�����蔻��J�v�Z���|�W�V����
	const VECTOR cap1Start = VGet(4700.0f, 1200.0f, 4350.0f);//4600,1300,4500
	const VECTOR cap1End = VGet(5750.0f, -300.0f, 4500.0f);//5650,-300,4500
	const VECTOR cap1pos = VScale(VAdd(cap1Start, cap1End), 0.5f);
	const VECTOR cap2Start = VGet(3200.0f, 1750.0f, 4300.0f);//3200,1750,4300
	const VECTOR cap2End = VGet(4500.0f, 1250.0f, 4300.0f);//4500,1250,4300
	const VECTOR cap2pos = VScale(VAdd(cap2Start, cap2End), 0.5f);

	//�����������̏���
	void OnHitObject();
	//�����蔻����Z�b�g
	void RegisterCollisionData();

	void PolyInit();

	//���N���X
	CollisionManager* collisionManager;
	CollisionData capsule1CollisionData;
	CollisionData capsule2CollisionData;

	int modelHandle;		//���f���n���h��

	bool objectHit;
	std::vector<VERTEX3D> vertex;
	MV1_REF_POLYGONLIST polygonList;
};