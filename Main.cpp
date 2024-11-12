#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
#include"GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	// 基本設定
	/////////////////////////
	//ウィンドウモード
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(TRUE);//小画面：TRUE 全画面：FALSE
	//ライブラリ初期化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	Effekseer_Init(8000);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);

	//ウィンドウモード命名変更
	SetMainWindowText("ぶっ飛びパンチ");
	//ダブルバッファリングを有効
	SetDrawScreen(DX_SCREEN_BACK);

	////////////////////////
	// ゲーム初期化
	////////////////////////
	Loader* loader = Loader::GetInstance();
	loader->LoadModel();

	//ゲームマネージャーインスタンス化
	GameManager* game = new GameManager();

	////////////////////////
	// ゲームループ
	////////////////////////
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//auto prevTime = GetNowHiPerformanceCount();//処理が始まる前の時間

		//画面クリア
		ClearDrawScreen();

		//更新
		game->Update();
		//描画
		game->Draw();

		ScreenFlip();

		//FPS固定
		//auto afterTime = GetNowHiPerformanceCount(); // 処理が終わった後の時間
		//while (afterTime - prevTime < 16667)
		//{
		//	afterTime = GetNowHiPerformanceCount();
		//}
	}

	//ゲーム終了
	Effkseer_End();
	DxLib_End();

	return 0;
}