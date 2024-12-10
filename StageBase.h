#pragma once

class StageBase
{
public:
	//�|�W�V�����������߂�
	VECTOR PushBackPosition(VECTOR position, VECTOR moveVec);
	//�`��
	void Draw();

protected:
	const VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);	//���S�_
	
	int modelHandle;		//���f���n���h��
	VECTOR position;
	float circleRadius;		//�~�̔��a
	float stageScale;
};