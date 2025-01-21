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
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	Loader* loader = loader->GetInstance();
	titleBackImage = loader->GetHandle(Loader::Kind::TitleBackImage);

	//インスタンス化
	input = new Input();
	bgm = new BGM(BGM::BGMKind::Title);

	//private変数初期化
	canInputB = false;
	inputOrderAlpha = 255;
	inputOrderflg = true;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
	bgm->StopBGM();
	delete bgm;
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のステート</returns>
SceneBase* TitleScene::Update()
{
	//Bボタン入力可能
	if (!canInputB && (Input::InputNumber::BButton & input->GetInputState()) != Input::InputNumber::BButton)
	{
		canInputB = true;
	}

	//bgm再生
	bgm->PlayBGM(BGM::BGMKind::Title);
	
	//入力指示点滅
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


	//Bボタン入力
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		//return new GameScene(new ArmEnemyStage(), new ArmEnemy());
		return new ArmEnemyStartScene();
	}

	return this;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	//背景
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, titleBackImage, TRUE);
	//タイトル名
	SetFontSize(150);
	DrawString(200, 200, "騎士と巨人", GetColor(0, 0, 0));

	//ボタン指示
	//透明度変更
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, inputOrderAlpha);
	SetFontSize(50);
	DrawString(500, 500, "Press B Button",GetColor(0,0,0));
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//透明度を元に戻す
}