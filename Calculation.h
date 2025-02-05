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

	//2つのベクトルのなす角
	float AngleTwoVector(VECTOR vec1, VECTOR vec2);

	/// <summary>
	/// 正射影ベクトル
	/// </summary>
	/// <param name="OA">原点から垂線を降ろされる側のベクトル</param>
	/// <param name="OB">原点から垂線を降ろす側のベクトル</param>
	/// <returns></returns>
	VECTOR OrthogonalProjectionVector(VECTOR OA, VECTOR OB);
};