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

	//2�_�̋���(3����)
	float LengthTwoPoint3D(VECTOR pos1, VECTOR pos2);
};