#pragma once

class FPS
{
public:
	FPS();
	void Update();//�X�V
	void Wait();//�ҋ@

	static const int N;//���ς����T���v����
	static const int AssumptionFPS;//�z�肵�Ă���FPS

private:
	int StartTime;//����J�n����
	int flameCount;    //�J�E���^
	float mFps;    //fps
};