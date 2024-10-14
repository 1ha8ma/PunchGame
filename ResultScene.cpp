#include<math.h>
#include"DxLib.h"
#include"Camera.h"
#include"InputManager.h"
#include"ResultScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();

	ribbonimage = LoadGraph("2D/ribbon.png");
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{

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

	//ポジションを取る
	VECTOR copypos = camera->GetPosition();

	//Lerp計算
	copypos = VAdd(copypos, VScale((VSub(targetposition, copypos)), t));

	//ポジションをセット
	camera->SetPosition(copypos);

	//Lerpの分割の割合を目標に近づける
	t += 0.01;

	if (t >= 1 && inputpossibleflg && inputstate && (16 & inputstate) == 16)
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
	DrawString(130, 110, "WINNER", GetColor(255, 215, 0));
}