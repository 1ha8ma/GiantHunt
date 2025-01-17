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
	const float PlayerGripSize = 60.0f;		//描画プレイヤー握力の大きさ

	float startEnemyHP;			//開始時敵HP
	float startPlayerHP;		//開始時プレイヤーHP
	float startPlayerGrip;		//開始時プレイヤー握力

	float enemyHP;				//現在の敵HP
	float playerHP;				//現在のプレイヤーHP
	float playerGrip;			//現在のプレイヤー握力

	float enemyHPPer;			//敵HP割合
	float playerHPPer;			//プレイヤーHP割合
	float playerGripPer;		//プレイヤー握力割合
};