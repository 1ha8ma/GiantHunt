#pragma once

class Input;

class Camera
{
public:
	Camera();

	//������
	void Initialize(VECTOR playerpos);
	//�X�V
	void Update(VECTOR playerPosition,float lookAngle,VECTOR enemyPosition);

	float GetangleH() { return angleH; }
	float GetangleV() { return angleV; }
	VECTOR GetLookPosition() { return lookPosition; }
	VECTOR GetPosition() { return position; }

private:
	const float AngleSpeed = 0.03f;					//����p�x
	const float CameraPlayerTargetHeight = 100.0f;	//�v���C���[�̂ǂꂾ�������Ƃ�������邩
	const float PlayerDistance = 300;				//�v���C���[�Ƃ̋���
	const float CollisionSize = 50.0f;				//�J�����̓����蔻��T�C�Y

	//���N���X
	Input* input;

	VECTOR position;		//�|�W�V����
	VECTOR lookPosition;	//�����_
	float angleH;			//���ʊp�x
	float angleV;			//�����p�x
	VECTOR lookTargetPos;	//�ڕW�̒����_���W
	float t;				//Lerp�p
	bool lerpflg;			//Lerp�J�n�t���O
};