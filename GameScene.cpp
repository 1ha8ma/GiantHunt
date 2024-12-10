#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemyStage.h"
#include"Player.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
	camera = new Camera();
	armEnemyStage = new ArmEnemyStage();
	player = new Player();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete armEnemyStage;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	camera->Update(player->GetPosition(), player->GetAngle());
	player->Update();

	return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
	armEnemyStage->Draw();
	player->Draw();
}