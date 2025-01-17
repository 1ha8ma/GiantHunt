#include"DxLib.h"
#include"Loader.h"
#include"Utility.h"
#include"Input.h"
#include"TitleScene.h"
#include"GameOverScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameOverScene::GameOverScene()
{
	Loader* loader = loader->GetInstance();
	//ハンドルロード
	backImage = loader->GetHandle(Loader::Kind::GameOverBackImage);

	input = new Input();

	//private変数初期化
	canInputB = false;
}

/// <summary>
/// デストラクタ
/// </summary>
GameOverScene::~GameOverScene()
{

}

/// <summary>
/// 初期化
/// </summary>
void GameOverScene::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameOverScene::Update()
{
	//Bボタン入力可能
	if (!canInputB && (Input::InputNumber::BButton & input->GetInputState()) != Input::InputNumber::BButton)
	{
		canInputB = true;
	}

	//Bボタン入力
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		return new TitleScene();
	}

	return this;
}

/// <summary>
/// 描画
/// </summary>
void GameOverScene::Draw()
{
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, backImage, true);
	SetFontSize(100);
	DrawString(600, 400, "Game Over", GetColor(240, 248, 255));
}