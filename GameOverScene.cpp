#include"DxLib.h"
#include"Loader.h"
#include"Utility.h"
#include"Input.h"
#include"TitleScene.h"
#include"GameOverScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOverScene::GameOverScene()
{
	Loader* loader = loader->GetInstance();
	//�n���h�����[�h
	backImage = loader->GetHandle(Loader::Kind::GameOverBackImage);

	input = new Input();

	//private�ϐ�������
	canInputB = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOverScene::~GameOverScene()
{

}

/// <summary>
/// ������
/// </summary>
void GameOverScene::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameOverScene::Update()
{
	//B�{�^�����͉\
	if (!canInputB && (Input::InputNumber::BButton & input->GetInputState()) != Input::InputNumber::BButton)
	{
		canInputB = true;
	}

	//B�{�^������
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		return new TitleScene();
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameOverScene::Draw()
{
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, backImage, true);
	SetFontSize(100);
	DrawString(600, 400, "Game Over", GetColor(240, 248, 255));
}