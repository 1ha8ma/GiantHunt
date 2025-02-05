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

	//2�̃x�N�g���̂Ȃ��p
	float AngleTwoVector(VECTOR vec1, VECTOR vec2);

	/// <summary>
	/// ���ˉe�x�N�g��
	/// </summary>
	/// <param name="OA">���_���琂�����~�낳��鑤�̃x�N�g��</param>
	/// <param name="OB">���_���琂�����~�낷���̃x�N�g��</param>
	/// <returns></returns>
	VECTOR OrthogonalProjectionVector(VECTOR OA, VECTOR OB);
};