#include"DxLib.h"
#include"Loader.h"
#include"Wall.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Wall::Wall()
{
	Loader* loader = loader->GetInstance();

	modelHandle = loader->GetHandle(Loader::Kind::WallModel);

	MV1SetScale(modelHandle, VGet(100.0f, 100.0f, 5.0f));
	MV1SetPosition(modelHandle, VGet(0.0f, 0.0f, 4800.0f));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{

}

/// <summary>
/// �`��
/// </summary>
void Wall::Draw()
{
	MV1DrawModel(modelHandle);
}