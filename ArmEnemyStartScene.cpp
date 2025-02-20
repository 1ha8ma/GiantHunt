#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Camera.h"
#include"ArmEnemy.h"
#include"ArmEnemyStage.h"
#include"Player.h"
#include"GameScene.h"
#include"Time.h"
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
	cameraPosition = VGet(5000, 2500, -1500);
	cameraLookPosition = VGet(500, 1000, 1000);
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
	camera->StartSceneInitialize(cameraPosition, cameraLookPosition);
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* ArmEnemyStartScene::Update()
{
	//更新
	camera->UpdateStartScene(cameraPosition, cameraLookPosition);
	if (cameraPosition.y >= 2000)
	{
		cameraPosition.z -= 4;
	}
	if (cameraLookPosition.y < 6000)
	{
		cameraLookPosition.y += 20;
	}

	//黒帯を濃くする
	if (blackBandAlpha < MaxBlackBandAlpha)
	{
		blackBandAlpha += 3;
		if (blackBandAlpha >= MaxBlackBandAlpha)
		{
			blackBandAlpha = MaxBlackBandAlpha;
		}
	}

	//シーン変更
	if (flame == 400)//400
	{
		player->StartSceneEnd();
		return new GameScene(stage, enemy, camera, player, Time::StageTag::ArmEnemy);
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, MaxAlpha);
}