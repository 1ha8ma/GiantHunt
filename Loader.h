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
		WoodModel,			//木
		ArmEnemyStage,		//腕の敵戦ステージ
		BossEnemyStage,		//ボス戦ステージ

		//2D
		GameOverBackImage,	//ゲームオーバー背景
		TitleBackImage,		//タイトル背景

		//BGM
		ArmEnemyBGM,		//腕の敵戦

		//SE
		MowinDownSE,		//振り下ろし攻撃SE
		NormalAttackSE,		//通常攻撃SE
		SwingSE,			//振りまわりSE

		//エフェクト
		WeakPointEffect,	//弱点
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