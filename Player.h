#pragma once

class Input;

class Player
{
public:
	Player();
	~Player();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();

	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//���
	enum State
	{
		Run,		//����
		Attack,		//�U��
		Climb,		//�o��
		Hanging,	//�Ԃ牺����
	};

	//�p�[�c�̎��
	enum PartsKind
	{
		LeftArm,
		RightArm,
		LeftLeg,
		RightLeg,
		Body,
		Head,
	};

	const float AngleSpeed = 0.02f;  //�p�x�ύX���x
	const float Speed = 10.0f;      //�X�s�[�h

	//CollisionData collisiondata;//�����蔻����
	Input* input;

	void Move();
	void UpdateAngle();

	int modelHandle;				//���f���n���h��
	VECTOR position;				//�|�W�V����
	float angle;					//�p�x
	VECTOR moveVec;					//�ړ���
	VECTOR targetLookDirection;		//���f���̌����ڕW����
};