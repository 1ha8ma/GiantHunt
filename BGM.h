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
		ArmEnemyStage,		//腕の敵戦
		Win,				//勝利シーン
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
		Title = 100,
		GameOver = 100,
		ArmEnemyStage = 80,
	};

	std::map<BGMKind, int> handle;	//ハンドル
	int playingBGM;					//再生中のBGM
};