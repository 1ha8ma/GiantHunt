#pragma once
#include"ArmEnemyMoveBase.h"

class CollisionManager;
struct CollisionData;
class SoundEffect;
class ArmEnemyAttackRock;

class ArmEnemyDropRock :public ArmEnemyMoveBase
{
public:
	ArmEnemyDropRock(int modelHandle,VECTOR prevRotate);
	~ArmEnemyDropRock()override;

	bool Update(Camera* camera, VECTOR playerPosition)override;
	void Draw()override;

	void OnHitObject(CollisionData* objectData);
private:
	const float AttackCapsuleRadius = 800.0f; //�w����w�̓����蔻��ɂ���Ȃ�200
	const int AttackPower = 20;

	//�����蔻����X�V
	void UpdateCollisionData();

	CollisionManager* collisionManager;		
	CollisionData collisionData;			//�U�������蔻����
	SoundEffect* se;
	ArmEnemyAttackRock* rock;				//��

	VECTOR attackCapsuleStart;				//�U���J�v�Z���n�_
	VECTOR attackCapsuleEnd;				//�U���J�v�Z���I�_
	bool moveEnd;							//�����I��
	bool onAttackCollision;					//�U�������蔻���t���邩
	bool attackHit;							//�U������������
};