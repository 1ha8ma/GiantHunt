#pragma once

class Calculation
{
public:
	Calculation() {};
	~Calculation() {};

	//���`���
	VECTOR Lerp(VECTOR targetPos, VECTOR nowPos, float speed, float& t);
	
	//���h���Q�X�̉�]����
	VECTOR RodriguesRotationFormula(VECTOR shaft, float angle, VECTOR prevVec);
};