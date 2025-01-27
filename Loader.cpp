#include"DxLib.h"
#include"EffekseerForDXLib.h"
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
	handle[SkyDome] = MV1LoadModel("3D/Dome_Y901.x");
	handle[Enemy2Model] = MV1LoadModel("3D/Enemy2.mv1");

	//2D
	handle[GameOverBackImage] = LoadGraph("2D/GameOverBack.jpg");
	handle[TitleBackImage] = LoadGraph("2D/TitleBack.jpg");
	handle[RankingArmEnemyImage] = LoadGraph("2D/RankingArmEnemy.png");
	handle[ClearTextBackImage] = LoadGraph("2D/ClearTextBack.png");
	handle[TutorialBackImage] = LoadGraph("2D/TutorialBack.jpg");

	//BGM
	handle[TitleBGM] = LoadSoundMem("Sound/BGM/TitleBGM.mp3");
	handle[GameOverBGM] = LoadSoundMem("Sound/BGM/GameOverBGM.mp3");
	handle[ArmEnemyBGM] = LoadSoundMem("Sound/BGM/ArmEnemyBGM.mp3");
	handle[GameClearBGM] = LoadSoundMem("Sound/BGM/GameClearBGM.mp3");
	handle[RankingBGM] = LoadSoundMem("Sound/BGM/RankingBGM.mp3");

	//SE
	handle[MowinDownSE] = LoadSoundMem("Sound/SE/MowingDownSE.mp3");
	handle[NormalAttackSE] = LoadSoundMem("Sound/SE/NormalAttackSE.mp3");
	handle[SwingSE] = LoadSoundMem("Sound/SE/SwingSE.mp3");
	handle[HitWeakPointSE] = LoadSoundMem("Sound/SE/HitWeakPointSE.mp3");
	handle[CursorMoveSE] = LoadSoundMem("Sound/SE/CursorMoveSE.mp3");
	handle[CrickSE] = LoadSoundMem("Sound/SE/CrickSE.mp3");

	//エフェクト
	handle[WeakPointEffect] = LoadEffekseerEffect("Effect/WeakPoint.efkefc", 1.0f);
	handle[HitWeakPointEffect] = LoadEffekseerEffect("Effect/HitWeakPoint.efkefc", 1.0f);
}