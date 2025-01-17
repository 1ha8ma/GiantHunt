#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Camera.h"
#include"CollisionManager.h"
#include"ArmEnemy.h"
#include"ArmEnemyStage.h"
#include"Wall.h"
#include"Wood.h"
#include"Player.h"
#include"GameUI.h"
#include"GameOverScene.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
	collisionManager = collisionManager->GetInstance();
	camera = new Camera();
	armEnemyStage = new ArmEnemyStage();
	player = new Player();
	wall = new Wall();
	armEnemy = new ArmEnemy();
	wood = new Wood();
	ui = new GameUI(armEnemy->GetHP(),player->GetHP(),player->GetGripPoint());

	gameOver = false;
	gameClear = false;
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete armEnemyStage;
	delete player;
	delete wall;
	delete armEnemy;
	delete wood;
	delete ui;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize()
{
	camera->Initialize(player->GetPosition());
	collisionManager->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	//エフェクトカメラ同期
	Effekseer_Sync3DSetting();

	camera->Update(player->GetPosition(), armEnemy->GetTargetCameraPosition());
	gameOver = player->Update(*camera);
	armEnemy->Update(player->GetPosition(),camera);
	ui->Update(armEnemy->GetHP(), player->GetHP(), player->GetGripPoint());

	//当たり判定
	collisionManager->Update();

	//Effekseer更新
	UpdateEffekseer3D();

	//ゲームオーバー
	if (gameOver)
	{
		return new GameOverScene();
	}

	return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
	armEnemyStage->Draw();
	wall->Draw();
	wood->Draw();
	player->Draw();
	armEnemy->Draw();
	ui->Draw();
}