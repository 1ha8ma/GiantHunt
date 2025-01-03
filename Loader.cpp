#include"DxLib.h"
#include"Loader.h"

//インスタンスを最初に空にする
Loader* Loader::loader = nullptr;

/// <summary>
/// インスタンスゲット
/// </summary>
/// <returns>インスタンス</returns>
Loader* Loader::GetInstance()
{
	//インスタンスが無ければ生成
	if (loader == nullptr)
	{
		loader = new Loader();
	}

	return loader;
}

/// <summary>
/// ロード
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

	//音

	//エフェクト
}