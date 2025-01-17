#pragma once
#include"PlayerStateProcessBase.h"

class CollisionManager;
struct CollisionData;

/// <summary>
/// �˂��h���U��
/// </summary>
class PlayerPiercing :public PlayerStateProcessBase
{
public:
	PlayerPiercing(int modelHandle, VECTOR prevtargetLookDirection);
	~PlayerPiercing();

	void Initialize()override {};
	bool Update(VECTOR position,float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision) override;
	void Draw()override;

private:
	const int LowestAttackPower = 30;		//�Œ�U����
	const float AttackCapsuleRadius = 20;	//�U���J�v�Z�����a
	const float MaxSwingUp = 1.3f;			//�ő�U��グ�n�_
	const float SwingUpSpeed = 0.01f;		//�U��グ���x
	const float SwingDownSpeed = 0.5f;		//�U�艺�낵���x

	//�����蔻����X�V
	void UpdateCollisionData();
	//�˂��h���U��
	void PiercingAttack(int inputstate);
	//�Փˌ㏈��
	void OnHitObject(CollisionData objectData);

	CollisionManager* collisionManager;
	CollisionData attackCollisionData;	//�U�������蔻����

	bool canInputX;					//X�{�^���A�����͖h�~�t���O
	bool changeState;				//�X�e�[�g�ύX
	VECTOR attackCapsuleStart;		//�U���J�v�Z���n�_
	VECTOR attackCapsuleEnd;		//�U���J�v�Z���I�_
	int attackPower;				//�U����
	int attackChargeFlame;			//�U�����ߎ���
	bool attack;					//�U����
	bool attackEnd;					//�U���I��
	bool attackHit;

	VECTOR rotate;
};