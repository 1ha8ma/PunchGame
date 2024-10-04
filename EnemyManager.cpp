#include"DxLib.h"
#include"Enemy.h"
#include"Utility.h"
#include"EnemyManager.h"

//�萔��`
const int EnemyManager::NumberofEnemy = 3;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyManager::EnemyManager()
{
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU0)] = new Enemy("3D/Enemy1.mv1", ModelSize, InitialPosition0, InitialTargetDir0, static_cast<int>(CharaNumber::CPU0));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU1)] = new Enemy("3D/Enemy2.mv1", ModelSize, InitialPosition1, InitialTargetDir1, static_cast<int>(CharaNumber::CPU1));
	enemy.push_back(NULL);
	enemy[static_cast<int>(CharaNumber::CPU2)] = new Enemy("3D/Enemy3.mv1", ModelSize, InitialPosition2, InitialTargetDir2, static_cast<int>(CharaNumber::CPU2));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{

}

/// <summary>
/// ������
/// </summary>
void EnemyManager::Initialize()
{

}

/// <summary>
/// �X�V
/// </summary>
void EnemyManager::Update(VECTOR playerpos, VECTOR playerTop, VECTOR playerBottom, VECTOR playershieldLeft, VECTOR playershieldRight, bool playerout, std::vector<int> outchara)
{
	//�v���C���[�Ƃ̓����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy[i]->GetOutflg() == false)
		{
			enemy[i]->FistWithCharacter(playerTop, playerBottom, 120.0f, playerout);
		}
	}

	//CPU�Ə��̓����蔻��
	if (enemy[static_cast<int>(CharaNumber::CPU0)]->GetOutflg() == false)//0�Ƒ�CPU�̏��̓����蔻��
	{
		bool judge1 = enemy[static_cast<int>(CharaNumber::CPU0)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU1)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU1)]->GetShieldRight(), 20);
		bool judge2 = enemy[static_cast<int>(CharaNumber::CPU0)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU2)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU2)]->GetShieldRight(), 20);
		bool judge3 = enemy[static_cast<int>(CharaNumber::CPU0)]->FistWithShield(playershieldLeft, playershieldRight, 20);
		if (judge1 || judge2 || judge3)
		{
			enemy[static_cast<int>(CharaNumber::CPU0)]->SetShieldHit(true);
		}
		else
		{
			enemy[static_cast<int>(CharaNumber::CPU0)]->SetShieldHit(false);
		}
	}
	if (enemy[static_cast<int>(CharaNumber::CPU1)]->GetOutflg() == false)//1�Ƒ�
	{
		bool judge1 = enemy[static_cast<int>(CharaNumber::CPU1)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU2)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU2)]->GetShieldRight(), 20);
		bool judge2 = enemy[static_cast<int>(CharaNumber::CPU1)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU0)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU0)]->GetShieldRight(), 20);
		bool judge3 = enemy[static_cast<int>(CharaNumber::CPU1)]->FistWithShield(playershieldLeft, playershieldRight, 20);
		if (judge1 || judge2 || judge3)
		{
			enemy[static_cast<int>(CharaNumber::CPU1)]->SetShieldHit(true);
		}
		else
		{
			enemy[static_cast<int>(CharaNumber::CPU1)]->SetShieldHit(false);
		}
	}
	if (enemy[static_cast<int>(CharaNumber::CPU2)]->GetOutflg() == false)//2�Ƒ�
	{
		bool judge1 = enemy[static_cast<int>(CharaNumber::CPU2)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU0)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU0)]->GetShieldRight(), 20);
		bool judge2 = enemy[static_cast<int>(CharaNumber::CPU2)]->FistWithShield(enemy[static_cast<int>(CharaNumber::CPU1)]->GetShieldLeft(), enemy[static_cast<int>(CharaNumber::CPU1)]->GetShieldRight(), 20);
		bool judge3 = enemy[static_cast<int>(CharaNumber::CPU2)]->FistWithShield(playershieldLeft, playershieldRight, 20);
		if (judge1 || judge2 || judge3)
		{
			enemy[static_cast<int>(CharaNumber::CPU2)]->SetShieldHit(true);
		}
		else
		{
			enemy[static_cast<int>(CharaNumber::CPU2)]->SetShieldHit(false);
		}
	}

	//CPU�Ƃ̓����蔻��
	if (enemy[static_cast<int>(CharaNumber::CPU0)]->GetOutflg() == false)//0�Ƒ�CPU�̓����蔻��
	{
		enemy[static_cast<int>(CharaNumber::CPU1)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU0)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU1)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU1)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU1)]->GetOutflg()));
		enemy[static_cast<int>(CharaNumber::CPU2)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU0)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU2)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU2)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU2)]->GetOutflg()));
	}
	if (enemy[static_cast<int>(CharaNumber::CPU1)]->GetOutflg() == false)//1�Ƒ�
	{
		enemy[static_cast<int>(CharaNumber::CPU2)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU1)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU2)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU2)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU2)]->GetOutflg()));
		enemy[static_cast<int>(CharaNumber::CPU0)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU1)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU0)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU0)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU0)]->GetOutflg()));
	}
	if (enemy[static_cast<int>(CharaNumber::CPU2)]->GetOutflg() == false)//2�Ƒ�
	{
		enemy[static_cast<int>(CharaNumber::CPU0)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU2)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU0)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU0)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU0)]->GetOutflg()));
		enemy[static_cast<int>(CharaNumber::CPU1)]->CheckOut(enemy[static_cast<int>(CharaNumber::CPU2)]->FistWithCharacter(enemy[static_cast<int>(CharaNumber::CPU1)]->GetPositioncapsuleTop(), enemy[static_cast<int>(CharaNumber::CPU1)]->GetPositioncapsuleBotoom(), 120.0f, enemy[static_cast<int>(CharaNumber::CPU1)]->GetOutflg()));
	}

	//�X�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy[i]->GetOutflg() == false)
		{
			enemy[i]->Update(outchara);
		}
	}

	//�E������K�v�ȍX�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->OtherClassUpdate(enemy[i]->GetShieldHit());
		enemy[i]->Blow();
	}
}

/// <summary>
/// �U���ɓ�������
/// </summary>
/// <param name="i">CPU�ԍ�</param>
/// <param name="hit">����������</param>
void EnemyManager::CheckOut(int i,bool hit)
{
	enemy[i]->CheckOut(hit);
}

/// <summary>
/// �`��
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