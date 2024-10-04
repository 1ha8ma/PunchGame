#include"DxLib.h"
#include"Utility.h"
#include"GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/////////////////////////
	// 基本設定
	/////////////////////////
	//ウィンドウモード
	SetGraphMode(SCREEN_W, SCREEN_H, 32);
	ChangeWindowMode(TRUE);//制作時：TRUE 本番：FALSE
	//ライブラリ初期化
	DxLib_Init();
	//ウィンドウモード命名変更
	SetMainWindowText("ぶっ飛びパンチ");
	//ダブルバッファリングを有効
	SetDrawScreen(DX_SCREEN_BACK);

	////////////////////////
	// ゲーム初期化
	////////////////////////
	ClearDrawScreen();
	SetFontSize(64);
	//DrawString(600, SCREEN_H / 2, "NowLoading・・・", GetColor(0, 124, 98), TRUE);
	ScreenFlip();
	//ゲームマネージャーインスタンス化
	GameManager* game = new GameManager();

	////////////////////////
	// ゲームループ
	////////////////////////
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		ClearDrawScreen();

		game->Update();
		game->Draw();

		ScreenFlip();

		//ウィンドウメッセージ処理
		if (ProcessMessage() < 0)
		{
			break;
		}
		//ESC終了
		else if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	//ゲーム終了
	DxLib_End();

	return 0;
}