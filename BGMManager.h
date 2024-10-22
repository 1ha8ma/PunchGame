#pragma once
#include<map>

class BGMManager
{
public:
	enum BGMKind
	{
		TitleBGM,
		GameBGM,
		ResultBGM,
	};

	//コンストラクタ
	BGMManager();

	//再生
	void PlayBGM(BGMKind kind);

	void ChangeBGM(BGMKind nextkind);

	//BGMを止める
	void StopBGM();

private:

	std::map<BGMKind, int> handle;

	int PlayingBGM;//再生中のBGM

};