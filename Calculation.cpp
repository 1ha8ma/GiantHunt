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

