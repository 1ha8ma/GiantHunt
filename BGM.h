#pragma once
#include<map>

class BGM
{
public:
	//BGMの種類
	enum class BGMKind :int
	{
		Title,				//タイトル
		GameOver,			//負けシーン
		GameClear,			//勝利シーン
		ArmEnemyStage,		//腕の敵戦
		Ranking,			//ランキング画面
	};

	BGM(BGMKind kind);
	~BGM();

	//BGM再生
	void PlayBGM(BGMKind kind);

	//BGMを止める
	void StopBGM();

private:
	//音量割合
	enum class Ratio :int
	{
		Title = 0,//100
		GameOver = 0,//100
		ArmEnemyStage = 0,//80
		GameClear = 0,//100
		Ranking = 0,//80
	};

	std::map<BGMKind, int> handle;	//ハンドル
	int playingBGM;					//再生中のBGM
};