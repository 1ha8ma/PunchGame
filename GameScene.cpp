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
/// コンストラクタ
/// </summary>
GameScene::GameScene()
{
	//インスタンス化
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
/// デストラクタ
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
	////////////////////////////////////////////
	//スタートシーン更新
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
	//ゲーム中更新
	//////////////////////////////////////////
	if (gamestartflg && !gameendflg)
	{
		//エフェクトカメラ同期
		Effekseer_Sync3DSetting();

		//更新
		bgmmanager->PlayBGM(BGMManager::BGMKind::GameBGM);
		camera->UpdateForGame();
		if (!player->GetOutflg())
		{
			player->Update(input->GetInputState());
		}
		enemy->Update(outchara);

		//盾どうしの当たり判定
		for (int i = 0; i < EnemyManager::NumberofEnemy; i++)
		{
			//当たっていたら
			if (player->ShieldWithShield(player->GetShieldLeft(), player->GetShieldRight(), enemy->GetShieldLeft(i), enemy->GetShieldRight(i)))
			{
				player->RemoveShield(enemy->GetShieldLeft(i), enemy->GetShieldRight(i));
			}
		}
		enemy->UpdateShieldWithShield(player->GetShieldLeft(), player->GetShieldRight());

		//ポジション反映
		player->ReflectPosition();
		enemy->ReflectPosition();

		//拳と盾の当たり判定
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

		//拳とキャラクター当たり判定
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

		//敵からのフラグ
		player->CheckOut(enemy->GetPlayerhit());

		//脱落確認
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
				bool alreadyout = false;//既に脱落しているフラグ
				for (int j = 0; j < outchara.size(); j++)
				{
					if (outchara[j] == i)//すでに脱落している場合
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

	//ゲーム中とリザルト更新
	if (gamestartflg)
	{
		player->ForeverUpdate();
		enemy->ForeverUpdate();

		UpdateEffekseer3D();
	}

	//終了条件を満たしていたらフラグ変更
	if (outchara.size() == 4)//1人残った場合
	{
		if (!gameendflg)
		{
			//勝者の情報を取得
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
			//ゲームBGMストップ
			bgmmanager->StopBGM();
			resultscene->Initialize(winnerpos, winnerangle);
			gameendflg = true;
		}
	}

	/////////////////////////////////////////
	//リザルト
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

	//もし終了条件を満たしていなかったら
	return this;
}

/// <summary>
/// 描画
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