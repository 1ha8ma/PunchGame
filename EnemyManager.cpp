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

	playerhit = false;
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
	playerhit = false;
}

/// <summary>
/// �X�V
/// </summary>
void EnemyManager::Update(VECTOR playerpos, VECTOR playerTop, VECTOR playerBottom, VECTOR playershieldLeft, VECTOR playershieldRight, bool playerout, std::vector<int> outchara)
{
	//�X�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (enemy[i]->GetOutflg() == false)
		{
			enemy[i]->Update(outchara);
		}
	}


	//CPU�Ə��̓����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		bool hit = false;

		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)//CPU�ǂ���
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
		bool withplayerjudge = enemy[i]->FistWithShield(playershieldLeft, playershieldRight, 20.0f);//�v���C���[��
		if (withplayerjudge)
		{
			hit = true;
		}

		enemy[i]->SetShieldHit(hit);
	}

	//�v���C���[�Ƃ̓����蔻��
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
	//CPU�ǂ����̓����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)
		{
			if (enemy[i]->GetOutflg() == false && enemy[i]->GetAttackflg())//�E�����Ă��炸�A�U�����Ă�����
			{
				//�m�F����CPU��ݒ�
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
/// �I����A�E����������X�V
/// </summary>
void EnemyManager::ForeverUpdate()
{
	//�E������K�v�ȍX�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->OtherClassUpdate(enemy[i]->GetShieldHit());
		enemy[i]->UpdateCapsule();
		enemy[i]->Blow();
		enemy[i]->UpdateEffect(enemy[i]->GetShieldHit());
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

float EnemyManager::GetAngle(int i)
{
	return enemy[i]->GetAngle();
}