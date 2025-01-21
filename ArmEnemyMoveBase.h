#pragma once

class ArmEnemyMoveBase
{
public:
	//�t���[���ԍ�
	enum class ArmEnemyFrameIndex :int
	{
		Upperarm = 16,	//��r
		Forearm = 18,	//�O�r
		Hand = 30,		//��(���w���֐�)
		Finger1 = 22,	//�e�w
		Finger2 = 40,	//���w�̐�
	};

	ArmEnemyMoveBase(int modelHandle,float modelScale);
	virtual ~ArmEnemyMoveBase() {};
	
	virtual bool Update(Camera* camera)abstract;
	virtual void Draw()abstract;

	VECTOR GetRotate() { return rotate; }

protected:
	//�t���[���̉�]����
	MATRIX FrameRotateProcess(int frameIndex, float Xaxis, float Yaxis, float Zaxis);

	int modelHandle;	//���f���n���h��
	float modelScale;	//���f���̃T�C�Y
	VECTOR rotate;		//��]�p
	int moveState;		//�������
};