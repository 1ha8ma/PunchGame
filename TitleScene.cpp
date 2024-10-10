#include"DxLib.h"
#include"InputManager.h"
#include"GameScene.h"
#include"TitleScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
	input = new InputManager();

	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	inputpossibleflg = false;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* TitleScene::Update()
{
	int inputstate = input->GetInputState();

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (16 & inputstate) == 16)//Bボタン
	{
		return new GameScene();
	}

	return this;
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Draw()
{
	SetFontSize(64);
	DrawString(600, 500, "TITLE", GetColor(190, 155, 211));
}