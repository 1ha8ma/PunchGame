#include"DxLib.h"
#include"Enemy.h"
#include"EnemyManager.h"

const int EnemyManager::NumberofEnemy = 3;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
	enemy.push_back(NULL);
	enemy[0] = new Enemy("3D/Enemy1.mv1", 4.5f, VGet(-1000.0f, 100.0f, 1000.0f), VGet(1.0f, 0.0f, -1.0f));
	enemy.push_back(NULL);
	enemy[1] = new Enemy("3D/Enemy2.mv1", 4.5f, VGet(1000.f, 100.0f, 1000.0f), VGet(-1.0f, 0.0f, -1.0f));
	enemy.push_back(NULL);
	enemy[2] = new Enemy("3D/Enemy3.mv1", 4.5f, VGet(1000.0f, 100.0f, -700.0f), VGet(-1.0f, 0.0f, 1.0f));
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{

}

/// <summary>
/// 初期化
/// </summary>
void EnemyManager::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
void EnemyManager::Update(VECTOR playerpos)
{
	//近くのキャラ更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->CheckNearCharacter(playerpos);
	}
	enemy[0]->CheckNearCharacter(enemy[1]->GetPosition());
	enemy[0]->CheckNearCharacter(enemy[2]->GetPosition());
	enemy[1]->CheckNearCharacter(enemy[2]->GetPosition());
	enemy[1]->CheckNearCharacter(enemy[0]->GetPosition());
	enemy[2]->CheckNearCharacter(enemy[0]->GetPosition());
	enemy[2]->CheckNearCharacter(enemy[1]->GetPosition());

	//更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->Update();
	}
}

/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->Draw();
	}
}