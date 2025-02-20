#include<fstream>
#include"DxLib.h"
#include"nlohmann/json.hpp"
#include"Loader.h"
#include"Camera.h"
#include"Input.h"
#include"CollisionManager.h"
#include"Calculation.h"
#include"PlayerRun.h"
#include"PlayerJump.h"
#include"PlayerNormalAttack.h"
#include"PlayerClimb.h"
#include"PlayerSquat.h"
#include"PlayerPiercing.h"
#include"PlayerFallDown.h"
#include"PlayerIdle.h"
#include"PlayerFalling.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::PlayerModel);

	InitializeStartScene();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	collisionManager->RemoveCollisionData(&bodyCollisionData);
	collisionManager->RemoveCollisionData(&footCollisionData);
	delete input;
	delete nowstate;
}

/// <summary>
/// スタートシーン初期化
/// </summary>
void Player::InitializeStartScene()
{
	//ファイル読み込み
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	nowstate = new PlayerRun(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	positionDistanceGround = jsonData["PositionDistanceGround"];
	position = VGet(jsonData["InitPositionX"], positionDistanceGround, jsonData["InitPositionZ"]);
	drawPosition = position;
	angle = 0.0f;
}

/// <summary>
/// ゲームシーン初期化
/// </summary>
void Player::InitializeGame()
{
	//インスタンス化
	nowstate = new PlayerIdle(modelHandle, VGet(0.0f, 0.0f, 0.0f));
	input = new Input();
	calculation = new Calculation();

	//ファイル読み込み
	using Json = nlohmann::json;
	Json jsonData;
	std::ifstream ifs("Data/PlayerData.json");
	if (ifs)
	{
		ifs >> jsonData;
	}

	//変数初期化
	//ステータス
	MaxHP = jsonData["PlayerMaxHP"];
	HP = MaxHP;
	MaxGripPoint = jsonData["MaxGripPoint"];
	gripPoint = MaxGripPoint;
	//入力
	canInputX = false;
	//モデル関係
	drawPosition = position;
	//あたり判定
	positionDistanceGround = jsonData["PositionDistanceGround"];
	position = VGet(jsonData["InitPositionX"], positionDistanceGround, jsonData["InitPositionZ"]);
	WholeBodyCapsuleRadius = jsonData["WholeBodyCapsuleRadius"];
	WholeBodyCapsuleHalfLength = jsonData["WholeBodyCapsuleHalfLength"];
	FootCapsuleRadius = jsonData["FootCapsuleRadius"];

	//移動関係
	angle = 0.0f;
	changeAngleSpeed = jsonData["ChangeAngleSpeed"];
	jumpAfterLeaveFoot = false;
	onGround = true;
	onFootObject = false;
	isCatch = false;
	runPlace = PlayerStateProcessBase::RunPlaceKind::ground;
	//動き関係
	nowstateKind = State::Run;
	changeStateflg = false;
	//落下関係
	fallSpeed = 0.0f;
	fallFrame = 0;
	fallDamage = 0;
	FallDamageIncrease = jsonData["FallDamageIncrease"];
	Gravity = jsonData["Gravity"];
	FallDamageCameraShakingPower = jsonData["FallDamageCameraShakingPower"];
	FallDamageCameraShakingDirChangeflame = jsonData["FallDamageCameraShakingDirChangeflame"];
	FallDamageCameraShakingPlayflame = jsonData["FallDamageCameraShakingPlayflame"];
	FallDamageJoypadVibPower = jsonData["FallDamageJoypadVibPower"];
	FallDamageJoypadVibPlayflame = jsonData["FallDamageJoypadVibPlayflame"];
	//突き刺し攻撃
	cameraZoom = 0.0f;
	piercingArmRotateZ = 0.0f;
	onPiercingGauge = false;
	//登り
	putCloseVec = VGet(0, 0, 0);
	MinusGripPoint = jsonData["MinusGripPoint"];
	//その他
	gameOverflg = false;

	//当たり判定
	collisionManager = collisionManager->GetInstance();
	//衝突後の処理を渡す
	bodyCollisionData.HitProcess = std::bind(&Player::BodyOnHitObject, this, std::placeholders::_1);
	bodyCollisionData.WallHitProcess = std::bind(&Player::WallHitProcess, this, std::placeholders::_1);
	footCollisionData.HitProcess = std::bind(&Player::FootOnHitObject, this, std::placeholders::_1);
	//当たり判定に必要なデータを渡す
	collisionManager->AddCollisionData(&bodyCollisionData);
	collisionManager->AddCollisionData(&footCollisionData);

	//ポジション反映
	MV1SetPosition(modelHandle, drawPosition);
}

/// <summary>
/// 更新
/// </summary>
/// <param name="camera">カメラ</param>
/// <returns>ゲームオーバー</returns>
bool Player::UpdateGame(Camera* camera)
{
	//入力
	inputstate = input->GetInputState();
	stickstate = input->GetStickInput();

	//入力によってステート変更
	ChangeState();

	//ステート更新に必要な情報を渡す
	if (nowstateKind == State::Climb)
	{
		hitObjectData = collisionManager->GetCollisionData(hitObjectDataPointer);
		float length = Segment_Segment_MinLength(wholebodyCapStart, wholebodyCapEnd, hitObjectData.startPosition, hitObjectData.endPosition);
		float distance = (WholeBodyCapsuleRadius + hitObjectData.radius) - length;
		//衝突したものとプレイヤーの向きのベクトルを取る
		VECTOR dir = VSub(hitObjectData.position,position);
		//近づける
		dir = VNorm(dir);
		putCloseVec = VScale(dir, distance);
	}
	MoveUseDataSet();
	//ステート更新
	changeStateflg = nowstate->Update(moveUseData, *camera, hitObjectData);
	rotateMatrix = nowstate->GetRotateMatrix();

	//移動
	moveVec = nowstate->GetmoveVec();
	//落下速度追加
	moveVec = VSub(moveVec, VGet(0.0f, fallSpeed, 0.0f));
	//ポジション反映
	position = VAdd(position, moveVec);
	//足がついているか確認
	CheckOnGround(camera);

	//角度更新
	targetLookDirection = nowstate->GettargetLookDirection();
	UpdateAngle();

	//描画位置修正
	CorrectionDrawPosition();

	//連続入力防止
	PreventionContinuousInput();

	//握力
	if (nowstateKind == State::Climb)
	{
		gripPoint -= MinusGripPoint;
	}
	else
	{
		gripPoint += MinusGripPoint;
		if (gripPoint > MaxGripPoint)
		{
			gripPoint = MaxGripPoint;
		}
	}

	//ゲームオーバー確認
	if (HP <= 0)
	{
		gameOverflg = true;
	}

	//突き刺し攻撃時
	if (nowstateKind == State::Piercing)
	{
		onPiercingGauge = true;
		cameraZoom = nowstate->GetCameraZoom();
		piercingArmRotateZ = nowstate->GetArmRotateZ();
	}
	else
	{
		onPiercingGauge = false;
		cameraZoom = 0.0f;
	}
	//ジャンプ時
	if (nowstateKind == State::Jump && !jumpAfterLeaveFoot && !onFootObject)
	{
		jumpAfterLeaveFoot = true;
	}

	//ポジション等更新
	UpdateCapsule();
	UpdateCollisionData();

	//変数初期化
	isCatch = false;
	onFootObject = false;
	putCloseVec = VGet(0, 0, 0);

	return gameOverflg;
}

/// <summary>
/// ゲームオーバーシーン初期化
/// </summary>
void Player::InitializeGameOver()
{
	delete nowstate;
	nowstateKind = State::FallDown;
	nowstate = new PlayerFallDown(modelHandle);
}

/// <summary>
/// ゲームオーバーシーン更新
/// </summary>
void Player::UpdateGameOver()
{
	nowstate->UpdateGameOver();
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1SetPosition(modelHandle, drawPosition);
	MV1DrawModel(modelHandle);

	//確認用
	DrawCapsule3D(bodyCollisionData.startPosition, bodyCollisionData.endPosition, WholeBodyCapsuleRadius, 8, GetColor(220, 20, 60),GetColor(220,20,60), FALSE);
	//DrawCapsule3D(footCapStart, footCapEnd, FootCapsuleRadius, 8, GetColor(220, 20, 60), GetColor(220, 20, 60), FALSE);
	//nowstate->Draw();
}

/// <summary>
/// 衝突時の処理
/// </summary>
/// <param name="hitObjectData">衝突したオブジェクト</param>
void Player::BodyOnHitObject(CollisionData* hitObjectData)
{
	//衝突したオブジェクトごとに処理を変更
	//敵の攻撃
	if (hitObjectData->tag == ObjectTag::EnemyAttack)
	{
		//HP減少
		HP -= hitObjectData->attackPower;

		if (HP < 0)
		{
			HP = 0;
		}
	}

	//カプセル
	if (hitObjectData->tag == ObjectTag::StageObject ||
		hitObjectData->tag == ObjectTag::EnemyParts)
	{
		//押し戻し
		if (nowstateKind != State::Climb)
		{
			CollisionPushBack(bodyCollisionData, hitObjectData);
		}
		//isCatch = true;
		runPlace = PlayerStateProcessBase::RunPlaceKind::capsule;
	}
}

/// <summary>
/// オブジェクト衝突時の処理(足)
/// </summary>
/// <param name="hitObjectData">衝突したオブジェクト</param>
void Player::FootOnHitObject(CollisionData* hitObjectData)
{
	if (hitObjectData->tag == ObjectTag::StageObject ||		//木
		hitObjectData->tag == ObjectTag::EnemyParts)	//腕の敵
	{
		runPlace = PlayerStateProcessBase::RunPlaceKind::capsule;
	}
}

/// <summary>
/// 角度更新
/// </summary>
void Player::UpdateAngle()
{
	//移動方向にモデルの方向を近づける
	float targetAngle;		//目標の角度
	float difference;		//目標角度と現在の角度の差

	//目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));

	//目標の角度と現在の角度との差を割り出す
	//最初は引き算
	difference = targetAngle - angle;

	//ある方向からある方向の差が180度以上になることはないので差が180度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//角度の差を0に近づける
	if (difference > 0.0f)//差がマイナスの場合
	{
		difference -= changeAngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//差がプラスの場合
	{
		difference += changeAngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//モデルの角度を更新
	angle = targetAngle - difference;

	//反映

	//登りモーションの時は反転
	if (nowstateKind == State::Climb)
	{
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle, 0.0f));
		//MV1SetMatrix(modelHandle, rotateMatrix);
	}
	else
	{
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));
	}
}

/// <summary>
/// 角度更新
/// </summary>
//void Player::UpdateAngle()
//{
//	//目標の方向ベクトルから角度値を算出する
//	float targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));
//
//	MV1SetMatrix(modelHandle, rotateMatrix);
//}

/// <summary>
/// ステート変更
/// </summary>
void Player::ChangeState()
{
	//待機
	if (nowstateKind == State::Run && (stickstate.X == 0.0f && stickstate.Y == 0.0f) ||
		nowstateKind == State::Jump && onGround ||
		nowstateKind == State::NormalAttack && changeStateflg ||
		nowstateKind == State::Climb && changeStateflg || nowstateKind == State::Climb && gripPoint <= 0 ||
		nowstateKind == State::Squat && changeStateflg ||
		nowstateKind == State::Piercing && changeStateflg ||
		nowstateKind == State::Falling && onGround)
	{
		delete nowstate;
		nowstateKind = State::Idle;
		nowstate = new PlayerIdle(modelHandle, targetLookDirection);
	}

	//走る
	if (nowstateKind != State::Run && nowstateKind != State::Climb && nowstateKind != State::NormalAttack && nowstateKind != State::Piercing && nowstateKind != State::Squat && onGround && (stickstate.X != 0.0f || stickstate.Y != 0.0f))
	{
		delete nowstate;
		nowstateKind = State::Run;
		nowstate = new PlayerRun(modelHandle, targetLookDirection);
	}

	//ジャンプ
	if (nowstateKind != State::Jump && nowstateKind != State::NormalAttack && (Input::InputNumber::AButton & inputstate) == Input::InputNumber::AButton)
	{
		delete nowstate;
		onGround = false;
		jumpAfterLeaveFoot = false;
		nowstateKind = State::Jump;
		nowstate = new PlayerJump(modelHandle, moveVec);
	}

	//突き刺し攻撃
	if (nowstateKind == State::Squat && canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::Piercing;
		nowstate = new PlayerPiercing(modelHandle, targetLookDirection);
	}

	//通常攻撃　(突き刺し攻撃の後に判定しないと一度通常攻撃に入ってしまう)
	if (nowstateKind != State::NormalAttack && nowstateKind != State::Piercing && nowstateKind != State::Jump && nowstateKind != State::Squat && canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		delete nowstate;
		nowstateKind = State::NormalAttack;
		nowstate = new PlayerNormalAttack(modelHandle, targetLookDirection);
	}

	//掴まり
	if (nowstateKind != State::Climb && isCatch && !onGround && (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1 && gripPoint > 20)
	{
		delete nowstate;
		nowstateKind = State::Climb;
		nowstate = new PlayerClimb(modelHandle, targetLookDirection);
	}

	//しゃがみ
	if (onGround && nowstateKind != State::Piercing && nowstateKind != State::Squat && nowstateKind != State::Climb && !isCatch && (Input::InputNumber::R1 & inputstate) == Input::InputNumber::R1)
	{
		delete nowstate;
		nowstateKind = State::Squat;
		nowstate = new PlayerSquat(modelHandle, targetLookDirection);
	}

	//落下(一定フレーム以上落ちている場合に移行)
	if (fallFrame > 25 && !onGround && nowstateKind != State::Falling && nowstateKind != State::Jump && nowstateKind != State::Climb)
	{
		delete nowstate;
		nowstateKind = State::Falling;
		nowstate = new PlayerFalling(modelHandle, targetLookDirection);
	}
}

/// <summary>
/// 足が着いているか確認
/// </summary>
/// <param name="camera">カメラ</param>
void Player::CheckOnGround(Camera* camera)
{
	//着地したとき
	if ((nowstateKind == State::Jump && jumpAfterLeaveFoot && (!onGround && position.y - positionDistanceGround < 0.0f || !onGround && onFootObject)) ||
		nowstateKind != State::Jump && (!onGround && position.y - positionDistanceGround < 0.0f || !onGround && onFootObject))
	{
		onGround = true;
		moveVec.y = 0.0f;

		//一定時間落下していたら落下ダメージ
		if (fallFrame >= 100)
		{
			HP -= fallDamage;
			//カメラ振動
			camera->PlayShakingVertical(FallDamageCameraShakingPower, FallDamageCameraShakingDirChangeflame, FallDamageCameraShakingPlayflame);
			//振動
			StartJoypadVibration(DX_INPUT_PAD1, FallDamageJoypadVibPower, FallDamageJoypadVibPlayflame, -1);
		}
	}

	//ついていなければ
	if (position.y - positionDistanceGround > 0.0f && !onFootObject)
	{
		onGround = false;
		runPlace = PlayerStateProcessBase::RunPlaceKind::air;
		fallDamage += FallDamageIncrease;
	}

	//足がついていなければ落下
	if (!onGround && nowstateKind != State::Climb)
	{
		fallFrame++;
		fallSpeed += Gravity;
	}
	else
	{
		fallFrame = 0;
		fallSpeed = 0.0f;
		fallDamage = 0;
	}

	//下まで行かないように
	if (position.y - positionDistanceGround < 0.0f)
	{
		runPlace = PlayerStateProcessBase::RunPlaceKind::ground;
		position.y = 0.0f + positionDistanceGround;
	}
}

/// <summary>
/// カプセル更新
/// </summary>
void Player::UpdateCapsule()
{
	//全身
	wholebodyCapStart = VAdd(position, VGet(0.0f, WholeBodyCapsuleHalfLength, 0.0f));
	wholebodyCapEnd = VAdd(position, VGet(0.0f, -WholeBodyCapsuleHalfLength, 0.0f));
	
	//中心
	centerPosition = VAdd(wholebodyCapStart, wholebodyCapEnd);
	centerPosition = VScale(centerPosition, 0.5);

	//足
	footCapStart = VAdd(position, VGet(0.0f, 10.0f, 0.0f));
	footCapEnd = VAdd(position, VGet(0.0f, 10.0f, 0.0f));
}

/// <summary>
/// 当たり判定情報更新
/// </summary>
void Player::UpdateCollisionData()
{
	//全身
	bodyCollisionData.tag = ObjectTag::PlayerWholeBody;
	bodyCollisionData.position = position;
	bodyCollisionData.startPosition = wholebodyCapStart;
	bodyCollisionData.endPosition = wholebodyCapEnd;
	bodyCollisionData.radius = WholeBodyCapsuleRadius;
	bodyCollisionData.isCollisionActive = true;

	//足
	footCollisionData.tag = ObjectTag::PlayerFoot;
	footCollisionData.position = position;
	footCollisionData.startPosition = footCapStart;
	footCollisionData.endPosition = footCapEnd;
	footCollisionData.radius = FootCapsuleRadius;
	footCollisionData.isCollisionActive = true;
}

/// <summary>
/// 描画位置修正(アニメーションの種類によっては座標がずれていたため)
/// </summary>
void Player::CorrectionDrawPosition()
{
	//基本
	drawPosition = position;
	drawPosition.y -= positionDistanceGround;

	//ジャンプ
	if (nowstateKind == State::Jump)
	{
		drawPosition.y -= 60.0f;
	}

	//登り
	if (nowstateKind == State::Climb)
	{
		drawPosition.y -= 90.0f;
		drawPosition.x -= cos(angle) * 100.0f;
		drawPosition.z -= sin(-angle) * 100.0f;
	}
}

/// <summary>
/// 衝突後の押し戻し
/// </summary>
void Player::CollisionPushBack(CollisionData partsData, CollisionData *hitObjectData)
{
	////半径の合計
	//float radiusSum = hitObjectData.radius + partsData.radius;

	////ベクトルのサイズを計算
	////2つの線分の最短距離を求める
	//float length = Segment_Segment_MinLength(partsData.startPosition, partsData.endPosition, hitObjectData.startPosition, hitObjectData.endPosition);
	//float distance = radiusSum - length;

	////衝突したものとプレイヤーの向きのベクトルを取る
	//VECTOR dir = VSub(hitObjectData.position, position);

	////押し戻し
	//dir = VNorm(dir);
	//VECTOR pushBackVec = VScale(dir, -distance);

	//position = VAdd(position, pushBackVec);

	//if (position.y < 0.0f)
	//{
	//	position.y = 0.0f;
	//}

	for (int i = 0; i < hitObjectData->meshData.polygonList.PolygonNum; i++)
	{
		VECTOR vertex0 = hitObjectData->meshData.polygonList.Vertexs[hitObjectData->meshData.polygonList.Polygons[i].VIndex[0]].Position;
		VECTOR vertex1 = hitObjectData->meshData.polygonList.Vertexs[hitObjectData->meshData.polygonList.Polygons[i].VIndex[1]].Position;
		VECTOR vertex2 = hitObjectData->meshData.polygonList.Vertexs[hitObjectData->meshData.polygonList.Polygons[i].VIndex[2]].Position;

		//カプセルと三角形の当たり判定
		bool bodyResult = HitCheck_Capsule_Triangle(wholebodyCapStart, wholebodyCapEnd, WholeBodyCapsuleRadius, vertex0, vertex1, vertex2);
		bool footResult = HitCheck_Capsule_Triangle(footCapStart, footCapEnd, FootCapsuleRadius, vertex0, vertex1, vertex2);

		if (footResult)
		{
			onFootObject = true;
		}

		if (bodyResult)
		{
			//データコピー
			hitObjectDataPointer = hitObjectData;
			this->hitObjectData = *hitObjectData;

			//掴めるようにする
			isCatch = true;

			VECTOR vec01 = VSub(vertex1, vertex0);	//0→1
			VECTOR vec02 = VSub(vertex2, vertex0);	//0→2
			VECTOR normVec = VCross(vec01, vec02);	//法線ベクトル
			normVec = VNorm(normVec);

			//HACK:moveVecの長さを法線の方向に戻しているためステージからの押し返しに反応しないしガタガタする
			float length = VSize(moveVec);
			//距離を取る
			//length = Segment_Triangle_MinLength(wholebodyCapStart, wholebodyCapEnd, vertex0, vertex1, vertex2);
			
			VECTOR pushBackVec = VScale(normVec, length);
			position = VAdd(position, pushBackVec);
			
			break;
		}
	}
}

/// <summary>
/// 壁衝突時の処理
/// </summary>
/// <param name="sinkIntoDepth">めり込み量</param>
void Player::WallHitProcess(VECTOR sinkIntoDepth)
{
	position = VAdd(position, sinkIntoDepth);
}

/// <summary>
/// 動きに使うデータのセット
/// </summary>
void Player::MoveUseDataSet()
{
	moveUseData.inputState = inputstate;
	moveUseData.stickState = stickstate;
	moveUseData.position = position;
	moveUseData.capsuleStart = wholebodyCapStart;
	moveUseData.capsuleEnd = wholebodyCapEnd;
	moveUseData.centerPosition = centerPosition;
	moveUseData.capsuleRadius = WholeBodyCapsuleRadius;
	moveUseData.angle = angle;
	moveUseData.runPlace = runPlace;
	moveUseData.onFoot = onFootObject;
	moveUseData.putCloseVec = putCloseVec;
	moveUseData.lookDirection = targetLookDirection;
}

/// <summary>
/// 連続入力防止
/// </summary>
void Player::PreventionContinuousInput()
{
	//連続入力防止
	if (canInputX && (Input::InputNumber::XButton & inputstate) == Input::InputNumber::XButton)
	{
		canInputX = false;
	}
	if (!canInputX && (Input::InputNumber::XButton & inputstate) != Input::InputNumber::XButton)
	{
		canInputX = true;
	}
}

/// <summary>
/// カメラに渡すためのポジション
/// </summary>
/// <returns>ポジション</returns>
VECTOR Player::GetPositionUseCamera()
{
	VECTOR returnVec;

	returnVec = position;
	returnVec.y -= positionDistanceGround;

	return returnVec;
}