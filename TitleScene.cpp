#include"DxLib.h"
#include"Loader.h"
#include"Input.h"
#include"Utility.h"
#include"CollisionData.h"
#include"GameScene.h"
#include"ArmEnemyStage.h"
#include"ArmEnemy.h"
#include"TitleScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
{
	Loader* loader = loader->GetInstance();
	titleBackImage = loader->GetHandle(Loader::Kind::TitleBackImage);

	input = new Input();
	//private�ϐ�������
	canInputB = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃X�e�[�g</returns>
SceneBase* TitleScene::Update()
{
	//B�{�^�����͉\
	if (!canInputB && (Input::InputNumber::BButton & input->GetInputState()) != Input::InputNumber::BButton)
	{
		canInputB = true;
	}

	//B�{�^������
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		return new GameScene(new ArmEnemyStage(), new ArmEnemy());
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, titleBackImage, TRUE);
	SetFontSize(150);
	DrawString(200, 300, "�����_�Ƌ���", GetColor(0, 0, 0));
}