#include<math.h>
#include"DxLib.h"
#include"Calculation.h"

/// <summary>
/// 線形補間
/// </summary>
/// <param name="targetPos">目標のポジション</param>
/// <param name="nowPos">現在のポジション</param>
/// <param name="speed">速度</param>
/// <param name="t">割合</param>
VECTOR Calculation::Lerp(VECTOR targetPos, VECTOR nowPos, float speed, float &t)
{
	VECTOR copypos = nowPos;
	copypos = VAdd(copypos, VScale((VSub(targetPos, copypos)), t));

	//近づける
	if (t < 1)
	{
		t += speed;
		if (t >= 1)
		{
			t = 1;
		}
	}

	return copypos;
}

/// <summary>
/// ロドリゲスの回転公式
/// </summary>
/// <param name="shaft">軸</param>
/// <param name="angle">回転角度</param>
/// <param name="prevVec">回転前のベクトル</param>
/// <returns>回転後のベクトル</returns>
VECTOR Calculation::RodriguesRotationFormula(VECTOR shaft, float angle, VECTOR prevVec)
{
	VECTOR unitVec = VNorm(shaft);//単位ベクトル
	VECTOR newVec;//回転後のベクトル

	VECTOR calc1 = VScale(prevVec, cos(angle));
	VECTOR calc2 = VScale(unitVec, VDot(prevVec, unitVec));
	calc2 = VScale(calc2, (1 - cos(angle)));
	VECTOR calc3 = VCross(unitVec, prevVec);
	calc3 = VScale(calc3, sin(angle));

	newVec = VAdd(calc1, calc2);
	newVec = VAdd(newVec, calc3);

	return newVec;
}

/// <summary>
/// 2点の距離(3次元)
/// </summary>
/// <param name="pos1">点1</param>
/// <param name="pos2">点2</param>
/// <returns>距離</returns>
float Calculation::LengthTwoPoint3D(VECTOR pos1, VECTOR pos2)
{
	float calc1 = pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2);
	float length = sqrtf(calc1);
	return length;
}

/// <summary>
/// 2つのベクトルのなす角
/// </summary>
/// <param name="vec1">ベクトル1</param>
/// <param name="vec2">ベクトル2</param>
/// <returns>角度</returns>
float Calculation::AngleTwoVector(VECTOR vec1, VECTOR vec2)
{
	float calc1 = VDot(vec1, vec2);
	float calc2 = sqrtf(pow(vec1.x, 2) + pow(vec1.y, 2) + pow(vec1.z, 2)) * sqrtf(pow(vec2.x, 2) + pow(vec2.y, 2) + pow(vec2.z, 2));
	float cosTheta = calc1 / calc2;

	float angle = acos(cosTheta);

	float deg = angle * (180 / DX_PI_F);//確認用

	return angle;
}

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="OA">原点から垂線を降ろされる側のベクトル</param>
/// <param name="OB">原点から垂線を降ろす側のベクトル</param>
/// <returns>降ろした点</returns>
VECTOR Calculation::OrthogonalProjectionVector(VECTOR OA, VECTOR OB)
{
	float calc1 = VDot(OA, OB);
	float calc2 = pow(OA.x, 2) + pow(OA.y, 2) + pow(OA.z, 2);
	float calc3 = calc1 / calc2;
	VECTOR OH = VScale(OA, calc3);

	return OH;
}