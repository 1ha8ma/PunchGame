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

	playerattackshieldhit = false;
	outchara.push_back(-1);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	int a = 0;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	camera->Initialize();
	player->Initialize();
	enemy->Initialize();

	gameendflg = false;
	playeroutcheck = false;
	playerattackshieldhit = false;
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
	if (gameendflg == false)
	{
		if (player->GetOutflg() == false)
		{
			player->Update(input->GetInputState(), playerattackshieldhit);
		}
		enemy->Update(player->GetPosition(), player->GetPositioncapsuleTop(), player->GetPositioncapsuleBotoom(), player->GetShieldLeft(), player->GetShieldRight(), player->GetOutflg(), outchara);

		//���Ƃ̓����蔻��
		if (player->GetOutflg() == false)
		{
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				playerattackshieldhit = false;
				if (player->FistWithShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i), 20.0f))
				{
					playerattackshieldhit = true;
					break;
				}
			}
		}

		//�����蔻��
		if (player->GetOutflg() == false)
		{
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				if (player->GetAttackflg())
				{
					bool characterhit;
					characterhit = player->FistWithCharacter(enemy->GetCapsuleTop(i), enemy->GetCapsuleBottom(i), 120.0f, enemy->GetOutflg(i));
					enemy->CheckOut(i, characterhit);
				}
			}
		}

		//�G����̃t���O
		player->CheckOut(enemy->GetPlayerhit());

		//�E���m�F
		if (player->GetOutflg() && playeroutcheck == false)
		{
			outchara.push_back(static_cast<int>(CharaNumber::Player));
		}
		if (enemy->GetPlayerhit() == true)
		{
			playeroutcheck = true;
		}
		for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
		{
			if (enemy->GetOutflg(i))
			{
				bool alreadyout = false;//���ɒE�����Ă���t���O
				for (int j = 0; j < outchara.size(); j++)
				{
					if (outchara[j] == i)//���łɒE�����Ă���ꍇ
					{
						alreadyout = true;
					}
				}
				if (alreadyout == false)
				{
					outchara.push_back(i);
				}
			}
		}

		//CPU�^�[�Q�b�g�|�W�V�����ݒ�
		for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
		{
			for (int j = 0; j < OllCharaNum; j++)
			{
				if (enemy->GetTargetNumber(i) == j)
				{
					if (j == static_cast<int>(CharaNumber::Player))
					{
						enemy->SetTargetPosition(i, player->GetPosition());
					}
					else
					{
						enemy->SetTargetPosition(i, enemy->GetPosition(j));
					}
				}
			}
		}
	}

	player->ForeverUpdate(playerattackshieldhit);
	enemy->ForeverUpdate();

	//�I�������𖞂����Ă�����t���O�ύX
	if (outchara.size() == 4)//1�l�c�����ꍇ
	{
		if (gameendflg == false)
		{
			gameendflg = true;
		}
	}
	//�I����̎���
	if (gameendflg)
	{
		gameendflame++;

		if (gameendflame == 200)
		{
			return new ResultScene();
		}
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