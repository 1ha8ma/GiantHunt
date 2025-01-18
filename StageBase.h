#pragma once

class StageBase
{
public:
	StageBase() {};
	virtual ~StageBase() {};

	//�|�W�V�����������߂�
	VECTOR PushBackPosition(VECTOR position, VECTOR moveVec);

	//�X�V
	virtual void Update()abstract;
	//�`��
	virtual void Draw()abstract;

protected:
	const VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);	//���S�_
	
	int modelHandle;		//���f���n���h��
	VECTOR position;
	float circleRadius;		//�~�̔��a
	float stageScale;
};