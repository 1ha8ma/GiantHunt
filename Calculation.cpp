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

/// <summary>
/// 2�_�̋���(3����)
/// </summary>
/// <param name="pos1">�_1</param>
/// <param name="pos2">�_2</param>
/// <returns>����</returns>
float Calculation::LengthTwoPoint3D(VECTOR pos1, VECTOR pos2)
{
	float calc1 = pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2);
	float length = sqrtf(calc1);
	return length;
}

/// <summary>
/// 2�̃x�N�g���̂Ȃ��p
/// </summary>
/// <param name="vec1">�x�N�g��1</param>
/// <param name="vec2">�x�N�g��2</param>
/// <returns>�p�x</returns>
float Calculation::AngleTwoVector(VECTOR vec1, VECTOR vec2)
{
	float calc1 = VDot(vec1, vec2);
	float calc2 = sqrtf(pow(vec1.x, 2) + pow(vec1.y, 2) + pow(vec1.z, 2)) * sqrtf(pow(vec2.x, 2) + pow(vec2.y, 2) + pow(vec2.z, 2));
	float cosTheta = calc1 / calc2;

	float angle = acos(cosTheta);

	float deg = angle * (180 / DX_PI_F);//�m�F�p

	return angle;
}

/// <summary>
/// ���ˉe�x�N�g��
/// </summary>
/// <param name="OA">���_���琂�����~�낳��鑤�̃x�N�g��</param>
/// <param name="OB">���_���琂�����~�낷���̃x�N�g��</param>
/// <returns>�~�낵���_</returns>
VECTOR Calculation::OrthogonalProjectionVector(VECTOR OA, VECTOR OB)
{
	float calc1 = VDot(OA, OB);
	float calc2 = pow(OA.x, 2) + pow(OA.y, 2) + pow(OA.z, 2);
	float calc3 = calc1 / calc2;
	VECTOR OH = VScale(OA, calc3);

	return OH;
}