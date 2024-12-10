#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//インスタンスゲット

	enum Kind
	{
		//3D
		PlayerModel,        //プレイヤー
		ArmEnemyModel,		//腕の敵
		WallModel,			//壁
		BossEnemyModel,		//ボス
		ArmEnemyStage,		//腕の敵戦ステージ
		BossEnemyStage,		//ボス戦ステージ

		//2D

		//音

		//エフェクト
	};

	//ハンドルゲット
	int GetHandle(Kind kind) { return handle[kind]; }
	//ロード
	void Load();

private:
	//インスタンス
	static Loader* loader;

	//ハンドルマップ
	std::map<Kind, int> handle;
};