#include"DxLib.h"
#include"SceneBase.h"
#include"GameManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager()
{
	//シーンを初期化
	nowscene = SceneBase::InitializeBase();
}

/// <summary>
/// 更新
/// </summary>
void GameManager::Update()
{
	//シーン更新
	nextscene = nowscene->Update();

	//nextsceneがnowsceneと違えばシーン変更
	if (nextscene != nowscene)
	{
		ChangeScene();
	}
}

/// <summary>
/// 描画
/// </summary>
void GameManager::Draw()
{
	nowscene->Draw();
}

/// <summary>
/// ステージ変更
/// </summary>
void GameManager::ChangeScene()
{
	//現在のシーンを削除
	delete(nowscene);

	//シーン切り替え
	nowscene = nextscene;

	//シーン初期化
	nowscene->Initialize();

	//nextscene初期化
	nextscene = NULL;
}