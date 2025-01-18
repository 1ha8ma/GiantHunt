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
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	Loader* loader = loader->GetInstance();
	titleBackImage = loader->GetHandle(Loader::Kind::TitleBackImage);

	input = new Input();
	//private変数初期化
	canInputB = false;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

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

	//Bボタン入力
	if (canInputB && (Input::InputNumber::BButton & input->GetInputState()) == Input::InputNumber::BButton)
	{
		return new GameScene(new ArmEnemyStage(), new ArmEnemy());
	}

	return this;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, titleBackImage, TRUE);
	SetFontSize(150);
	DrawString(200, 300, "ワンダと巨像", GetColor(0, 0, 0));
}