#include"DxLib.h"
#include"Loader.h"
#include"FPS.h"
#include"GameManager.h"
#include"Utility.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	//　基本設定
	/////////////////////////
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	SetWaitVSyncFlag(FALSE);//垂直同期
	ChangeWindowMode(TRUE);//FASLE 大　TRUE 小
	//ライティング処理使用設定
	SetUseLighting(FALSE);

	//ライブラリ初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();

	//ウィンドウモード名前変更
	SetMainWindowText("GiantHunt");
	//ダブルバッファリングを有効
	SetDrawScreen(DX_SCREEN_BACK);

	/////////////////////////
	// ゲーム初期化
	/////////////////////////
	//素材ロード
	Loader* loader = loader->GetInstance();
	loader->Load();

	//インスタンス化
	FPS* fps = new FPS();
	GameManager* game = new GameManager();

	/////////////////////////
	// ゲームループ
	/////////////////////////
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		//画面クリア
		ClearDrawScreen();

		//fps更新
		fps->Update();

		//更新
		game->Update();
		//描画処理
		game->Draw();

		//描画
		ScreenFlip();

		//fps待機
		fps->Wait();
	}

	//終了
	DxLib_End();

}
