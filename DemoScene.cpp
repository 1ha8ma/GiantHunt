#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"Input.h"
#include"TitleScene.h"
#include"DemoScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
DemoScene::DemoScene()
{
	loader = loader->GetInstance();
	input = new Input();

	movieHandle = loader->GetHandle(Loader::Kind::DemoMovie);
	SetGraphMode(1920 + 800, 1080 + 800, 32);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DemoScene::~DemoScene()
{
	PauseMovieToGraph(movieHandle);
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
}

/// <summary>
/// ������
/// </summary>
void DemoScene::Initialize()
{
	
}

/// <summary>
/// �X�V
/// </summary>
/// <returns></returns>
SceneBase* DemoScene::Update()
{
	if (GetMovieStateToGraph(movieHandle) == 0)
	{
		PlayMovie("2D/DemoMovie.mp4",1,DX_MOVIEPLAYTYPE_BCANCEL);
	}

	if (input->GetInputState() != 0)
	{
		return new TitleScene();
	}

	return this;
}

/// <summary>
/// �`��
/// </summary>
void DemoScene::Draw()
{
}