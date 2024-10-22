#include"DxLib.h"
#include"Loader.h"
#include"BGMManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BGMManager::BGMManager()
{
	Loader* loader = loader->GetInstance();
	handle[TitleBGM] = loader->GetHandle(Loader::Kind::TitleBGM);
	handle[GameBGM] = loader->GetHandle(Loader::Kind::GameBGM);
	handle[ResultBGM] = loader->GetHandle(Loader::Kind::ResultBGM);

	PlayingBGM = handle[TitleBGM];
}

/// <summary>
/// BGM�Đ�
/// </summary>
/// <param name="kind">�Đ�������BGM�̎��</param>
void BGMManager::PlayBGM(BGMKind kind)
{
	if (!CheckSoundMem(PlayingBGM))
	{
		PlayingBGM = handle[kind];
		PlaySoundMem(PlayingBGM, DX_PLAYTYPE_LOOP, true);
	}
}

/// <summary>
/// �Đ�����BGM���~�߂�
/// </summary>
void BGMManager::StopBGM()
{
	if (CheckSoundMem(PlayingBGM))
	{
		StopSoundMem(PlayingBGM);
	}
}