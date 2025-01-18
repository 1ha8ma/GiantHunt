#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"CollisionManager.h"
#include"Camera.h"
#include"EnemyBase.h"
#include"StageBase.h"
#include"Player.h"
#include"GameUI.h"
#include"GameOverScene.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stage">ステージインスタンス</param>
/// <param name="enemy">敵インスタンス</param>
GameScene::GameScene(StageBase* stage, EnemyBase* enemy)
{
	//インスタンス化
	collisionManager = collisionManager->GetInstance();
	camera = new Camera();
	this->stage = stage;
	player = new Player();
	this->enemy = enemy;
	ui = new GameUI(this->enemy->GetHP(), player->GetHP(), player->GetGripPoint());

	//変数初期化
	gameOver = false;
	gameClear = false;
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete stage;
	delete player;
	delete enemy;
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

	//クラス更新
	stage->Update();
	camera->Update(player->GetPosition(), enemy->GetTargetCameraPosition());
	gameOver = player->Update(*camera);
	gameClear = enemy->Update(player->GetPosition(), camera);
	ui->Update(enemy->GetHP(), player->GetHP(), player->GetGripPoint());

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
	stage->Draw();
	player->Draw();
	enemy->Draw();
	ui->Draw();
}