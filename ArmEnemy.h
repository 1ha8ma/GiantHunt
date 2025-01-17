#pragma once
#include<vector>

class EnemyParts;
class ArmEnemyMoveBase;
class Calculation;

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//������
	void Initialize();
	//�X�V
	void Update(VECTOR playerPos,Camera* camera);
	//�`��
	void Draw();

	VECTOR GetPosition() { return position; }
	VECTOR GetTargetCameraPosition() { return targetCameraPosition; }
	int GetHP() { return HP; }
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

	//�X�e�[�^�X
	int HP;

	std::vector<EnemyParts*> parts;			//�p�[�c
	int modelHandle;						//���f���n���h��
	VECTOR position;						//�`��|�W�V����
	RidePlace playerRidePlace;				//�v���C���[������Ă���ꏊ
	VECTOR targetCameraPosition;			//�^�[�Q�b�g�J�����p�|�W�V����
	bool moveChangeflg;						//��Ԃ���̓����ύX�w���t���O
	MoveKind nowMoveKind;					//���݂̓����̎��
	int playerRideFlame;					//�v���C���[������Ă��鎞��
	bool playerRideflg;//�v���C���[������Ă���t���O
	bool swingflg;							//�U��񂵃t���O
};