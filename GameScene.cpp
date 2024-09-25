#include"DxLib.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
#include"Shield.h"
#include"InputManager.h"
#include"Fist.h"
#include"EnemyManager.h"
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
	input = new InputManager();
	shield = new Shield();
	fist = new Fist();
	enemy = new EnemyManager();
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
	shield->Initialize();
	fist->Initialize();
	enemy->Initialize();
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	camera->Update();
	player->Update(input->GetInputState());
	enemy->Update(player->GetPos());
	shield->Update(player->GetPos(), player->GetAngle());
	fist->Update(player->GetPos(),player->GetAngle(),player->GetAttackflg());

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
	player->Draw();
	shield->Draw();
	fist->Draw();
	enemy->Draw();
}