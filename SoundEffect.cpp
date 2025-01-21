#include"DxLib.h"
#include"Loader.h"
#include"SoundEffect.h"

/// <summary>
/// コンストラクタ
/// </summary>
SoundEffect::SoundEffect()
{
	Loader* loader = loader->GetInstance();

	//ハンドルロード・音量調整
	handle[SEKind::NormalAttack] = loader->GetHandle(Loader::Kind::NormalAttackSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::NormalAttack / 100, handle[SEKind::NormalAttack]);
	handle[SEKind::MowinDownAttack] = loader->GetHandle(Loader::Kind::MowinDownSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::MowingAttack / 100, handle[SEKind::MowinDownAttack]);
	handle[SEKind::Swing] = loader->GetHandle(Loader::Kind::SwingSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::Swing / 100, handle[SEKind::Swing]);
	handle[SEKind::HitWeakPoint] = loader->GetHandle(Loader::Kind::HitWeakPointSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::HitWeakPoint / 100, handle[SEKind::HitWeakPoint]);
}

/// <summary>
/// デストラクタ
/// </summary>
SoundEffect::~SoundEffect()
{

}

/// <summary>
/// SE再生
/// </summary>
/// <param name="kind">SEの種類</param>
void SoundEffect::PlaySE(SEKind kind)
{
	PlaySoundMem(handle[kind], DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// 特定のSE終了
/// </summary>
/// <param name="kind"></param>
void SoundEffect::StopSE(SEKind kind)
{
	if (CheckSoundMem(handle[kind]))
	{
		StopSoundMem(handle[kind]);
	}
}