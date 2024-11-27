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
#include"Pause.h"
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
	pausescene = new Pause();
	resultscene = new ResultScene();
	startscene = new StartScene(player->GetPosition());
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
	delete pausescene;

	bgmmanager->StopBGM();
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	camera->GamestartInitialize();
	playeroutcheck = false;
	scenechange = false;
	outchara.clear();
	outchara.push_back(-1);

	outpauseinputflg = false;

	nowstate = GameSceneState::start;
}

/// <summary>
/// �X�V
/// </summary>
/// <returns>���̃V�[��</returns>
SceneBase* GameScene::Update()
{
	switch (nowstate)
	{
	case (GameSceneState::start):
	{
		bool gamestartflg = startscene->Update();
		camera->UpdateForStart(startscene->GetCameraPos(), startscene->GetLookPos());

		if (gamestartflg)
		{
			camera->Initialize();
			nowstate = GameSceneState::game;
		}
	}
	break;
	case (GameSceneState::game):
	{
		//�G�t�F�N�g�J��������
		Effekseer_Sync3DSetting();

		//�ꎞ��~������̘A�����͖h�~
		if (outpauseinputflg && !((InputManager::InputNumber::BButton & input->GetInputState()) == InputManager::InputNumber::BButton))
		{
			outpauseinputflg = false;
		}

		//�X�V
		bgmmanager->PlayBGM(BGMManager::BGMKind::GameBGM);
		camera->UpdateForGame();
		if (!player->GetOutflg())
		{
			player->Update(input->GetInputState(),outpauseinputflg);
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
			bool playerattackshieldhit;

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

		//�Q�[�����ƃ��U���g�X�V
		player->ForeverUpdate(false);
		enemy->ForeverUpdate(false);
		UpdateEffekseer3D();

		//�I�������𖞂����Ă�����t���O�ύX
		if (outchara.size() == 4)//1�l�c�����ꍇ
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

			//�X�e�[�g�ύX
			nowstate = GameSceneState::result;
		}
		//�ꎞ��~
		if (pauseinputpossible && (InputManager::InputNumber::Start & input->GetInputState()) == InputManager::InputNumber::Start)
		{
			semanager->PlaySE(SEManager::SEKind::OpenPauseSE);
			pausescene->Initialize();
			nowstate = GameSceneState::pause;
		}
		if (!((InputManager::InputNumber::Start & input->GetInputState()) == InputManager::InputNumber::Start))
		{
			pauseinputpossible = true;
		}
		else
		{
			pauseinputpossible = false;
		}
		
	}
	break;
	case(GameSceneState::pause):
	{
		int out = pausescene->Update();

		if (out == Pause::CursorPoint::GameReturn)
		{
			nowstate = GameSceneState::game;
			outpauseinputflg = true;
		}
		if (out == Pause::CursorPoint::TitleReturn)
		{
			return new TitleScene();
		}
	}
	break;

	case(GameSceneState::result):
	{
		//�G�t�F�N�g�J��������
		Effekseer_Sync3DSetting();

		camera->UpdateForResult(winnerpos, winnernumber, resultscene->GetFlame());
		scenechange = resultscene->Update(camera);

		player->ForeverUpdate(true);
		enemy->ForeverUpdate(true);
		UpdateEffekseer3D();

		if (scenechange)
		{
			semanager->PlaySE(SEManager::SEKind::CrickSE);
			return new TitleScene();
		}
	}
	break;

	default:
		break;
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

	switch (nowstate)
	{
	case(GameSceneState::start):
	{
		startscene->Draw();
	}
	break;
	case(GameSceneState::game):
	{
		gameui->Draw();
	}
	break;
	case(GameSceneState::pause):
	{
		pausescene->Draw();
	}
	break;
	case(GameSceneState::result):
	{
		resultscene->Draw();
	}
	break;

	default:
		break;
	}
}