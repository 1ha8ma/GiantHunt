#pragma once
#include"PlayerStateProcessBase.h"

class Input;
class CollisonManager;
struct CollisionData;

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

	//�|�W�V�������f
	void ReflectPosition();
	//�Փ˂������̏���
	void OnHitObject(CollisionData hitObjectData);

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }

private:
	//���
	enum class State :int
	{
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		ThrustAttack,	//�˂��h���U��
		Climb,			//�o��
		Hanging,		//�Ԃ牺����
		Roll,			//�]����
	};

	const float AngleSpeed = 0.2f;			//�p�x�ύX���x
	const float CapsuleRadius = 50.0f;		//�J�v�Z�����a
	const int AttackPower = 100;			//�U����
	const float Gravity = 0.5f;				//�d��

	//�p�x�X�V
	void UpdateAngle();
	//�X�e�[�g�ύX
	void ChangeState();
	//�������Ă��邩�m�F
	void CheckOnGround();
	//�J�v�Z���X�V
	void UpdateCapsule();
	//�����蔻����X�V
	void UpdateCollisionData();
	//�`��ʒu�C��
	void CorrectionDrawPosition();
	//�����߂�
	void CollisionPushBack(CollisionData hitCollisionData);
	
	//���N���X
	PlayerStateProcessBase* nowstate;
	Input* input;
	CollisionManager* collisionManager;
	CollisionData collisionData;

	//�X�e�[�^�X
	int HP;				//�̗�
	int gripPoint;		//���̓Q�[�W

	//����
	int inputstate;									//���͏��
	DINPUT_JOYSTATE stickstate;						//�X�e�B�b�N���͏��

	int modelHandle;								//���f���n���h��
	VECTOR position;								//�|�W�V����
	VECTOR drawPosition;							//�`��p�|�W�V����
	VECTOR capStart;								//�J�v�Z���n�_(��)
	VECTOR capEnd;									//�J�v�Z���I�_(��)
	float angle;									//�`��p�x
	VECTOR moveVec;									//�ړ���
	VECTOR targetLookDirection;						//���f���̌����ڕW���� 
	State nowstateKind;								//���݂̏��
	bool onGround;									//�������Ă��邩
	bool isCatch;									//�͂߂��Ԃ�
	bool isStand;									//���Ă��Ԃ�
	PlayerStateProcessBase::RunPlaceKind runPlace;	//�����Ă���ꏊ

	float fallSpeed;								//�������x
	bool changeStateflg;							//��Ԃ���̏�ԕύX�w��������ꍇ

	//�������Ă���I�u�W�F�N�g�̃f�[�^
	VECTOR hitObjectCapStart;
	VECTOR hitObjectCapEnd;
};