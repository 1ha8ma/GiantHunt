#include"DxLib.h"
#include"Loader.h"
#include"Input.h"
#include"Utility.h"
#include"CollisionData.h"
#include"BGM.h"
#include"ArmEnemyStartScene.h"
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

	//�C���X�^���X��
	input = new Input();
	bgm = new BGM(BGM::BGMKind::Title);

	//private�ϐ�������
	canInputB = false;
	inputOrderAlpha = 255;
	inputOrderflg = true;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	bgm->StopBGM();
	delete bgm;
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

	//bgm�Đ�
	bgm->PlayBGM(BGM::BGMKind::Title);
	
	//���͎w���_��
	if (inputOrderflg)
	{
		inputOrderAlpha -= 2;

		if (inputOrderAlpha <= 100)
		{
			inputOrderAlpha = 100;
			inputOrderflg = false;
		}
	}
	else
	{
		inputOrderAlpha += 2;

		if (inputOrderAlpha >= 255)
		{
			inputOrderAlpha = 255;
			inputOrderflg = true;
		}
	}


	//B�{�^������
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		//return new GameScene(new ArmEnemyStage(), new ArmEnemy());
		return new ArmEnemyStartScene();
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void TitleScene::Draw()
{
	//�w�i
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, titleBackImage, TRUE);
	//�^�C�g����
	SetFontSize(150);
	DrawString(200, 200, "�R�m�Ƌ��l", GetColor(0, 0, 0));

	//�{�^���w��
	//�����x�ύX
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, inputOrderAlpha);
	SetFontSize(50);
	DrawString(500, 500, "Press B Button",GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//�����x�����ɖ߂�
}