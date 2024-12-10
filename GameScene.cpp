#include"DxLib.h"
#include"Camera.h"
#include"ArmEnemyStage.h"
#include"Player.h"
#include"GameScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	//�C���X�^���X��
	camera = new Camera();
	armEnemyStage = new ArmEnemyStage();
	player = new Player();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete armEnemyStage;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	camera->Update(player->GetPosition(), player->GetAngle());
	player->Update();

	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	armEnemyStage->Draw();
	player->Draw();
}