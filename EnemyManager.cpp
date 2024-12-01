#include"DxLib.h"
#include"Enemy.h"
#include"Utility.h"
#include"Loader.h"
#include"EnemyManager.h"

//�萔��`
const int EnemyManager::NumberofEnemy = 3;

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		delete enemy[i];
	}
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
void EnemyManager::Update(std::vector<int> outchara)
{
	//�X�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (!enemy[i]->GetOutflg())
		{
			enemy[i]->Update(outchara);
		}
	}
}

/// <summary>
/// ���Ə��̍X�V
/// </summary>
/// <param name="playershieldleft">�v���C���[���J�v�Z����</param>
/// <param name="playershieldright">�v���C���[���J�v�Z���E</param>
void EnemyManager::UpdateFistWithShield(VECTOR playershieldleft,VECTOR playershieldright)
{
	//CPU�̌��Ə��̓����蔻��
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
			withenemyjudge = enemy[i]->FistWithShield(enemy[checkenemy]->GetShieldLeft(), enemy[checkenemy]->GetShieldRight());
			if (withenemyjudge)
			{
				hit = true;
			}
		}
		bool withplayerjudge = enemy[i]->FistWithShield(playershieldleft, playershieldright);//�v���C���[��
		if (withplayerjudge)
		{
			hit = true;
		}

		enemy[i]->SetShieldHit(hit);
		enemy[i]->PlayShieldHitSE(hit);
	}
}

/// <summary>
/// ���ƃL�����N�^�[�̓����蔻��X�V
/// </summary>
/// <param name="playerTop">�v���C���[�J�v�Z����</param>
/// <param name="playerBottom">�v���C���[�J�v�Z����</param>
/// <param name="playerout">�v���C���[���E�����Ă��邩</param>
void EnemyManager::UpdateFistWithCharacter(VECTOR playerTop,VECTOR playerBottom,bool playerout,bool lastchara)
{
	//�v���C���[�Ƃ̓����蔻��
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
	//CPU�ǂ����̓����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)
		{
			if (!enemy[i]->GetOutflg())//�E�����Ă��Ȃ�������
			{
				//�m�F����CPU��ݒ�
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
/// �����m�̓����蔻��X�V
/// </summary>
/// <param name="playershieldleft"></param>
/// <param name="playershieldright"></param>
void EnemyManager::UpdateShieldWithShield(VECTOR playershieldleft, VECTOR playershieldright)
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		for (int j = 0; j < EnemyManager::NumberofEnemy - 1; j++)//CPU�ǂ���
		{
			//�ΏۃL�����ݒ�
			int checkenemy = i + j + 1;
			if (checkenemy > EnemyManager::NumberofEnemy - 1)
			{
				checkenemy -= EnemyManager::NumberofEnemy;
			}
			
			enemy[i]->UpdateShieldWithShield(enemy[checkenemy]->GetShieldLeft(), enemy[checkenemy]->GetShieldRight());
		}
		//�v���C���[��
		enemy[i]->UpdateShieldWithShield(playershieldleft, playershieldright);
	}
}

/// <summary>
/// �|�W�V�����X�V
/// </summary>
void EnemyManager::ReflectPosition()
{
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->UpdatePosition();
	}
}

/// <summary>
/// �I����A�E����������X�V
/// </summary>
void EnemyManager::ForeverUpdate(bool Settlement)
{
	//�E������K�v�ȍX�V
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		enemy[i]->ForeverUpdate(Settlement);
	}
}

/// <summary>
/// �U���ɓ�������
/// </summary>
/// <param name="i">CPU�ԍ�</param>
/// <param name="hit">����������</param>
void EnemyManager::CheckOut(int i, bool hit, bool lastchara)
{
	enemy[i]->CheckOut(hit, lastchara);
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