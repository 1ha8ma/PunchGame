#include"DxLib.h"
#include"Enemy.h"
#include"Utility.h"
#include"EnemyManager.h"

//定数定義
const int EnemyManager::NumberofEnemy = 3;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU0)] = new Enemy("3D/Enemy1.mv1", ModelSize, InitialPosition0, InitialTargetDir0, static_cast<int>(CharaNumber::CPU0));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU1)] = new Enemy("3D/Enemy2.mv1", ModelSize, InitialPosition1, InitialTargetDir1, static_cast<int>(CharaNumber::CPU1));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU2)] = new Enemy("3D/Enemy3.mv1", ModelSize, InitialPosition2, InitialTargetDir2, static_cast<int>(CharaNumber::CPU2));

	playerhit = false;
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
	playerhit = false;
}

/// <summary>
/// 更新
/// </summary>
void EnemyManager::Update(VECTOR playerpos, VECTOR playerTop, VECTOR playerBottom, VECTOR playershieldLeft, VECTOR playershieldRight, bool playerout, std::vector<int> outchara)
{
	//更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy[i]->GetOutflg() == false)
		{
			enemy[i]->Update(outchara);
		}
	}


	//CPUと盾の当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		bool hit = false;

		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)//CPUどうし
		{
			bool withenemyjudge = false;
			int checkenemy = i + j + 1;
			if (checkenemy > EnemyManager::NumberofEnemy - 1)
			{
				checkenemy -= EnemyManager::NumberofEnemy;
			}
			withenemyjudge = enemy[i]->FistWithShield(enemy[checkenemy]->GetShieldLeft(), enemy[checkenemy]->GetShieldRight(), 20.0f);
			if (withenemyjudge)
			{
				hit = true;
			}
		}
		bool withplayerjudge = enemy[i]->FistWithShield(playershieldLeft, playershieldRight, 20.0f);//プレイヤーと
		if (withplayerjudge)
		{
			hit = true;
		}

		enemy[i]->SetShieldHit(hit);
	}

	//プレイヤーとの当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy[i]->GetOutflg() == false)
		{
			playerhit = enemy[i]->FistWithCharacter(playerTop, playerBottom, 120.0f, playerout);
			if (playerhit)
			{
				break;
			}
		}
	}
	//CPUどうしの当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)
		{
			if (enemy[i]->GetOutflg() == false && enemy[i]->GetAttackflg())//脱落しておらず、攻撃していたら
			{
				//確認するCPUを設定
				int checkenemy = i + j + 1;
				if (checkenemy > EnemyManager::NumberofEnemy - 1)
				{
					checkenemy -= EnemyManager::NumberofEnemy;
				}
				enemy[checkenemy]->CheckOut(enemy[i]->FistWithCharacter(enemy[checkenemy]->GetPositioncapsuleTop(), enemy[checkenemy]->GetPositioncapsuleBotoom(), 120.0f, enemy[checkenemy]->GetOutflg()));
			}
		}
	}
}

/// <summary>
/// 終了後、脱落後も続く更新
/// </summary>
void EnemyManager::ForeverUpdate()
{
	//脱落後も必要な更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->OtherClassUpdate(enemy[i]->GetShieldHit());
		enemy[i]->UpdateCapsule();
		enemy[i]->Blow();
		enemy[i]->UpdateEffect(enemy[i]->GetShieldHit());
	}
}

/// <summary>
/// 攻撃に当たった
/// </summary>
/// <param name="i">CPU番号</param>
/// <param name="hit">当たったか</param>
void EnemyManager::CheckOut(int i,bool hit)
{
	enemy[i]->CheckOut(hit);
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

VECTOR EnemyManager::GetPosition(int i)
{
	return enemy[i]->GetPosition();
}

VECTOR EnemyManager::GetCapsuleTop(int i)
{
	return enemy[i]->GetPositioncapsuleTop();
}

VECTOR EnemyManager::GetCapsuleBottom(int i)
{
	return enemy[i]->GetPositioncapsuleBotoom();
}

bool EnemyManager::GetOutflg(int i)
{
	return enemy[i]->GetOutflg();
}

VECTOR EnemyManager::GetShieldLeft(int i)
{
	return enemy[i]->GetShieldLeft();
}

VECTOR EnemyManager::GetShieldRight(int i)
{
	return enemy[i]->GetShieldRight();
}

int EnemyManager::GetTargetNumber(int i)
{
	return enemy[i]->GetTarGetNumber();
}

void EnemyManager::SetTargetPosition(int i, VECTOR targetPos)
{
	enemy[i]->SetTargetPosition(targetPos);
}

float EnemyManager::GetAngle(int i)
{
	return enemy[i]->GetAngle();
}