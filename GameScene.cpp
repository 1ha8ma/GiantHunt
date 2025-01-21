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
/// �R���X�g���N�^
/// </summary>
/// <param name="stage">�X�e�[�W�C���X�^���X</param>
/// <param name="enemy">�G�C���X�^���X</param>
GameScene::GameScene(StageBase* stage, EnemyBase* enemy,Camera* camera,Player* player)
{
	//�C���X�^���X��
	collisionManager = collisionManager->GetInstance();
	this->camera = camera;
	this->stage = stage;
	this->player = player;
	this->player->InitializeGame();
	this->enemy = enemy;
	ui = new GameUI(this->enemy->GetHP(), player->GetHP(), player->GetGripPoint());

	//�ϐ�������
	gameOver = false;
	gameClear = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	/*delete camera;
	delete stage;
	delete player;
	delete enemy;*/
	delete ui;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	collisionManager->Initialize();

	camera->GameInitialize(player->GetPosition());
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	//�G�t�F�N�g�J��������
	Effekseer_Sync3DSetting();

	//�N���X�X�V
	stage->Update();
	camera->UpdateGame(player->GetPosition(), enemy->GetTargetCameraPosition());
	gameOver = player->UpdateGame(*camera);
	gameClear = enemy->Update(player->GetPosition(), camera);
	ui->Update(enemy->GetHP(), player->GetHP(), player->GetGripPoint());

	//�����蔻��
	collisionManager->Update();

	//Effekseer�X�V
	UpdateEffekseer3D();

	//�Q�[���I�[�o�[
	if (gameOver)
	{
		return new GameOverScene(stage, enemy, camera, player);
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	stage->Draw();
	player->Draw();
	enemy->Draw();
	ui->Draw();
}