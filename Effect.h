#pragma once
#include<vector>
#include<map>

class Effect
{
public:
	enum class EffectKind :int
	{
		WeakPoint,
	};

	Effect();
	~Effect();

	void Initialize();
	void PlayEffect(EffectKind kind, VECTOR playPosition, VECTOR initScale, VECTOR rotate, float playSpeed);
	void Update(VECTOR playPosition,VECTOR rotate);
	void Draw();

	//指定のエフェクトが再生中か確認
	bool IsPlayEffect(EffectKind kind);

private:
	std::vector<EffectKind> playingEffectKind;		//再生中のエフェクトの種類
	std::vector<int> playingEffectHandle;	//再生中のエフェクトハンドル
	std::vector<VECTOR> playingEffectScale;	//エフェクトサイズ
	std::map<EffectKind, int> effectHandle;	//エフェクトハンドル

	//ハンドル
	int weakPointHandle;	//弱点
};