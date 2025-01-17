#pragma once
#include"ArmEnemyMoveBase.h"

class CollisionManager;
struct CollisionData;

class ArmEnemyMowingDown :public ArmEnemyMoveBase
{
public:
	ArmEnemyMowingDown(int modelHandle,float modelScale,VECTOR prevRotate);
	~ArmEnemyMowingDown()override;

	bool Update(Camera* camera)override;
	void Draw()override;

	void OnHitObject(CollisionData objectData);
private:
	const float AttackCapsuleRadius = 200.0f;
	const int AttackPower = 20;

	//�����蔻����X�V
	void UpdateCollisionData();

	CollisionManager* collisionManager;		
	CollisionData collisionData;			//�����蔻����
	VECTOR attackCapsuleStart;				//�U���J�v�Z���n�_
	VECTOR attackCapsuleEnd;				//�U���J�v�Z���I�_
	bool moveEnd;							//�����I��
	bool onAttackCollision;					//�U�������蔻���t���邩
	bool attackHit;							//�U������������
};