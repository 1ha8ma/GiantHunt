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

	//�w��̃G�t�F�N�g���Đ������m�F
	bool IsPlayEffect(EffectKind kind);

private:
	std::vector<EffectKind> playingEffectKind;		//�Đ����̃G�t�F�N�g�̎��
	std::vector<int> playingEffectHandle;	//�Đ����̃G�t�F�N�g�n���h��
	std::vector<VECTOR> playingEffectScale;	//�G�t�F�N�g�T�C�Y
	std::map<EffectKind, int> effectHandle;	//�G�t�F�N�g�n���h��

	//�n���h��
	int weakPointHandle;	//��_
};