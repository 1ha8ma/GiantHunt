#pragma once
#include<map>

class SoundEffect
{
public:
	//SEの種類
	enum class SEKind :int
	{
		NormalAttack,		//通常攻撃
		MowinDownAttack,	//振り下ろし攻撃
		Swing,				//振り回し
		HitWeakPoint,		//弱点に当たった時
		Jump,				//ジャンプ
	};

	SoundEffect();
	~SoundEffect();

	//SE再生
	void PlaySE(SEKind kind);
	//特定のSEを終了
	void StopSE(SEKind kind);

private:
	//音量割合
	enum class Ratio :int
	{
		NormalAttack = 80,
		MowingAttack = 100,
		Swing = 100,
		HitWeakPoint = 100,
	};

	std::map<SEKind, int> handle;	//ハンドル
};