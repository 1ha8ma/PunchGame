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
/// �R���X�g���N�^
/// </summary>
GameScene::GameScene()
{
	//�C���X�^���X��
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
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{

}

/// <summary>
/// ������
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
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	//�X�V
	camera->Update();
	player->Update(input->GetInputState(), shieldhit);
	enemy->Update(player->GetPosition(), player->GetPositioncapsuleTop(), player->GetPositioncapsuleBotoom(),player->GetShieldLeft(),player->GetShieldRight(), player->GetOutflg(), outchara);

	//���Ƃ̓����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		shieldhit = false;
		if (player->FistWithShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i), 20.0f))
		{
			shieldhit = true;
			break;
		}
	}

	//�����蔻��
	for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
	{
		if (player->GetAttackflg())
		{
			bool characterhit;
			characterhit = player->FistWithCharacter(enemy->GetCapsuleTop(i), enemy->GetCapsuleBottom(i), 120.0f, enemy->GetOutflg(i));
			enemy->CheckOut(i, characterhit);
		}
	}


	//�E���m�F
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
				if (outchara[j] == i)//���łɒE�����Ă���ꍇ
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

	//CPU�^�[�Q�b�g�|�W�V�����ݒ�
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

	//�I�������𖞂����Ă�����resurt�ɑJ��
	if (outchara.size() == 4)
	{
		return new ResultScene();
	}

	//�����I�������𖞂����Ă��Ȃ�������
	return this;
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw()
{
	skydome->Draw();
	wood->Draw();
	player->Draw();
	enemy->Draw();
}