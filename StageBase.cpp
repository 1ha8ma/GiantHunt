#include<math.h>
#include"DxLib.h"
#include"Loader.h"
#include"StageBase.h"

/// <summary>
/// �ړ��x�N�g���̉����߂�
/// </summary>
/// <param name="position">���݂̃|�W�V����</param>
/// <param name="moveVec">�ړ��x�N�g��</param>
/// <returns>�����߂���</returns>
VECTOR StageBase::PushBackPosition(VECTOR position, VECTOR moveVec)
{
	VECTOR backVec = VGet(0, 0, 0);
	VECTOR nextPos = VAdd(position, moveVec);//�ړ���
	nextPos.y = 0.0f;

	//���S����̋��������
	float calc = pow((nextPos.x - centerPosition.x), 2.0f) + pow((nextPos.z - centerPosition.z), 2.0f);
	float distance = sqrtf(calc);

	//���������a�ȏ�Ȃ�
	if (distance > circleRadius)
	{
		while (1)
		{
			backVec = VAdd(backVec, VGet(0.1f, 0.0f, 0.1f));//�߂��ʂ����Z
			VECTOR backafterPos = VSub(nextPos, backVec);

			//���S����̋��������
			float calc = pow((backafterPos.x - centerPosition.x), 2.0f) + pow((backafterPos.z - centerPosition.z), 2.0f);
			float distance = sqrtf(calc);

			//���a�ȓ��܂Ŗ߂�
			if (distance < circleRadius)
			{
				break;
			}
		}
	}

	return backVec;
}

/// <summary>
/// �`��
/// </summary>
//void StageBase::Draw()
//{
//	MV1DrawModel(modelHandle);
//}