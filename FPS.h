#pragma once

class FPS
{
public:
	FPS();
	void Update();//更新
	void Wait();//待機

	static const int N;//平均を取るサンプル数
	static const int AssumptionFPS;//想定しているFPS

private:
	int StartTime;//測定開始時刻
	int flameCount;    //カウンタ
	float mFps;    //fps
};