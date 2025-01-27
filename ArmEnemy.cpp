#include"DxLib.h"
#include"Loader.h"
#include"Calculation.h"
#include"Camera.h"
#include"EnemyParts.h"
#include"ArmEnemyMoveBase.h"
#include"ArmEnemyIdle.h"
#include"ArmEnemyMowingDown.h"
#include"ArmEnemySwing.h"
#include"ArmEnemyFallDown.h"
#include"ArmEnemyHandUp.h"
#include"ArmEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
ArmEnemy::ArmEnemy()
{
	Loader* loader = loader->GetInstance();
	//モデルロード
	modelHandle = loader->GetHandle(Loader::Kind::ArmEnemyModel);

	//ステータス初期化
	HP = MaxHP;

	//private変数初期化
	calclation = new Calculation();
	position = VGet(2000.0f, -5000.0f, 6550.0f);
	playerRidePlace = RidePlace::None;
	moveChangeflg = false;
	playerRideFlame = 0;
	playerRideflg = false;
	playerRideMoveStartflg = false;

	//描画モデル
	MV1SetScale(modelHandle, VGet(ModelScale, ModelScale, ModelScale));
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI_F / 2, 0.0f));
	MV1SetPosition(modelHandle, position);

	//部位当たり判定
	parts.clear();
	parts.push_back(new EnemyParts(ObjectTag::Upperarm_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm-1, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Upperarm, 600));
	parts.push_back(new EnemyParts(ObjectTag::Forearm_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm - 1, 500));
	parts.push_back(new EnemyParts(ObjectTag::Hand_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Forearm, 300));
	parts.push_back(new EnemyParts(ObjectTag::WeakPoint_E1, modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand - 1, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand - 1, 320));

	move = new ArmEnemyIdle(modelHandle, VGet(0, 0, 0));
	nowMoveKind = MoveKind::Idle;
}

/// <summary>
/// デストラクタ
/// </summary>
ArmEnemy::~ArmEnemy()
{
	for (int i = 0; i < parts.size(); i++)
	{
		delete parts[i];
	}

	parts.clear();
}

/// <summary>
/// 初期化
/// </summary>
void ArmEnemy::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
bool ArmEnemy::Update(VECTOR playerPos,Camera* camera)
{
	//プレイヤーの乗っている関係初期化
	playerRidePlace = RidePlace::None;
	playerRideflg = false;

	//HPが無くなったか
	bool HPoutflg = false;

	for (int i = 0; i < parts.size(); i++)
	{
		if (parts[i]->GetIsPlayerRide())
		{
			playerRideflg = true;
			if (i == 0)
			{
				playerRidePlace = RidePlace::Upperarm;
			}
			else if (i == 1)
			{
				playerRidePlace = RidePlace::Forearm;
			}
			else if (i == 2)
			{
				playerRidePlace = RidePlace::Hand;
			}
		}
	}

	//プレイヤーが乗っていたら
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && playerRideflg)
	{
		playerRideFlame++;

		if (playerRideFlame > PlayerRideMoveStateFlame)
		{
			playerRideFlame = 0;
			playerRideMoveStartflg = true;
		}
	}

	//更新
	for (int i = 0; i < parts.size(); i++)
	{
		HP -= parts[i]->TakeDamage();
		parts[i]->Update();
	}
	if (HP < 0)
	{
		HP = 0;
	}

	//HP確認
	if (HP == 0)
	{
		HPoutflg = true;
	}

	//手をターゲットカメラに設定
	targetCameraPosition = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);
	//動き更新
	moveChangeflg = move->Update(camera);
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->CalculationMoveVec();
	}

	//動きの変更確認
	ChangeMove(playerPos);

	MV1SetPosition(modelHandle, position);

	return HPoutflg;
}

/// <summary>
/// 倒された後の初期化
/// </summary>
void ArmEnemy::InitializeFallDown()
{
	VECTOR prevRotate = move->GetRotate();
	delete move;
	nowMoveKind = MoveKind::FallDown;
	move = new ArmEnemyFallDown(modelHandle);
}

/// <summary>
/// 倒された後の更新
/// </summary>
/// <returns>動きが終わったか</returns>
bool ArmEnemy::UpdateFallDown(Camera* camera)
{
	bool moveEnd = false;
	moveEnd = move->UpdateFallDown(camera);

	//パーツ、エフェクトの更新
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}

	//手をターゲットカメラに設定
	targetCameraPosition = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);

	MV1SetPosition(modelHandle, position);
	return moveEnd;
}

/// <summary>
/// 描画
/// </summary>
void ArmEnemy::Draw()
{
	MV1DrawModel(modelHandle);

	//当たり判定確認用
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}
	//move->Draw();
}

/// <summary>
/// 動きの変更
/// </summary>
/// <param name="playerPos">プレイヤーポジション</param>
void ArmEnemy::ChangeMove(VECTOR playerPos)
{
	VECTOR handpos = MV1GetFramePosition(modelHandle, (int)ArmEnemyMoveBase::ArmEnemyFrameIndex::Hand);
	float handForPlayerDistance = calclation->LengthTwoPoint3D(handpos, playerPos);

	//待機
	if (nowMoveKind == MoveKind::MowingDown && moveChangeflg ||
		nowMoveKind == MoveKind::Swing && moveChangeflg ||
		nowMoveKind == MoveKind::HandUp && moveChangeflg
		)
	{
		//プレイヤーが乗っている時の動きのフラグを初期化
		if (nowMoveKind == MoveKind::Swing || nowMoveKind == MoveKind::HandUp)
		{
			playerRideMoveStartflg = false;
		}
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::Idle;
		move = new ArmEnemyIdle(modelHandle, prevRotate);
	}

	//薙ぎ払い
	if (nowMoveKind == MoveKind::Idle && handForPlayerDistance < 2500 && playerRidePlace == RidePlace::None && playerPos.y < handpos.y)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::MowingDown;
		move = new ArmEnemyMowingDown(modelHandle,prevRotate);
	}

	//振り回し...プレイヤーが上腕か前腕に乗っている場合
	if (nowMoveKind != MoveKind::Swing && nowMoveKind != MoveKind::HandUp && playerRideMoveStartflg && (playerRidePlace == RidePlace::Upperarm || playerRidePlace == RidePlace::Forearm))
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::Swing;
		move = new ArmEnemySwing(modelHandle, prevRotate);
	}

	//腕を上げる...プレイヤーが手に乗っている場合
	if (nowMoveKind != MoveKind::HandUp && nowMoveKind != MoveKind::Swing && playerRideMoveStartflg && playerRidePlace == RidePlace::Hand)
	{
		VECTOR prevRotate = move->GetRotate();
		delete move;
		nowMoveKind = MoveKind::HandUp;
		move = new ArmEnemyHandUp(modelHandle, prevRotate);
	}
}