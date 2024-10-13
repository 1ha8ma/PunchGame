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

	playerattackshieldhit = false;
	outchara.push_back(-1);
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	int a = 0;
}

/// <summary>
/// 初期化
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
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* GameScene::Update()
{
	//更新
	if (gameendflg == false)
	{
		if (player->GetOutflg() == false)
		{
			player->Update(input->GetInputState(), playerattackshieldhit);
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

	//終了条件を満たしていたらフラグ変更
	if (outchara.size() == 4)//1人残った場合
	{
		if (gameendflg == false)
		{
			gameendflg = true;
		}
	}
	//終了後の時間
	if (gameendflg)
	{
		gameendflame++;

		if (gameendflame == 200)
		{
			return new ResultScene();
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
}