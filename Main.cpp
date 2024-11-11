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
	//環境
	//const int FPS = 144;//想定ヘルツ
	//LONGLONG PrevTime = GetNowHiPerformanceCount();//現在の時間を取得
	//LONGLONG NextAddTime = 0;//あまり時間
	//int NextUpdateLoopNum = 1;//次の更新ループの呼び出し回数

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
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		ClearDrawScreen();

		//更新
		//for (int i = 0; i < NextUpdateLoopNum; i++)
		//{
			game->Update();
		//}
		//描画
		game->Draw();

		ScreenFlip();

		//if (!GetActiveFlag())
		//{
		//	//ソフトのウィンドウがアクティブになるまで待つ
		//	while (ProcessMessage() == 0 && !GetActiveFlag())
		//	{
		//		Sleep(1);
		//	}

		//	//アクティブになったら時間関係のパラメータを初期化して次のループに進む
		//	PrevTime = GetNowHiPerformanceCount();
		//	NextAddTime = 0;
		//	NextUpdateLoopNum = 1;
		//}
		//else
		//{
		//	LONGLONG NowTime;
		//	LONGLONG LoopTime;

		//	//現在の時間を取得
		//	NowTime = GetNowHiPerformanceCount();

		//	//前回の時間との差分を計算
		//	LoopTime = NowTime - PrevTime;

		//	//経過した時間が1フレーム分に満たない場合は1フレーム文の時間が経過するまで待つ
		//	if (LoopTime < 1000000 / FPS)
		//	{
		//		while (ProcessMessage() == 0 && LoopTime < 1000000 / FPS)
		//		{
		//			NowTime = GetNowHiPerformanceCount();
		//			LoopTime = NowTime - PrevTime;
		//		}
		//	}

		//	//次のループで実行するUpdate関数の呼び出し回数を算出
		//	NextAddTime = (LoopTime + NextAddTime) - NextUpdateLoopNum * (1000000 / FPS);

		//	//次のループでの計算に使用するための余り時間
		//	LoopTime - NextUpdateLoopNum * (1000000 / FPS);

		//	//今回の時間を保存しておく
		//	PrevTime = NowTime;
		//}

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
	Effkseer_End();
	DxLib_End();

	return 0;
}