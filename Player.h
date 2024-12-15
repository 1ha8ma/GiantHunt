#pragma once

class PlayerStateProcessBase;
class Input;

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
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		ThrustAttack,	//�˂��h���U��
		Climb,			//�o��
		Hanging,		//�Ԃ牺����
		Roll,			//�]����
	};

	const float AngleSpeed = 0.2f;  //�p�x�ύX���x
	const float Speed = 10.0f;      //�X�s�[�h

	//�p�x�X�V
	void UpdateAngle();
	//�X�e�[�g�ύX
	void ChangeState();
	//�������Ă��邩�m�F
	void CheckOnGround();

	//���N���X
	PlayerStateProcessBase* nowstate;
	Input* input;

	//�X�e�[�^�X
	int HP;				//�̗�
	int gripPoint;		//���̓Q�[�W

	//����
	int inputstate;					//���͏��
	DINPUT_JOYSTATE stickstate;		//�X�e�B�b�N���͏��

	int modelHandle;				//���f���n���h��
	VECTOR position;				//�|�W�V����
	float angle;					//�p�x
	VECTOR moveVec;					//�ړ���
	VECTOR targetLookDirection;		//���f���̌����ڕW���� 
	int nowstateKind;				//���݂̏��
	bool onGround;					//�������Ă��邩

	bool changeStateflg;			//��Ԃ���̏�ԕύX�w��������ꍇ
};