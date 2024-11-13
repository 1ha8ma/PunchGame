#include<math.h>
#include"DxLib.h"
#include"FPS.h"

const int FPS::N = 60;
const int FPS::AssumptionFPS = 60;

/// <summary>
/// �R���X�g���N�^
/// </summary>
FPS::FPS()
{
	StartTime = 0;
	flameCount = 0;
	mFps = 0;
}

/// <summary>
/// �X�V
/// </summary>
/// <returns></returns>
void FPS::Update()
{
	if (flameCount == 0)//1�t���[���ڂȂ玞�����L��
	{
		StartTime = GetNowCount();
	}
	if (flameCount == N)//N�t���[���ڂȂ畽�ς��v�Z
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
/// FPS�`��
/// </summary>
void FPS::Draw()
{
	DrawFormatString(100, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

/// <summary>
/// �ҋ@
/// </summary>
void FPS::Wait()
{
	int tookTime = GetNowCount() - StartTime;//������������
	int waitTime = flameCount * 1000 / AssumptionFPS - tookTime;//�҂ׂ�����
	if (waitTime > 0)
	{
		Sleep(waitTime);//�ҋ@
	}
}