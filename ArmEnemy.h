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
	~ArmEnemy();

	//������
	void Initialize()override;
	//�X�V
	bool Update(VECTOR playerPos, Camera* camera)override;
	//�`��
	void Draw()override;

private:
	//����Ă���ꏊ
	enum class RidePlace :int
	{
		None,		//����Ă��Ȃ�
		Upperarm,	//��r
		Forearm,	//�O�r
		Hand,		//��
	};

	//�����̎��
	enum class MoveKind :int
	{
		Idle,		//�ҋ@
		MowingDown,	//�ガ����
		Swing,		//�U���
	};

	const int StartHP = 1000;		//�J�n��HP
	const float ModelScale = 40.0f;	//���f���̕`��T�C�Y

	void ChangeMove(VECTOR playerPos);

	ArmEnemyMoveBase* move;
	Calculation* calclation;

	std::vector<EnemyParts*> parts;			//�p�[�c
	RidePlace playerRidePlace;				//�v���C���[������Ă���ꏊ
	bool moveChangeflg;						//��Ԃ���̓����ύX�w���t���O
	MoveKind nowMoveKind;					//���݂̓����̎��
	int playerRideFlame;					//�v���C���[������Ă��鎞��
	bool playerRideflg;						//�v���C���[������Ă���t���O
	bool swingflg;							//�U��񂵃t���O
};