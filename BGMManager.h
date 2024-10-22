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

	//�R���X�g���N�^
	BGMManager();

	//�Đ�
	void PlayBGM(BGMKind kind);

	void ChangeBGM(BGMKind nextkind);

	//BGM���~�߂�
	void StopBGM();

private:

	std::map<BGMKind, int> handle;

	int PlayingBGM;//�Đ�����BGM

};