#include"DxLib.h"
#include"Utility.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
#include"InputManager.h"
#include"EnemyManager.h"
#include"ResultScene.h"
#include"GameScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
	camera = new Camera();
	input = new InputManager();
	skydome = new SkyDome();
	wood = new WoodBoard();
	player = new Player();
	enemy = new EnemyManager();

	shieldhit = false;
	outchara.push_back(-1);
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
	enemy->Initialize();

	shieldhit = false;
	outchara.clear();
	outchara.push_back(-1);
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	//更新
	camera->Update();
	player->Update(input->GetInputState(), shieldhit);
	enemy->Update(player->GetPosition(), player->GetPositioncapsuleTop(), player->GetPositioncapsuleBotoom(),player->GetShieldLeft(),player->GetShieldRight(), player->GetOutflg(), outchara);

	//盾との当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		shieldhit = false;
		if (player->FistWithShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i), 20.0f))
		{
			shieldhit = true;
			break;
		}
	}

	//当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (player->GetAttackflg())
		{
			bool characterhit;
			characterhit = player->FistWithCharacter(enemy->GetCapsuleTop(i), enemy->GetCapsuleBottom(i), 120.0f, enemy->GetOutflg(i));
			enemy->CheckOut(i, characterhit);
		}
	}


	//脱落確認
	if (player->GetOutflg())
	{
		outchara.push_back(0);
	}
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy->GetOutflg(i))
		{
			bool sumi = false;
			for (int j = 0; j < outchara.size(); j++)
			{
				if (outchara[j] == i)//すでに脱落している場合
				{
					sumi = true;
				}
			}
			if (sumi == false)
			{
				outchara.push_back(i);
			}
		}
	}

	//CPUターゲットポジション設定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy->GetTargetNumber(i) == static_cast<int>(CharaNumber::CPU0))
		{
			enemy->SetTargetPosition(i, enemy->GetPosition(static_cast<int>(CharaNumber::CPU0)));
		}
		if (enemy->GetTargetNumber(i) == static_cast<int>(CharaNumber::CPU1))
		{
			enemy->SetTargetPosition(i, enemy->GetPosition(static_cast<int>(CharaNumber::CPU1)));
		}
		if (enemy->GetTargetNumber(i) == static_cast<int>(CharaNumber::CPU2))
		{
			enemy->SetTargetPosition(i, enemy->GetPosition(static_cast<int>(CharaNumber::CPU2)));
		}
		if (enemy->GetTargetNumber(i) == static_cast<int>(CharaNumber::Player))
		{
			enemy->SetTargetPosition(i, player->GetPosition());
		}
	}

	//終了条件を満たしていたらresurtに遷移
	if (outchara.size() == 4)
	{
		return new ResultScene();
	}

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
	enemy->Draw();
}