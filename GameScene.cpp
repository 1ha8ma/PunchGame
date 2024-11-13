#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Utility.h"
#include"Camera.h"
#include"Player.h"
#include"Stage.h"
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
	stage = new Stage();
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
	delete stage;
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
	////////////////////////////////////////////
	//�X�^�[�g�V�[���X�V
	///////////////////////////////////////////
	if (!gamestartflg)
	{
		gamestartflg = startscene->Update();
		camera->UpdateForStart(startscene->GetCameraPos(), startscene->GetLookPos());

		if (gamestartflg)
		{
			camera->Initialize();
		}
	}
	
	//////////////////////////////////////////
	//�Q�[�����X�V
	//////////////////////////////////////////
	if (gamestartflg && !gameendflg)
	{
		//�G�t�F�N�g�J��������
		Effekseer_Sync3DSetting();

		//�X�V
		bgmmanager->PlayBGM(BGMManager::BGMKind::GameBGM);
		camera->UpdateForGame();
		if (!player->GetOutflg())
		{
			player->Update(input->GetInputState());
		}
		enemy->Update(outchara);

		//���ǂ����̓����蔻��
		for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
		{
			//�������Ă�����
			if (player->ShieldWithShield(player->GetShieldLeft(), player->GetShieldRight(), enemy->GetShieldLeft(i), enemy->GetShieldRight(i)))
			{
				player->RemoveShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i));
			}
		}
		enemy->UpdateShieldWithShield(player->GetShieldLeft(), player->GetShieldRight());

		//�|�W�V�������f
		player->ReflectPosition();
		enemy->ReflectPosition();

		//���Ə��̓����蔻��
		if (!player->GetOutflg())
		{
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				playerattackshieldhit = false;
				if (player->FistWithShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i)))
				{
					playerattackshieldhit = true;
					break;
				}
			}
			player->SetShieldHit(playerattackshieldhit);
			player->PlayShieldHitSE(playerattackshieldhit);
		}
		enemy->UpdateFistWithShield(player->GetShieldLeft(), player->GetShieldRight());

		//���ƃL�����N�^�[�����蔻��
		if (!player->GetOutflg())
		{
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				bool characterhit;
				characterhit = player->FistWithCharacter(enemy->GetCapsuleTop(i), enemy->GetCapsuleBottom(i), enemy->GetOutflg(i));
				enemy->CheckOut(i, characterhit);
			}
		}
		enemy->UpdateFistWithCharacter(player->GetPositioncapsuleTop(), player->GetPositioncapsuleBotoom(), player->GetOutflg());

		//�G����̃t���O
		player->CheckOut(enemy->GetPlayerhit());

		//�E���m�F
		if (player->GetOutflg() && !playeroutcheck)
		{
			outchara.push_back(static_cast<int>(CharaNumber::Player));
		}
		if (enemy->GetPlayerhit())
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
				if (!alreadyout)
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
							enemy->SetTargetCharaPosition(i, player->GetPosition());
							enemy->SetTargetCharaAngle(i, player->GetAngle());
						}
						else
						{
							enemy->SetTargetCharaPosition(i, enemy->GetPosition(j));
							enemy->SetTargetCharaAngle(i, enemy->GetAngle(j));
						}
					}
				}
			}
		}
	}

	//�Q�[�����ƃ��U���g�X�V
	if (gamestartflg)
	{
		player->ForeverUpdate();
		enemy->ForeverUpdate();

		UpdateEffekseer3D();
	}

	//�I�������𖞂����Ă�����t���O�ύX
	if (outchara.size() == 4)//1�l�c�����ꍇ
	{
		if (!gameendflg)
		{
			//���҂̏����擾
			if (!player->GetOutflg())
			{
				winnerpos = player->GetPosition();
				winnerangle = player->GetAngle();
				winnernumber = static_cast<int>(CharaNumber::Player);
			}
			for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
			{
				if (!enemy->GetOutflg(i))
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

	/////////////////////////////////////////
	//���U���g
	////////////////////////////////////////
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
	stage->Draw();
	player->Draw();
	enemy->Draw();

	if (!gamestartflg)
	{
		startscene->Draw();
	}
	if (gamestartflg && !gameendflg)
	{
		gameui->Draw();
	}
	if (gameendflg)
	{
		resultscene->Draw();
	}
}