#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//インスタンスゲット

	enum Kind
	{
		//3D
		PlayerModel,			//プレイヤー
		ArmEnemyModel,			//腕の敵
		WallModel,				//壁
		BossEnemyModel,			//ボス
		WoodModel,				//木
		ArmEnemyStage,			//腕の敵戦ステージ
		BossEnemyStage,			//ボス戦ステージ

		//2D
		GameOverBackImage,		//ゲームオーバー背景
		TitleBackImage,			//タイトル背景
		RankingArmEnemyImage,	//ランキング画面の腕の敵背景
		ClearTextBackImage,		//クリア画面のテキスト背景

		//BGM
		TitleBGM,				//タイトルBGM
		GameOverBGM,			//ゲームオーバーBGM
		ArmEnemyBGM,			//腕の敵戦
		GameClearBGM,			//ゲームクリアBGM
		RankingBGM,				//ランキング画面BGM

		//SE
		MowinDownSE,			//振り下ろし攻撃SE
		NormalAttackSE,			//通常攻撃SE
		SwingSE,				//振りまわりSE
		HitWeakPointSE,			//弱点ヒットSE
		CrickSE,				//決定SE
		CursorMoveSE,			//カーソル移動SE

		//エフェクト
		WeakPointEffect,		//弱点
		HitWeakPointEffect,		//弱点ヒットエフェクト
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