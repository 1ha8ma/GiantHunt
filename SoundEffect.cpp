#include"DxLib.h"
#include"Loader.h"
#include"SoundEffect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundEffect::SoundEffect()
{
	Loader* loader = loader->GetInstance();

	//�n���h�����[�h�E���ʒ���
	handle[SEKind::NormalAttack] = loader->GetHandle(Loader::Kind::NormalAttackSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::NormalAttack / 100, handle[SEKind::NormalAttack]);
	handle[SEKind::MowinDownAttack] = loader->GetHandle(Loader::Kind::MowinDownSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::MowingAttack / 100, handle[SEKind::MowinDownAttack]);
	handle[SEKind::Swing] = loader->GetHandle(Loader::Kind::SwingSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::Swing / 100, handle[SEKind::Swing]);
	handle[SEKind::HitWeakPoint] = loader->GetHandle(Loader::Kind::HitWeakPointSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::HitWeakPoint / 100, handle[SEKind::HitWeakPoint]);
	handle[SEKind::CursorMove] = loader->GetHandle(Loader::Kind::CursorMoveSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::CursorMove / 100, handle[SEKind::CursorMove]);
	handle[SEKind::Crick] = loader->GetHandle(Loader::Kind::CrickSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::Crick / 100, handle[SEKind::Crick]);
	handle[SEKind::RockHit] = loader->GetHandle(Loader::Kind::RockHitSE);
	ChangeVolumeSoundMem(255 * (int)Ratio::RockHit / 100, handle[SEKind::RockHit]);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundEffect::~SoundEffect()
{

}

/// <summary>
/// SE�Đ�
/// </summary>
/// <param name="kind">SE�̎��</param>
void SoundEffect::PlaySE(SEKind kind)
{
	PlaySoundMem(handle[kind], DX_PLAYTYPE_BACK, true);
}

/// <summary>
/// �����SE�I��
/// </summary>
/// <param name="kind"></param>
void SoundEffect::StopSE(SEKind kind)
{
	if (CheckSoundMem(handle[kind]))
	{
		StopSoundMem(handle[kind]);
	}
}