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
	t += speed;

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