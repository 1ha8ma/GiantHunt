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
	const float ModelScale = 40.0f;		//モデルスケール
	const int MaxHP = 2000;				//最大HP

	std::vector<EnemyParts*> parts;		//当たり判定パーツ
};
