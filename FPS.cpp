#include<math.h>
#include"DxLib.h"
#include"FPS.h"

const int FPS::N = 60;
const int FPS::AssumptionFPS = 60;

/// <summary>
/// コンストラクタ
/// </summary>
FPS::FPS()
{
	StartTime = 0;
	flameCount = 0;
	mFps = 0;
}

/// <summary>
/// 更新
/// </summary>
/// <returns></returns>
void FPS::Update()
{
	if (flameCount == 0)//1フレーム目なら時刻を記憶
	{
		StartTime = GetNowCount();
	}
	if (flameCount == N)//Nフレーム目なら平均を計算
	{
		int t = GetNowCount();
		mFps = 1000.0f / ((t - StartTime) / (float)N);
		flameCount = 0;
		StartTime = t;
	}
	else
	{
		flameCount++;
	}
}

/// <summary>
/// FPS描画
/// </summary>
void FPS::Draw()
{
	DrawFormatString(100, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

/// <summary>
/// 待機
/// </summary>
void FPS::Wait()
{
	int tookTime = GetNowCount() - StartTime;//かかった時間
	int waitTime = flameCount * 1000 / AssumptionFPS - tookTime;//待つべき時間
	if (waitTime > 0)
	{
		Sleep(waitTime);//待機
	}
}