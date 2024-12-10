#include"DxLib.h"
#include"Loader.h"

//�C���X�^���X���ŏ��ɋ�ɂ���
Loader* Loader::loader = nullptr;

/// <summary>
/// �C���X�^���X�Q�b�g
/// </summary>
/// <returns>�C���X�^���X</returns>
Loader* Loader::GetInstance()
{
	//�C���X�^���X��������ΐ���
	if (loader == nullptr)
	{
		loader = new Loader();
	}

	return loader;
}

/// <summary>
/// ���[�h
/// </summary>
void Loader::Load()
{
	//3D
	handle[ArmEnemyStage] = MV1LoadModel("3D/ArmEnemyStage.mv1");
	handle[PlayerModel] = MV1LoadModel("3D/Player.mv1");

	//2D

	//��

	//�G�t�F�N�g
}