#include"DxLib.h"
#include"Loader.h"
#include"BGMManager.h"

/// <summary>
/// コンストラクタ
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
/// BGM再生
/// </summary>
/// <param name="kind">再生したいBGMの種類</param>
void BGMManager::PlayBGM(BGMKind kind)
{
	if (!CheckSoundMem(PlayingBGM))
	{
		PlayingBGM = handle[kind];
		PlaySoundMem(PlayingBGM, DX_PLAYTYPE_LOOP, true);
	}
}

/// <summary>
/// 再生中のBGMを止める
/// </summary>
void BGMManager::StopBGM()
{
	if (CheckSoundMem(PlayingBGM))
	{
		StopSoundMem(PlayingBGM);
	}
}