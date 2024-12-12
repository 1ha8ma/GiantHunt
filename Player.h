#pragma once

class PlayerStateProcessBase;

class Player
{
public:
	Player();
	~Player();

	//������
	void Initialize();
	//�X�V
	void Update(const Camera& camera);
	//�`��
	void Draw();

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//���
	enum State
	{
		Run,		//����
		Attack,		//�U��
		Jump,		//�W�����v
		Climb,		//�o��
		Hanging,	//�Ԃ牺����
	};

	const float AngleSpeed = 0.2f;  //�p�x�ύX���x
	const float Speed = 10.0f;      //�X�s�[�h

	//CollisionData collisiondata;//�����蔻����

	//�p�x�X�V
	void UpdateAngle();
	//�X�e�[�g�ύX
	void ChangeState();

	//���N���X
	PlayerStateProcessBase* nowstate;
	PlayerStateProcessBase* nextstate;

	//�X�e�[�^�X
	int HP;				//�̗�
	int gripPoint;		//���̓Q�[�W

	int modelHandle;				//���f���n���h��
	VECTOR position;				//�|�W�V����
	float angle;					//�p�x
	VECTOR moveVec;					//�ړ���
	VECTOR targetLookDirection;		//���f���̌����ڕW���� 
};