#include"DxLib.h"
#include"Enemy.h"
#include"Utility.h"
#include"Loader.h"
#include"EnemyManager.h"

//定数定義
const int EnemyManager::NumberofEnemy = 3;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
	Loader* loader = Loader::GetInstance();

	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU0)] = new Enemy(loader->GetHandle(Loader::Kind::Enemy1Model), ModelSize, InitialPosition0, InitialTargetDir0, static_cast<int>(CharaNumber::CPU0));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU1)] = new Enemy(loader->GetHandle(Loader::Kind::Enemy2Model), ModelSize, InitialPosition1, InitialTargetDir1, static_cast<int>(CharaNumber::CPU1));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU2)] = new Enemy(loader->GetHandle(Loader::Kind::Enemy3Model), ModelSize, InitialPosition2, InitialTargetDir2, static_cast<int>(CharaNumber::CPU2));
	
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		delete enemy[i];
	}
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
void EnemyManager::Update(std::vector<int> outchara)
{
	//更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (!enemy[i]->GetOutflg())
		{
			enemy[i]->Update(outchara);
		}
	}
}

/// <summary>
/// 拳と盾の更新
/// </summary>
/// <param name="playershieldleft">プレイヤー盾カプセル左</param>
/// <param name="playershieldright">プレイヤー盾カプセル右</param>
void EnemyManager::UpdateFistWithShield(VECTOR playershieldleft,VECTOR playershieldright)
{
	//CPUの拳と盾の当たり判定
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
			withenemyjudge = enemy[i]->FistWithShield(enemy[checkenemy]->GetShieldLeft(), enemy[checkenemy]->GetShieldRight());
			if (withenemyjudge)
			{
				hit = true;
			}
		}
		bool withplayerjudge = enemy[i]->FistWithShield(playershieldleft, playershieldright);//プレイヤーと
		if (withplayerjudge)
		{
			hit = true;
		}

		enemy[i]->SetShieldHit(hit);
		enemy[i]->PlayShieldHitSE(hit);
	}
}

/// <summary>
/// 拳とキャラクターの当たり判定更新
/// </summary>
/// <param name="playerTop">プレイヤーカプセル上</param>
/// <param name="playerBottom">プレイヤーカプセル下</param>
/// <param name="playerout">プレイヤーが脱落しているか</param>
void EnemyManager::UpdateFistWithCharacter(VECTOR playerTop,VECTOR playerBottom,bool playerout,bool lastchara)
{
	//プレイヤーとの当たり判定
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (!enemy[i]->GetOutflg())
		{
			playerhit = enemy[i]->FistWithCharacter(playerTop, playerBottom, playerout);
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
			if (!enemy[i]->GetOutflg())//脱落していなかったら
			{
				//確認するCPUを設定
				int checkenemy = i + j + 1;
				if (checkenemy > EnemyManager::NumberofEnemy - 1)
				{
					checkenemy -= EnemyManager::NumberofEnemy;
				}
				enemy[checkenemy]->CheckOut(enemy[i]->FistWithCharacter(enemy[checkenemy]->GetPositioncapsuleTop(), enemy[checkenemy]->GetPositioncapsuleBotoom(), enemy[checkenemy]->GetOutflg()),lastchara);
			}
		}
	}
}

/// <summary>
/// 盾同士の当たり判定更新
/// </summary>
/// <param name="playershieldleft"></param>
/// <param name="playershieldright"></param>
void EnemyManager::UpdateShieldWithShield(VECTOR playershieldleft, VECTOR playershieldright)
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)//CPUどうし
		{
			//対象キャラ設定
			int checkenemy = i + j + 1;
			if (checkenemy > EnemyManager::NumberofEnemy - 1)
			{
				checkenemy -= EnemyManager::NumberofEnemy;
			}
			
			enemy[i]->UpdateShieldWithShield(enemy[checkenemy]->GetShieldLeft(), enemy[checkenemy]->GetShieldRight());
		}
		//プレイヤーと
		enemy[i]->UpdateShieldWithShield(playershieldleft, playershieldright);
	}
}

/// <summary>
/// ポジション更新
/// </summary>
void EnemyManager::ReflectPosition()
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->UpdatePosition();
	}
}

/// <summary>
/// 終了後、脱落後も続く更新
/// </summary>
void EnemyManager::ForeverUpdate(bool Settlement)
{
	//脱落後も必要な更新
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->ForeverUpdate(Settlement);
	}
}

/// <summary>
/// 攻撃に当たった
/// </summary>
/// <param name="i">CPU番号</param>
/// <param name="hit">当たったか</param>
void EnemyManager::CheckOut(int i, bool hit, bool lastchara)
{
	enemy[i]->CheckOut(hit, lastchara);
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

void EnemyManager::SetTargetCharaPosition(int i, VECTOR targetcharaPos)
{
	enemy[i]->SetTargetCharaPosition(targetcharaPos);
}

void EnemyManager::SetTargetCharaAngle(int i, float targetcharaAngle)
{
	enemy[i]->SetTargetCharaAngle(targetcharaAngle);
}

float EnemyManager::GetAngle(int i)
{
	return enemy[i]->GetAngle();
}

int EnemyManager::GetNowMoveKind(int i)
{
	return enemy[i]->GetNowMoveKind();
}