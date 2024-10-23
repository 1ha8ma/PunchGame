#include"DxLib.h"
#include"Utility.h"
#include"Camera.h"
#include"Player.h"
#include"WoodBoard.h"
#include"SkyDome.h"
#include"InputManager.h"
#include"Enemy.h"
#include"EnemyManager.h"
#include"GameUI.h"
#include"BGMManager.h"
#include"SEManager.h"
#include"ResultScene.h"
#include"TitleScene.h"
#include"StartScene.h"
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
	gameui = new GameUI();
	resultscene = new ResultScene();
	startscene = new StartScene();
	bgmmanager = new BGMManager();
	semanager = new SEManager();

	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	delete camera;
	delete input;
	delete skydome;
	delete wood;
	delete player;
	delete enemy;
	delete resultscene;
	delete startscene;
	delete gameui;

	bgmmanager->StopBGM();
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	camera->GamestartInitialize();
	gamestartflg = false;
	gameendflg = false;
	playeroutcheck = false;
	playerattackshieldhit = false;
	scenechange = false;
	outchara.clear();
	outchara.push_back(-1);
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	//�X�^�[�g�V�[���X�V
	if (gamestartflg == false)
	{
		gamestartflg = startscene->Update();
		camera->UpdateForStart(startscene->GetCameraPos(), startscene->GetLookPos());

		if (gamestartflg)
		{
			camera->Initialize();
		}
	}
	
	//�X�V
	if (gamestartflg && gameendflg == false)
	{
		bgmmanager->PlayBGM(BGMManager::BGMKind::GameBGM);
		camera->UpdateForGame();
		if (player->GetOutflg() == false)
		{
			player->Update(input->GetInputState());
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
			player->PlayShieldHitSE(playerattackshieldhit);
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
			if (enemy->GetNowMoveKind(i) == Enemy::MoveKind::charachase)//�L������ǂ���Ԃ������ꍇ
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
	}

	if (gamestartflg)
	{
		player->ForeverUpdate(playerattackshieldhit);
		enemy->ForeverUpdate();
	}

	//�I�������𖞂����Ă�����t���O�ύX
	if (outchara.size() == 4)//1�l�c�����ꍇ
	{
		if (gameendflg == false)
		{
			//���҂̏����擾
			if (player->GetOutflg() == false)
			{
				winnerpos = player->GetPosition();
				winnerangle = player->GetAngle();
				winnernumber = static_cast<int>(CharaNumber::Player);
			}
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				if (enemy->GetOutflg(i) == false)
				{
					winnerpos = enemy->GetPosition(i);
					winnerangle = enemy->GetAngle(i);
					winnernumber = i;
					break;
				}
			}
			//�Q�[��BGM�X�g�b�v
			bgmmanager->StopBGM();
			resultscene->Initialize(winnerpos, winnerangle);
			gameendflg = true;
		}
	}
	//�I����̎���
	if (gameendflg)
	{
		camera->UpdateForResult(winnerpos, winnernumber);
		scenechange = resultscene->Update(camera);

		if (scenechange)
		{
			semanager->PlaySE(SEManager::SEKind::CrickSE);
			return new TitleScene();
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

	if (gamestartflg == false)
	{
		startscene->Draw();
	}
	if (gamestartflg && gameendflg == false)
	{
		gameui->Draw();
	}
	if (gameendflg)
	{
		resultscene->Draw();
	}
}