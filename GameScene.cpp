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
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	//�C���X�^���X��
	camera = new Camera();
	collisionManager = collisionManager->GetInstance();
	armEnemyStage = new ArmEnemyStage();
	player = new Player();
	wall = new Wall();
	armEnemy = new ArmEnemy();
	wood = new Wood();
}

/// <summary>
/// �f�X�g���N�^
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
/// ������
/// </summary>
void GameScene::Initialize()
{
	camera->Initialize(player->GetPosition());
	collisionManager->Initialize();
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	camera->Update(player->GetPosition(), VGet(2000.0f, 2000.0f, 6550.0f));
	player->Update(*camera);
	armEnemy->Update();

	//�����蔻��
	collisionManager->Update();

	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	armEnemyStage->Draw();
	wall->Draw();
	wood->Draw();
	player->Draw();
	armEnemy->Draw();
}