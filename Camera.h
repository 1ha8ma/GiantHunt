#pragma once

class Input;
class Calculation;

class Camera
{
public:
	Camera();

	//�X�^�[�g�V�[��������
	void StartSceneInitialize();
	//�X�^�[�g�V�[���X�V
	void UpdateStartScene();

	//�Q�[���V�[��������
	void GameInitialize(VECTOR playerpos);
	//�X�V
	void UpdateGame(VECTOR playerPosition,VECTOR targetCameraPosition);

	//�Q�[���I�[�o�[�V�[��������
	void InitializeGameOver(VECTOR playerPosition);
	//�Q�[���I�[�o�[�V�[���X�V
	void UpdateGameOver();
	
	//���o
	void PlayShakingVertical(float shakingPower, int shakingDirectionChangeflame, int flame);

	//GetSet
	float GetangleH() { return angleH; }
	float GetangleV() { return angleV; }
	VECTOR GetLookPosition() { return lookPosition; }
	VECTOR GetPosition() { return position; }

private:
	const float AngleSpeed = 0.03f;					//����p�x
	const float CameraPlayerTargetHeight = 100.0f;	//�v���C���[�̂ǂꂾ�������Ƃ�������邩
	const float PlayerDistance = 300;				//�v���C���[�Ƃ̋���
	const float CollisionSize = 50.0f;				//�J�����̓����蔻��T�C�Y

	//���o�X�V
	void UpdateProduction(VECTOR playerPosition);
	//�㉺�h��
	void ShakingVertical(VECTOR playerPosition);

	//���N���X
	Input* input;
	Calculation* calculation;

	VECTOR position;		//�|�W�V����
	VECTOR lookPosition;	//�����_
	float angleH;			//���ʊp�x
	float angleV;			//�����p�x
	VECTOR lookTargetPos;	//�ڕW�̒����_���W
	float t;				//Lerp�p
	bool lerpflg;			//Lerp�J�n�t���O

	//���o
	bool productionflg;					//���o���t���O
	int totalflame;						//���o�t���[��
	//�c�h��
	int changeflame;					//�؂�ւ��܂ł̃t���[��
	bool shakingDirection;				//�h�������t���O
	bool shakingVerticalflg;			//�c�h��t���O
	float shakingPower;					//�h��̋���
	int shakingDirectionChangeflame;	//�h��������ύX����t���[��
	int playflame;						//�Đ�����
};