#pragma once
#include"ArmEnemyMoveBase.h"

class ArmEnemyFallDown :public ArmEnemyMoveBase
{
public:
	ArmEnemyFallDown(int modelHandle);
	~ArmEnemyFallDown()override;

	bool UpdateFallDown(Camera* camera)override;
	void Draw()override;

private:
	const float CameraShakingPower = 3.0;		//�J�����h�ꋭ��
	const int CameraShakingChangeDirflame = 10;	//�J�����㉺�h��ύX�t���[��
	const int CameraShakinPlayflame = 50;		//�J�����h��Đ��t���[��
	const int JoyPadVibPower = 300;				//�R���g���[���[�U������
	const int JoyPadVibflame = 1200;				//�R���g���[���[�U���t���[��
};