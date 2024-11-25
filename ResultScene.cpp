#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"InputManager.h"
#include"Loader.h"
#include"BGMManager.h"
#include"ResultScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();
	bgmmanager = new BGMManager();
	Loader* loader = loader->GetInstance();

	ribbonimage = loader->GetHandle(Loader::Kind::RibbonImage);
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	bgmmanager->StopBGM();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="position">勝者ポジション</param>
/// <param name="angle">勝者角度</param>
void ResultScene::Initialize(VECTOR position, float angle)
{
	inputpossibleflg = false;
	t = 0;

	winnerposition = position;
	winnerangle = angle;

	targetposition.x = winnerposition.x + sin(winnerangle) * 1000;
	targetposition.z = winnerposition.z + cos(winnerangle) * 1000;
	targetposition.y = winnerposition.y + 500;

	flame = 0;

	fontsize = 64;
	fontsizechangeflame = 0;
	fontsizechangeflg = false;
	explanationpos = VGet(1100, 750, 0);
}

/// <summary>
/// 更新
/// </summary>
bool ResultScene::Update(Camera*& camera)
{
	int inputstate = input->GetInputState();
	bool scenechange = false;

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	//BGM再生
	bgmmanager->PlayBGM(BGMManager::BGMKind::ResultBGM);

	//ポジションを取る
	VECTOR copypos = camera->GetPosition();
	if (flame < 130)
	{
		copypos.x = winnerposition.x + sin(winnerangle + DX_PI_F / 2) * 1400;
		copypos.z = winnerposition.z + cos(winnerangle + DX_PI_F / 2) * 1400;
		copypos.y = winnerposition.y + 1200;
	}
	else if (130 <= flame && flame <= 260)
	{
		copypos.x = winnerposition.x + sin(winnerangle - DX_PI_F / 2) * 1400;
		copypos.z = winnerposition.z + cos(winnerangle - DX_PI_F / 2) * 1400;
		copypos.y = winnerposition.y + 1200;
	}
	else
	{
		//Lerp計算
		copypos = VAdd(copypos, VScale((VSub(targetposition, copypos)), t));
		//Lerpの分割の割合を目標に近づける
		t += 0.005;
	}

	//ポジションをセット
	camera->SetPosition(copypos);

	//フレーム加算
	flame++;

	//目的地にカメラが到着したら
	if (t >= 1)
	{
		//フォントサイズ更新
		fontsizechangeflame++;

		if (fontsizechangeflame != 0 && fontsizechangeflame % 30 == 0)
		{
			//拡大縮小交代
			if (fontsizechangeflg)
			{
				fontsizechangeflg = false;
			}
			else
			{
				fontsizechangeflg = true;
			}

			fontsizechangeflame = 0;
		}

		if (fontsizechangeflg)//縮小
		{
			fontsize -= FontScalingSpeed;
			explanationpos.x += FontScalingSpeed;
			explanationpos.y += FontScalingSpeed;
		}
		else//拡大
		{
			fontsize += FontScalingSpeed;
			explanationpos.x -= FontScalingSpeed;
			explanationpos.y -= FontScalingSpeed;
		}
	}

	//決定でシーン変更
	if (t >= 1 && inputpossibleflg && inputstate && (InputManager::InputNumber::Decision & inputstate) == InputManager::InputNumber::Decision)
	{
		scenechange = true;
	}

	return scenechange;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
	DrawGraph(0, -100, ribbonimage, TRUE);
	SetFontSize(64);
	DrawString(150, 110, "WINNER", GetColor(255, 215, 0));

	if (t >= 1)
	{
		SetFontSize(fontsize);
		DrawString(explanationpos.x, explanationpos.y, "A タイトル", GetColor(127, 255, 0));
	}
}