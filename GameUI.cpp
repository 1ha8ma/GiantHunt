#include"DxLib.h"
#include"GameUI.h"

GameUI::GameUI(int enemyHP, int playerHP, int playerGrip)
{
	//現在のステータス初期化
	this->enemyHP = enemyHP;
	this->playerHP = playerHP;
	this->playerGrip = playerGrip;

	//開始時ステータス
	startEnemyHP = enemyHP;
	startPlayerHP = playerHP;
	startPlayerGrip = playerGrip;
}

/// <summary>
/// デストラクタ
/// </summary>
GameUI::~GameUI()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="enemyHP">敵HP</param>
/// <param name="playerHP">プレイヤーHP</param>
/// <param name="playerGrip">プレイヤー握力</param>
void GameUI::Update(int enemyHP, int playerHP, int playerGrip)
{
	//ステータス取得
	this->enemyHP = enemyHP;
	this->playerHP = playerHP;
	this->playerGrip = playerGrip;

	//割合計算
	enemyHPPer = this->enemyHP / startEnemyHP;
	playerHPPer = this->playerHP / startPlayerHP;
	playerGripPer = this->playerGrip / startPlayerGrip;
}

/// <summary>
/// 描画
/// </summary>
void GameUI::Draw()
{
	//敵HP
	DrawBox(50, 38, 50 + EnemyHPLength, 57, GetColor(75, 75, 75),TRUE);
	DrawBox(50, 40, 50 + EnemyHPLength * enemyHPPer, 55, GetColor(0, 191, 255), TRUE);
	//プレイヤーHP
	DrawBox(1200, 798, 1200+ PlayerHPLength, 827, GetColor(75, 75, 75), TRUE);
	DrawBox(1200, 800, 1200 + PlayerHPLength*playerHPPer, 825, GetColor(220, 20, 60), TRUE);
	//プレイヤー握力
	DrawCircle(1400, 700, PlayerGripSize+2, GetColor(75, 75, 75), TRUE);
	DrawCircle(1400, 700, PlayerGripSize * playerGripPer, GetColor(240, 230, 140), TRUE);
}