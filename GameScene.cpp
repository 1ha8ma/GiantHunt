#include"DxLib.h"
#include"Camera.h"
#include"CollisionManager.h"
#include"ArmEnemy.h"
#include"ArmEnemyStage.h"
#include"Wall.h"
#include"Wood.h"
#include"Player.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
	camera = new Camera();
	collisionManager = collisionManager->GetInstance();
	armEnemyStage = new ArmEnemyStage();
	player = new Player();
	wall = new Wall();
	armEnemy = new ArmEnemy();
	wood = new Wood();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete collisionManager;
	delete armEnemyStage;
	delete player;
	delete wall;
	delete armEnemy;
	delete wood;
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
	camera->Update(player->GetPosition(), VGet(2000.0f, 2000.0f, 6550.0f));
	player->Update(*camera);
	armEnemy->Update();

	//当たり判定
	collisionManager->Update();

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
}