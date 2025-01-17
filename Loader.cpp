#include"DxLib.h"
#include"EffekseerForDXLib.h"
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
	handle[WallModel] = MV1LoadModel("3D/Wall.mv1");
	handle[ArmEnemyModel] = MV1LoadModel("3D/monster.mv1");
	handle[WoodModel] = MV1LoadModel("3D/Wood.mv1");

	//2D
	handle[GameOverBackImage] = LoadGraph("2D/GameOverBack.jpg");
	handle[TitleBackImage] = LoadGraph("2D/TitleBack.jpg");

	//��

	//�G�t�F�N�g
	handle[WeakPointEffect] = LoadEffekseerEffect("Effect/WeakPoint.efkefc", 1.0f);
}