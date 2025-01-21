#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Camera.h"
#include"ArmEnemy.h"
#include"ArmEnemyStage.h"
#include"Player.h"
#include"GameScene.h"
#include"ArmEnemyStartScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemyStartScene::ArmEnemyStartScene()
{
	camera = new Camera();
	player = new Player();
	stage = new ArmEnemyStage();
	enemy = new ArmEnemy();

	//変数初期化
	flame = 0;
	blackBandAlpha = 0;
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemyStartScene::~ArmEnemyStartScene()
{
	
}

/// <summary>
/// 初期化
/// </summary>
void ArmEnemyStartScene::Initialize()
{
	camera->StartSceneInitialize();
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* ArmEnemyStartScene::Update()
{
	//更新
	camera->UpdateStartScene();

	if (blackBandAlpha < 255)
	{
		blackBandAlpha += 3;
		if (blackBandAlpha >= 255)
		{
			blackBandAlpha = 255;
		}
	}

	//シーン変更
	if (flame == 300)
	{
		player->StartSceneEnd();
		return new GameScene(stage, enemy, camera, player);
	}

	flame++;
	return this;
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemyStartScene::Draw()
{
	stage->Draw();
	player->Draw();
	enemy->Draw();

	//上下黒帯
	//透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackBandAlpha);
	DrawBox(0, 0, SCREEN_W, 100, GetColor(0, 0, 0), TRUE);
	DrawBox(0, SCREEN_H - 100, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}