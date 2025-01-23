#pragma once

class GameUI
{
public:
	GameUI(int enemyHP,int playerHP,int playerGrip);
	~GameUI();

	void Update(int enemyHP, int playerHP, int playerGrip);
	void Draw();

private:
	const float PlayerHPLength = 300.0f;	//描画プレイヤーHPゲージの長さ
	const float EnemyHPLength = 500.0f;		//描画敵HPゲージの長さ
	const float PlayerGripSize = 50.0f;		//描画プレイヤー握力の大きさ

	float startEnemyHP;			//開始時敵HP
	float startPlayerHP;		//開始時プレイヤーHP
	float startPlayerGrip;		//開始時プレイヤー握力

	float prevEnemyHP;			//1フレーム前の敵のHP
	float prevPlayerHP;			//1フレーム前のプレイヤーのHP

	float enemyHP;				//現在の敵HP
	float playerHP;				//現在のプレイヤーHP
	float playerGrip;			//現在のプレイヤー握力

	float enemyHPPer;			//敵HP割合
	float playerHPPer;			//プレイヤーHP割合
	float playerGripPer;		//プレイヤー握力割合

	bool enemyTakeDamage;		//敵がダメージを受けた
	bool playerTakeDamage;		//プレイヤーがダメージを受けた
	int enemyTakeDamageFlame;	//敵がダメージを受けた後のHPバー演出のフレーム
	int playerTakeDamageFlame;	//プレイヤーがダメージを受けた後のHPバー演出のフレーム

	int enemyColorR, enemyColorG, enemyColorB;
	int playerColorR, playerColorG, playerColorB;
};