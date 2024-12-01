#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Loader.h"
#include"FPS.h"
#include"GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	// 基本設定
	/////////////////////////
	//ウィンドウモード
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	SetWaitVSyncFlag(FALSE);//垂直同期設定 TRUE : あり FALSE : なし
	ChangeWindowMode(FALSE);//小画面：TRUE 全画面：FALSE
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
	//フォント設定
	ChangeFont("851テガキカクット", DX_CHARSET_DEFAULT);

	//モデル等ロード
	Loader* loader = Loader::GetInstance();
	loader->LoadModel();

	//インスタンス化
	FPS* fps = new FPS();
	GameManager* game = new GameManager();

	////////////////////////
	// ゲームループ
	////////////////////////
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//画面クリア
		ClearDrawScreen();

		//FPS更新
		fps->Update();

		//更新
		game->Update();
		//描画処理
		game->Draw();
		
		//描画
		ScreenFlip();

		//FPS待機
		fps->Wait();
	}

	//ゲーム終了
	Effkseer_End();
	DxLib_End();

	return 0;
}