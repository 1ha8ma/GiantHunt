#pragma once
#include"PlayerStateProcessBase.h"
#include"CollisionData.h"
#include"CollisionManager.h"

class Input;
//class CollisonManager;
class Camera;

class Player
{
public:
	Player();
	~Player();

	//�X�^�[�g�V�[��������
	void InitializeStartScene();
	//�X�^�[�g�V�[���I������
	void StartSceneEnd() { delete nowstate; }

	//�Q�[��������
	void InitializeGame();
	//�Q�[���X�V
	bool UpdateGame(const Camera& camera);

	//�Q�[���I�[�o�[�V�[��������
	void InitializeGameOver();
	//�Q�[���I�[�o�[�V�[���X�V
	void UpdateGameOver();
	//�`��
	void Draw();

	//�Փ˂������̏���
	void BodyOnHitObject(CollisionData* hitObjectData);
	void FootOnHitObject(CollisionData* hitObjectData);
	//�ǏՓˎ��̏���
	void WallHitProcess(VECTOR sinkIntoDepth);

	//GetSet
	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }
	int GetHP() { return HP; }
	int GetGripPoint() { return gripPoint; }

private:
	//���
	enum class State :int
	{
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		Climb,			//�o��
		Squat,			//���Ⴊ��
		Piercing,		//�˂��h���U��
		Roll,			//�]����
		FallDown,		//�|���
	};

	const float AngleSpeed = 0.2f;					//�p�x�ύX���x
	const float WholeBodyCapsuleRadius = 50.0f;		//�S�g�J�v�Z�����a
	const float FootCapsuleRadius = 20.0f;			//���J�v�Z�����a
	const float Gravity = 0.5f;						//�d��
	const int MaxHP = 100;							//�ő�HP
	const int MaxGripPoint = 400;					//�ő刬��
	const int MinusGripPoint = 1;					//���炷���͗�

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
	void CollisionPushBack(CollisionData partsData,CollisionData hitCollisionData);
	//�A�����͖h�~
	void PreventionContinuousInput();
	
	//���N���X
	PlayerStateProcessBase* nowstate;
	Input* input;
	CollisionManager* collisionManager;
	CollisionData bodyCollisionData;
	CollisionData footCollisionData;
	CollisionData hitObjectData;
	CollisionData* hitObjectDataPointer;

	//�X�e�[�^�X
	int HP;				//�̗�
	int gripPoint;		//���̓Q�[�W

	//����
	int inputstate;									//���͏��
	DINPUT_JOYSTATE stickstate;						//�X�e�B�b�N���͏��

	int modelHandle;								//���f���n���h��
	VECTOR drawPosition;							//�`��p�|�W�V����
	//�����蔻��
	VECTOR position;								//�|�W�V����
	VECTOR wholebodyCapStart;						//�J�v�Z���n�_(��)
	VECTOR wholebodyCapEnd;							//�J�v�Z���I�_(��)
	VECTOR footCapStart;							//���J�v�Z��
	VECTOR footCapEnd;								//���J�v�Z��
	//���̑�
	float angle;									//�v���C���[�̌���
	VECTOR moveVec;									//�ړ���
	VECTOR targetLookDirection;						//���f���̌����ڕW���� 
	State nowstateKind;								//���݂̏��
	bool onGround;									//�������Ă��邩
	bool onFootObject;								//�����I�u�W�F�N�g�ɒ����Ă���
	bool isCatch;									//�͂߂��Ԃ�
	bool isStand;									//���Ă��Ԃ�
	PlayerStateProcessBase::RunPlaceKind runPlace;	//�����Ă���ꏊ
	bool gameOverflg;								//�Q�[���I�[�o�[�t���O
	bool canInputX;									//�U���A�����͖h�~

	float fallSpeed;								//�������x
	int fallFrame;									//��������
	bool changeStateflg;							//��Ԃ���̏�ԕύX�w��������ꍇ

	//�������Ă���I�u�W�F�N�g�̃f�[�^
	VECTOR hitObjectCapStart;
	VECTOR hitObjectCapEnd;
};