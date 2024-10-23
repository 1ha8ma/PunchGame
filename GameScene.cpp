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
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
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
/// デストラクタ
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
/// 初期化
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
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	//スタートシーン更新
	if (gamestartflg == false)
	{
		gamestartflg = startscene->Update();
		camera->UpdateForStart(startscene->GetCameraPos(), startscene->GetLookPos());

		if (gamestartflg)
		{
			camera->Initialize();
		}
	}
	
	//更新
	if (gamestartflg && gameendflg == false)
	{
		bgmmanager->PlayBGM(BGMManager::BGMKind::GameBGM);
		camera->UpdateForGame();
		if (player->GetOutflg() == false)
		{
			player->Update(input->GetInputState());
		}
		enemy->Update(player->GetPosition(), player->GetPositioncapsuleTop(), player->GetPositioncapsuleBotoom(), player->GetShieldLeft(), player->GetShieldRight(), player->GetOutflg(), outchara);

		//盾との当たり判定
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

		//当たり判定
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

		//敵からのフラグ
		player->CheckOut(enemy->GetPlayerhit());

		//脱落確認
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
				bool alreadyout = false;//既に脱落しているフラグ
				for (int j = 0; j < outchara.size(); j++)
				{
					if (outchara[j] == i)//すでに脱落している場合
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

		//CPUターゲットポジション設定
		for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
		{
			if (enemy->GetNowMoveKind(i) == Enemy::MoveKind::charachase)//キャラを追う状態だった場合
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

	//終了条件を満たしていたらフラグ変更
	if (outchara.size() == 4)//1人残った場合
	{
		if (gameendflg == false)
		{
			//勝者の情報を取得
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
			//ゲームBGMストップ
			bgmmanager->StopBGM();
			resultscene->Initialize(winnerpos, winnerangle);
			gameendflg = true;
		}
	}
	//終了後の時間
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

	//もし終了条件を満たしていなかったら
	return this;
}

/// <summary>
/// 描画
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