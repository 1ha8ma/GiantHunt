#pragma once
#include<vector>
#include"EnemyBase.h"

class EnemyParts;

class Enemy2 :public EnemyBase
{
public:
	Enemy2();
	~Enemy2()override;

	//初期化
	void Initialize()override;
	//更新
	bool Update(VECTOR playerPos, Camera* camera)override;

	//倒された後の初期化
	void InitializeFallDown()override;
	//倒された後の更新
	bool UpdateFallDown(Camera* camera)override;

	//描画
	void Draw()override;

private:
	//パーツの名前
	enum class PartsName :int
	{
		Head,			//頭
		Body,			//胴体
		LeftUpperArm,	//左上腕
		LeftForeArm,	//左前腕
		LeftHand,		//左手
		LeftSowrd,		//左手の剣の部分
		RightUpperArm,	//右上腕
		RightForeArm,	//右前腕
		RightHand,		//右手
		LeftThigh,		//左太もも
		LeftCalf,		//左ふくらはぎ
		LeftFoot,		//左足
		RightThigh,		//右ふともも
		RightCalf,		//右ふくらはぎ
		RightFoot,		//右足
		WeakPoint,		//弱点
	};

	/// <summary>
	/// 動きの種類
	/// </summary>
	enum class MoveKind :int
	{
		Walk,			//歩く

	};

	const float ModelScale = 40.0f;		//モデルスケール
	const int MaxHP = 2000;				//最大HP

	std::vector<EnemyParts*> parts;		//当たり判定パーツ
};
