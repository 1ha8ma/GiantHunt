#pragma once
#include<vector>

class EnemyParts;
class ArmEnemyMove;

class ArmEnemy
{
public:
	ArmEnemy();
	~ArmEnemy();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	VECTOR GetPosition() { return position; }
private:
	//�t���[���ԍ�
	enum class ArmEnemyFrameIndex :int
	{
		Upperarm = 16,	//��r
		Forearm,	//�O�r
		Hand,		//��
	};

	const int StartHP = 1000;		//�J�n��HP
	const float ModelScale = 40.0f;	//���f���̕`��T�C�Y

	ArmEnemyMove* armEnemyMove;

	//�X�e�[�^�X
	int HP;

	std::vector<EnemyParts*> parts;				//�p�[�c
	int modelHandle;							//���f���n���h��
	VECTOR position;							//�`��|�W�V����
	int playerRidePlace;	//�v���C���[������Ă���ꏊ
};