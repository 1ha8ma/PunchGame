#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Loader.h"
#include"SEManager.h"
#include"StartScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
StartScene::StartScene()
{
	Loader* loader = loader->GetInstance();

	image.clear();
	image.push_back(loader->GetHandle(Loader::Kind::NumImage1));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage2));
	image.push_back(loader->GetHandle(Loader::Kind::NumImage3));
	startimage = loader->GetHandle(Loader::Kind::StartImage);

	semanager = new SEManager();
	semanager->PlaySE(SEManager::SEKind::StartSceneSE);

	Initialize();
}

/// <summary>
/// 初期化
/// </summary>
void StartScene::Initialize()
{
	countflg = false;
	countflame = 0;
	cameraangle = 0.0f;
	lookpos = VGet(0, 600, 0);
	count = 3;
	sizechangeflg = false;
	sizechangeflame = 0;
	startseflg = false;

	//ポジション
	numberlx = 800;
	numberly = 400;
	numberrx = 859;
	numberry = 480;
}

/// <summary>
/// 更新
/// </summary>
bool StartScene::Update()
{
	bool scenechange = false;

	//見回す
	if (countflg == false)
	{
		cameraangle += 0.009f;
		camerapos = VGet(0, 600, 0);
		lookpos.x = sin(cameraangle);
		lookpos.z = cos(cameraangle);
	}


	//一周したら
	if (cameraangle >= DX_PI_F * 2 && countflg == false)
	{
		semanager->PlaySE(SEManager::SEKind::StartCountSE);
		countflg = true;
	}

	//カウントに入ったら
	if (countflg)
	{
		cameraangle = 0.0f;
		camerapos = VGet(0, 2000, -1500);
		lookpos = VGet(0, 0, 0);

		countflame++;
	}

	if (countflg && countflame == 350)
	{
		scenechange = true;
	}

	return scenechange;
}

/// <summary>
/// 描画
/// </summary>
void StartScene::Draw()
{
	if (countflg)
	{
		//100フレーム毎に画像切り替え
		if (countflame != 0 && countflame % 100 == 0)
		{
			sizechangeflame = 0;
			sizechangeflg = false;
			numberlx = 800;
			numberly = 400;
			numberrx = 859;
			numberry = 480;
			if (count >= 2)
			{
				semanager->PlaySE(SEManager::SEKind::StartCountSE);
			}
			count--;
		}

		//サイズの変更フラグ
		if (sizechangeflame % 50 == 0 && sizechangeflame % 100 != 0)
		{
			sizechangeflg = true;
		}

		//数字のサイズ変更
		if (sizechangeflg == false)
		{
			numberlx -= 1;
			numberly -= 1;
			numberrx += 1;
			numberry += 1;
		}
		else
		{
			numberlx += 1;
			numberly += 1;
			numberrx -= 1;
			numberry -= 1;
		}	

		//数字カウント
		if (count >= 1)
		{
			DrawExtendGraph(numberlx, numberly, numberrx, numberry, image[count - 1], TRUE);
		}

		//スタート
		if (300 < countflame && countflame <= 350)
		{
			if (startseflg == false)
			{
				semanager->PlaySE(SEManager::SEKind::StartSE);
				startseflg = true;
			}
			DrawGraph(650, 370, startimage, TRUE);
		}

		sizechangeflame++;
	}
}