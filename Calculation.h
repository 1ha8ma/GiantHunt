#pragma once

class Calculation
{
public:
	Calculation() {};
	~Calculation() {};

	//線形補間
	VECTOR Lerp(VECTOR targetPos, VECTOR nowPos, float speed, float& t);
	
	//ロドリゲスの回転公式
	VECTOR RodriguesRotationFormula(VECTOR shaft, float angle, VECTOR prevVec);

	//2点の距離(3次元)
	float LengthTwoPoint3D(VECTOR pos1, VECTOR pos2);
};