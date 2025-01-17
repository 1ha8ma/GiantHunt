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
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	//�C���X�^���X��
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
/// �f�X�g���N�^
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
	//�G�t�F�N�g�J��������
	Effekseer_Sync3DSetting();

	camera->Update(player->GetPosition(), armEnemy->GetTargetCameraPosition());
	gameOver = player->Update(*camera);
	armEnemy->Update(player->GetPosition(),camera);
	ui->Update(armEnemy->GetHP(), player->GetHP(), player->GetGripPoint());

	//�����蔻��
	collisionManager->Update();

	//Effekseer�X�V
	UpdateEffekseer3D();

	//�Q�[���I�[�o�[
	if (gameOver)
	{
		return new GameOverScene();
	}

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
	ui->Draw();
}