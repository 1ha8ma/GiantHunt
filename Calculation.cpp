#include<math.h>
#include"DxLib.h"
#include"Calculation.h"

/// <summary>
/// ���`���
/// </summary>
/// <param name="targetPos">�ڕW�̃|�W�V����</param>
/// <param name="nowPos">���݂̃|�W�V����</param>
/// <param name="speed">���x</param>
/// <param name="t">����</param>
VECTOR Calculation::Lerp(VECTOR targetPos, VECTOR nowPos, float speed, float &t)
{
	VECTOR copypos = nowPos;
	copypos = VAdd(copypos, VScale((VSub(targetPos, copypos)), t));

	//�߂Â���
	t += speed;

	return copypos;
}

