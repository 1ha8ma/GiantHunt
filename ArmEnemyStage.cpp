#include"DxLib.h"
#include"Loader.h"
#include"CollisionManager.h"
#include"BGM.h"
#include"Wood.h"
#include"Wall.h"
#include"ArmEnemyStage.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemyStage::ArmEnemyStage()
{
	//インスタンス化
	wood = new Wood();
	wall = new Wall();
	bgm = new BGM(BGM::BGMKind::ArmEnemyStage);
	Loader* loader = loader->GetInstance();

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
}