#pragma once
#include"ArmEnemyMoveBase.h"

class CollisionManager;
struct CollisionData;
class SoundEffect;

class ArmEnemyMowingDown :public ArmEnemyMoveBase
{
public:
	ArmEnemyMowingDown(int modelHandle,float modelScale,VECTOR prevRotate);
	~ArmEnemyMowingDown()override;

	bool Update(Camera* camera)override;
	void Draw()override;

	void OnHitObject(CollisionData objectData);
private:
	const float AttackCapsuleRadius = 800.0f; //指から指の当たり判定にするなら200
	const int AttackPower = 20;

	//当たり判定情報更新
	void UpdateCollisionData();

	CollisionManager* collisionManager;		
	CollisionData collisionData;			//攻撃当たり判定情報
	SoundEffect* se;

	VECTOR attackCapsuleStart;				//攻撃カプセル始点
	VECTOR attackCapsuleEnd;				//攻撃カプセル終点
	bool moveEnd;							//動き終了
	bool onAttackCollision;					//攻撃当たり判定を付けるか
	bool attackHit;							//攻撃が当たった
};