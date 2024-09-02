#include"DxLib.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
	wood = new WoodBoard();
	camera = new Camera();
	player = new Player();
	skydome = new SkyDome();
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{

}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize()
{
	camera->Initialize();
	player->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	camera->Update();
	//もし終了条件を満たしていなかったら
	return this;
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw()
{
	skydome->Draw();
	wood->Draw();
}