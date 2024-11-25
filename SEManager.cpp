#include"DxLib.h"
#include"Loader.h"
#include"SEManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
SEManager::SEManager()
{
	Loader* loader = loader->GetInstance();

	handle[StartSceneSE] = loader->GetHandle(Loader::Kind::StartSceneSE);
	handle[StartCountSE] = loader->GetHandle(Loader::Kind::CountSE);
	handle[StartSE] = loader->GetHandle(Loader::Kind::StartSE);
	handle[ShieldhitSE] = loader->GetHandle(Loader::Kind::ShieldHitSE);
	handle[CrickSE] = loader->GetHandle(Loader::Kind::CrickSE);
	handle[AttackSE] = loader->GetHandle(Loader::Kind::AttackSE);
	handle[CharahitSE] = loader->GetHandle(Loader::Kind::CharacterHitSE);
	handle[CursorMoveSE] = loader->GetHandle(Loader::Kind::CursorMoveSE);
	handle[CursorSelectSE] = loader->GetHandle(Loader::Kind::CursorSelectSE);
	handle[OpenPauseSE] = loader->GetHandle(Loader::Kind::OpenPauseSE);

	ChangeVolumeSoundMem(255 * 300 / 100, handle[CharahitSE]);//音量変更
}

/// <summary>
/// SE再生
/// </summary>
/// <param name="kind">再生したい種類</param>
void SEManager::PlaySE(SEKind kind)
{
	PlaySoundMem(handle[kind], DX_PLAYTYPE_BACK, true);
}