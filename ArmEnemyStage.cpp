#include"DxLib.h"
#include"Loader.h"
#include"CollisionManager.h"
#include"BGM.h"
#include"Wood.h"
#include"Rock.h"
#include"Wall.h"
#include"ArmEnemyStage.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemyStage::ArmEnemyStage()
{
	//インスタンス化
	Loader* loader = loader->GetInstance();
	wood = new Wood();
	wall = new Wall();
	rock1 = new Rock(loader->GetHandle(Loader::Kind::RockModel1), VGet(400, 0, 0), VGet(-400, 0, 50), 1000.0f, VGet(500, 2300, 4400), VGet(0, 0, DX_PI_F/2), 5);
	rock2 = new Rock(loader->GetHandle(Loader::Kind::RockModel2), VGet(200, 200, 0), VGet(-700, 200, 0), 900.0f, VGet(3700, 3400, 4000), VGet(0, 0, DX_PI_F / 2), 7);
	rock3 = new Rock(loader->GetHandle(Loader::Kind::RockModel3), VGet(1000, -1000, 0), VGet(-1000, 1000, 0), 900.0f, VGet(1700, 6000, 5000), VGet(0, 0, DX_PI_F / 4), 4.0f);
	bgm = new BGM(BGM::BGMKind::ArmEnemyStage);

	//変数初期化
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyStage);
	skyDomeHandle = loader->GetHandle(Loader::Kind::SkyDome);
	stagePosition = VGet(0.0f, 0.0f, 0.0f);
	stageScale = 25.0f;

	//ステージ設定
	MV1SetScale(modelHandle, VGet(stageScale, stageScale, stageScale));
	MV1SetPosition(modelHandle, stagePosition);

	//スカイドーム設定
	MV1SetScale(skyDomeHandle, VGet(SkyDomeScale, SkyDomeScale, SkyDomeScale));
	MV1SetPosition(skyDomeHandle, VGet(1000, 0, -1000));

	//当たり判定
	collisionManager = collisionManager->GetInstance();
	collisionData.tag = ObjectTag::Stage;
	collisionData.stageLeft = StageLeft;
	collisionData.stageRight = StageRight;
	collisionData.stageFront = StageFront;
	collisionData.stageBack = StageBack;

	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemyStage::~ArmEnemyStage()
{
	bgm->StopBGM();
	collisionManager->RemoveCollisionData(&collisionData);
	delete wood;
	delete wall;
	delete rock1;
	delete rock2;
	delete rock3;
	delete bgm;
}

/// <summary>
/// ゲームオーバーシーン初期化
/// </summary>
void ArmEnemyStage::InitializeGameOver()
{
	bgm->StopBGM();
}

/// <summary>
/// ゲームクリア初期化
/// </summary>
void ArmEnemyStage::InitializeGameClear()
{
	bgm->StopBGM();
}

/// <summary>
/// 更新
/// </summary>
void ArmEnemyStage::Update()
{
	bgm->PlayBGM(BGM::BGMKind::ArmEnemyStage);
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemyStage::Draw()
{
	MV1DrawModel(skyDomeHandle);
	MV1DrawModel(modelHandle);
	wall->Draw();
	wood->Draw();
	rock1->Draw();
	rock2->Draw();
	rock3->Draw();
}