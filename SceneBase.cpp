#include"DxLib.h"
#include"GameScene.h"
#include"SceneBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
{

}

/// <summary>
/// シーンを最初にする
/// </summary>
/// <returns>最初にしたいシーン</returns>
SceneBase* SceneBase::InitializeBase()
{
	return new GameScene();
}