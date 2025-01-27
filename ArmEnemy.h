#pragma once
#include<vector>
#include"EnemyBase.h"

class EnemyParts;
class ArmEnemyMoveBase;
class Calculation;

class ArmEnemy:public EnemyBase
{
public:
	ArmEnemy();
	~ArmEnemy()override;

	//������
	void Initialize()override;
	//�X�V
	bool Update(VECTOR playerPos, Camera* camera)override;

	//�|���ꂽ��̏�����
	void InitializeFallDown()override;
	//�|���ꂽ��̍X�V
	bool UpdateFallDown(Camera* camera)override;

	//�`��
	void Draw()override;

private:
	//����Ă���ꏊ
	enum class PartsName :int
	{
		Upperarm,	//��r
		Forearm,	//�O�r
		Hand,		//��
		WeakPoint,	//��_
	};

	//�����̎��
	enum class MoveKind :int
	{
		Idle,		//�ҋ@
		MowingDown,	//�ガ����
		Swing,		//�U���
		FallDown,	//�|���
		HandUp,		//����グ��
	};

	const int MaxHP = 1000;							//�ő�HP
	const float ModelScale = 40.0f;					//���f���̕`��T�C�Y
	const int PlayerRideMoveStateFlame = 100;		//�v���C���[������Ă��鎞�̓������n�߂�t���[��

	void ChangeMove(VECTOR playerPos);

	ArmEnemyMoveBase* move;
	Calculation* calclation;

	std::vector<EnemyParts*> parts;			//�p�[�c
	int playerRidePlace;				//�v���C���[������Ă���ꏊ
	bool moveChangeflg;						//��Ԃ���̓����ύX�w���t���O
	MoveKind nowMoveKind;					//���݂̓����̎��
	int playerRideFlame;					//�v���C���[������Ă��鎞��
	bool playerRideflg;						//�v���C���[������Ă���t���O
	bool playerRideMoveStartflg;			//�v���C���[������Ă��鎞�̓����̊J�n�t���O
};