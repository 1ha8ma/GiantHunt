#pragma once
#include"PlayerStateProcessBase.h"
#include"CollisionData.h"
#include"CollisionManager.h"

class Input;
class Camera;
class Calculation;

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
	bool UpdateGame(Camera* camera);

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
	VECTOR GetPositionUseCamera();
	float GetAngle() { return angle; }
	int GetHP() { return HP; }
	int GetGripPoint() { return gripPoint; }
	float GetCameraZoom() { return cameraZoom; }
	float GetPiercingArmRotateZ() { return piercingArmRotateZ; }
	bool GetOnPiercingGauge() { return onPiercingGauge; }

private:
	//���
	enum class State :int
	{
		Idle,			//�ҋ@
		Run,			//����
		Jump,			//�W�����v
		NormalAttack,	//�ʏ�U��
		Climb,			//�o��
		Squat,			//���Ⴊ��
		Piercing,		//�˂��h���U��
		FallDown,		//�|���(��������)
		Falling,		//����
	};

	//�p�x�X�V
	void UpdateAngle();
	//�X�e�[�g�ύX
	void ChangeState();
	//�������Ă��邩�m�F
	void CheckOnGround(Camera* camera);
	//�J�v�Z���X�V
	void UpdateCapsule();
	//�����蔻����X�V
	void UpdateCollisionData();
	//�`��ʒu�C��
	void CorrectionDrawPosition();
	//�����߂�
	void CollisionPushBack(CollisionData partsData,CollisionData *hitCollisionData);
	//�A�����͖h�~
	void PreventionContinuousInput();
	//�����Ɏg���\���̂̒��g�̃Z�b�g
	void MoveUseDataSet();
	
	//���N���X
	PlayerStateProcessBase* nowstate;
	Input* input;
	CollisionManager* collisionManager;
	CollisionData bodyCollisionData;
	CollisionData footCollisionData;
	CollisionData hitObjectData;
	CollisionData* hitObjectDataPointer;
	PlayerStateProcessBase::UsePlayerData moveUseData;	//�����Ɏg���f�[�^�\����
	Calculation* calculation;

	//�X�e�[�^�X
	int MaxHP;			//�ő�̗�
	int HP;				//�̗�
	int MaxGripPoint;	//�ő刬��
	int gripPoint;		//���̓Q�[�W

	//����
	int inputstate;									//���͏��
	DINPUT_JOYSTATE stickstate;						//�X�e�B�b�N���͏��
	bool canInputX;									//�U���A�����͖h�~

	//���f���֌W
	int modelHandle;								//���f���n���h��
	VECTOR drawPosition;							//�`��p�|�W�V����
	MATRIX rotateMatrix;							//���f����]�s��

	//�����蔻��
	float WholeBodyCapsuleRadius;					//�S�g�J�v�Z�����a
	float WholeBodyCapsuleHalfLength;				//�J�v�Z���̔����̒���
	float FootCapsuleRadius;						//���J�v�Z�����a
	float positionDistanceGround;					//�|�W�V�����ƒn�ʂ̋���
	VECTOR position;								//�|�W�V����
	VECTOR wholebodyCapStart;						//�J�v�Z���n�_(��)
	VECTOR wholebodyCapEnd;							//�J�v�Z���I�_(��)
	VECTOR centerPosition;							//�J�v�Z���̐^��
	VECTOR footCapStart;							//���J�v�Z��
	VECTOR footCapEnd;								//���J�v�Z��

	//�ړ��֌W
	float angle;									//�v���C���[�̌���
	float changeAngleSpeed;							//�p�x�ύX���x
	VECTOR moveVec;									//�ړ���
	VECTOR targetLookDirection;						//���f���̌����ڕW����
	bool jumpAfterLeaveFoot;						//�W�����v������ɑ������ꂽ
	bool onGround;									//�������Ă��邩
	bool onFootObject;								//�����I�u�W�F�N�g�ɒ����Ă���
	bool isCatch;									//�͂߂��Ԃ�
	PlayerStateProcessBase::RunPlaceKind runPlace;	//�����Ă���ꏊ

	//�����֌W
	State nowstateKind;								//���݂̏��
	bool changeStateflg;							//��Ԃ���̏�ԕύX�w��������ꍇ

	//����
	float Gravity;									//�d��
	float fallSpeed;								//�������x
	int fallFrame;									//��������
	float fallDamage;								//�����_���[�W
	float FallDamageIncrease;						//�����_���[�W�̑�����
	float FallDamageCameraShakingPower;				//�����_���[�W�J�����h�ꋭ��
	float FallDamageCameraShakingDirChangeflame;	//�����_���[�W�J�����̗h��̏㉺��؂�ւ���t���[��
	float FallDamageCameraShakingPlayflame;			//�����_���[�W�h��Đ��t���[��
	float FallDamageJoypadVibPower;					//�����_���[�W�R���g���[���[�h�ꋭ��
	float FallDamageJoypadVibPlayflame;				//�����_���[�W�R���g���[���[�h��t���[��

	//�˂��h���U����
	float cameraZoom;								//�J�����̃Y�[��
	float piercingArmRotateZ;						//�r�̉�]�x
	bool onPiercingGauge;							//�˂��h���U���Q�[�W�\��

	//�o�莞
	int MinusGripPoint;								//���炷���͗�
	VECTOR putCloseVec;								//�I�u�W�F�N�g�Ɨ���Ă��镪�߂Â���x�N�g��

	//���̑�
	bool gameOverflg;								//�Q�[���I�[�o�[�t���O
};