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

/// <summary>
/// ���h���Q�X�̉�]����
/// </summary>
/// <param name="shaft">��</param>
/// <param name="angle">��]�p�x</param>
/// <param name="prevVec">��]�O�̃x�N�g��</param>
/// <returns>��]��̃x�N�g��</returns>
VECTOR Calculation::RodriguesRotationFormula(VECTOR shaft, float angle, VECTOR prevVec)
{
	VECTOR unitVec = VNorm(shaft);//�P�ʃx�N�g��
	VECTOR newVec;//��]��̃x�N�g��

	VECTOR calc1 = VScale(prevVec, cos(angle));
	VECTOR calc2 = VScale(unitVec, VDot(prevVec, unitVec));
	calc2 = VScale(calc2, (1 - cos(angle)));
	VECTOR calc3 = VCross(unitVec, prevVec);
	calc3 = VScale(calc3, sin(angle));

	newVec = VAdd(calc1, calc2);
	newVec = VAdd(newVec, calc3);

	return newVec;
}