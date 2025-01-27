#pragma once
#include"PlayerStateProcessBase.h"

struct CollisionData;
class CollisionManager;
class SoundEffect;

class PlayerNormalAttack :public PlayerStateProcessBase
{
public:
	PlayerNormalAttack(int modelHandle, VECTOR prevtargetLookDirection);
	~PlayerNormalAttack()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(VECTOR position,float angle, int inputstate, DINPUT_JOYSTATE stickstate, const Camera& camera, CollisionData objectCollision)override;

	void Draw()override;

private:
	const int AttackPower = 15;				//�U����
	const float AttackCapsuleRadius = 20;	//�U�������蔻�蔼�a

	//�����蔻��X�V
	void UpdateCollisionData();

	//�Փˌ㏈��
	void OnHitObject(CollisionData* objectData);

	//���N���X
	CollisionManager* collisionManager;
	CollisionData attackCollisionData;
	SoundEffect* se;

	bool stateChangeflg;			//�X�e�[�g�ύX�t���O
	bool animEndflg;				//�A�j���[�V�����I��
	bool attack;					//�U����
	bool attackHit;					//�U������������
	VECTOR attackCapsuleStart;		//�U���J�v�Z���n�_
	VECTOR attackCapsuleEnd;		//�U���J�v�Z���I�_
};