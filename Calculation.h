#pragma once

class Calculation
{
public:
	Calculation() {};
	~Calculation() {};

	//üŒ`•âŠÔ
	VECTOR Lerp(VECTOR targetPos, VECTOR nowPos, float speed, float& t);
	
	//ƒƒhƒŠƒQƒX‚Ì‰ñ“]Œö®
	VECTOR RodriguesRotationFormula(VECTOR shaft, float angle, VECTOR prevVec);
};