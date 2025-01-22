#include<vector>
#include"DxLib.h"
#include"ArmEnemyMoveBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ArmEnemyMoveBase::ArmEnemyMoveBase(int modelHandle,float modelScale)
{
	this->modelHandle = modelHandle;
	this->modelScale = modelScale;
}

/// <summary>
/// �t���[���̉�]����
/// </summary>
/// <param name="frameIndex">�t���[���ԍ�</param>
/// <param name="Xaxis">X����]</param>
/// <param name="Yaxis">Y����]</param>
/// <param name="Zaxis">Z����]</param>
/// <returns>��]�����邽�߂̍s��</returns>
MATRIX ArmEnemyMoveBase::FrameRotateProcess(int frameIndex, float Xaxis, float Yaxis, float Zaxis)
{
	//�e�t���[���̎擾
	int ParentFrame = MV1GetFrameParent(modelHandle, frameIndex);

	//���f���̊g�嗦�ɏ]���Ĉړ�������␳���鏀��
	float correctionScale;
	if (0 != modelScale)
	{
		correctionScale = 1 / modelScale;
	}
	else
	{
		return MGetIdent();
	}

	//���΍��W���̕��s�ړ��s����擾
	MATRIX MTranslate;
	if (-2 != ParentFrame)
	{
		//�e�q�t���[���̍��W�̎擾
		VECTOR vecParent = MV1GetFramePosition(modelHandle, ParentFrame);
		VECTOR vecChild = MV1GetFramePosition(modelHandle, frameIndex);

		//�e����ɂ����q�̑��΍��W���擾
		VECTOR vecRerativPar2Chi = VSub(vecChild, vecParent);
		//���f���̊g�嗦�ɂ���đ��΋�����␳
		vecRerativPar2Chi = VScale(vecRerativPar2Chi, correctionScale);
		MTranslate = MGetTranslate(vecRerativPar2Chi);
	}
	else
	{
		MTranslate = MGetIdent();
	}

	//���ꂼ��̎��ɉ����ĉ�]����s����擾
	MATRIX MXaxis = MGetRotX(Xaxis);
	MATRIX MYaxis = MGetRotY(Yaxis);
	MATRIX MZaxis = MGetRotZ(Zaxis);

	////�k���Đe�t���[���̉�]�v�f�̎擾
	//std::vector<MATRIX> MParentsRotates;
	//while (-2 != ParentFrame && -1 != ParentFrame)
	//{
	//	//�e�t���[�����W���擾���A���������]�v�f�𒊏o
	//	MATRIX MParentFrame = MV1GetFrameLocalMatrix(modelHandle, ParentFrame);
	//	MATRIX MParentRotate = MGetRotElem(MParentFrame);
	//	//��]�s��̋t�s��=��]�̕������t�ɂ���
	//	MATRIX MInvParentRotate = MInverse(MParentRotate);
	//	//���ɒǉ�
	//	MParentsRotates.push_back(MInvParentRotate);

	//	//�X�ɐe�̃t���[�����擾
	//	ParentFrame = MV1GetFrameParent(modelHandle, ParentFrame);
	//}
	////�擾�����c�悽���̉�]�s�����蒆���̕����炩���āA���s�ړ��̃x�N�g����␳����
	//for (int i = MParentsRotates.size() - 1; i >= 0; i--)
	//{
	//	MTranslate = MMult(MTranslate, MParentsRotates[i]);
	//}
	////���s�ړ��x�N�g���ɐ��������]����������
	//MTranslate.m[0][0] = 1;	MTranslate.m[0][1] = 0;	MTranslate.m[0][2] = 0;
	//MTranslate.m[1][0] = 0;	MTranslate.m[1][1] = 1;	MTranslate.m[1][2] = 0;
	//MTranslate.m[2][0] = 0;	MTranslate.m[2][1] = 0;	MTranslate.m[2][2] = 1;

	//�����ɉ�]�����Ă��畽�s�ړ������s����
	MATRIX MReturn = MMult(MMult(MMult(MXaxis, MYaxis), MZaxis), MTranslate);

	return MReturn;
}