#include"DxLib.h"
#include"Loader.h"

//�C���X�^���X���ŏ��ɋ�ɂ���
Loader* Loader::loader = nullptr;

/// <summary>
/// �C���X�^���X�Q�b�g
/// </summary>
/// <returns>�C���X�^���X</returns>
Loader* Loader::GetInstance()
{
	//�C���X�^���X��������ΐ���
	if (loader == nullptr)
	{
		loader = new Loader();
	}

	return loader;
}

/// <summary>
/// ���[�h
/// </summary>
void Loader::Load()
{

}