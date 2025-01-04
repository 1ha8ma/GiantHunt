#include"DxLib.h"
#include"CollisionManager.h"
#include"EnemyParts.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag">オブジェクトタグ</param>
/// <param name="modelHandle">モデルハンドル</param>
/// <param name="frameIndex">フレーム番号</param>
/// <param name="capsuleLength">カプセルの長さ</param>
/// <param name="capsuleRadius">カプセル半径</param>
/// <param name="frameVec">フレームの座標からの向き</param>
EnemyParts::EnemyParts(ObjectTag tag, int modelHandle, int frameIndex, float capsuleLength, float capsuleRadius,VECTOR frameVec)
{
	this->modelHandle = modelHandle;
	//タグ設定
	this->tag = tag;
	//ボーンのポジション取得
	this->frameIndex = frameIndex;
	framePosition = MV1GetFramePosition(modelHandle, frameIndex);
	initFramePosition = framePosition;

	//フレームの向きをコピー
	this->frameVec = frameVec;
	
	//カプセル設定
	this->capsuleRadius = capsuleRadius;
	this->capsuleLength = capsuleLength;
	capsuleStart = VScale(frameVec, capsuleLength);
	capsuleStart = VAdd(capsuleStart, framePosition);
	capsuleEnd = VScale(frameVec, -capsuleLength);
	capsuleEnd = VAdd(capsuleEnd, framePosition);
	
	collisionManager = collisionManager->GetInstance();

	//private変数初期化
	isPlayerRide = false;

	//当たり判定情報追加
	collisionData.HitProcess = std::bind(&EnemyParts::OnHitObject, this, std::placeholders::_1);
	UpdateCollisionData();
	collisionManager->AddCollisionData(&collisionData);
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyParts::~EnemyParts()
{

}

/// <summary>
/// 初期化
/// </summary>
void EnemyParts::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void EnemyParts::Update()
{
	//ボーンのベクトル取得
	framePosition = MV1GetFramePosition(modelHandle, frameIndex);

	//カプセル設定
	capsuleStart = VScale(frameVec, capsuleLength);
	capsuleStart = VAdd(capsuleStart, framePosition);
	capsuleEnd = VScale(frameVec, -capsuleLength);
	capsuleEnd = VAdd(capsuleEnd, framePosition);

	//当たり判定情報更新
	UpdateCollisionData();

	isPlayerRide = false;
}

/// <summary>
/// 描画(当たり判定確認用)
/// </summary>
void EnemyParts::Draw()
{
	DrawCapsule3D(capsuleStart, capsuleEnd, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);
	//DrawSphere3D(framePosition, capsuleRadius, 8, GetColor(102, 0, 255), GetColor(102, 0, 255), false);//ポジションの点
}

/// <summary>
/// 衝突後の処理
/// </summary>
/// <param name="hitObjectData">衝突したオブジェクト</param>
void EnemyParts::OnHitObject(CollisionData hitObjectData)
{
	//プレイヤーが乗っている時の処理
	if (hitObjectData.tag == ObjectTag::Player)
	{
		isPlayerRide = true;
	}
}

/// <summary>
/// 当たり判定更新
/// </summary>
void EnemyParts::UpdateCollisionData()
{
	collisionData.tag = tag;
	collisionData.startPosition = capsuleStart;
	collisionData.endPosition = capsuleEnd;
	collisionData.radius = capsuleRadius;
	collisionData.attackPower = 0;
	collisionData.isCollisionActive = true;
}