#include"DxLib.h"
#include"InputManager.h"
#include"TitleScene.h"
#include"ResultScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
	input = new InputManager();

	Initialize();
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
void ResultScene::Initialize()
{
	inputpossibleflg = false;
}

/// <summary>
/// 更新
/// </summary>
/// <returns>次のシーン</returns>
SceneBase* ResultScene::Update()
{
	int inputstate = input->GetInputState();

	if (inputstate == 0)
	{
		inputpossibleflg = true;
	}

	if (inputpossibleflg && (16 & inputstate) == 16)//Bボタン
	{
		return new TitleScene();
	}

	//条件を満たしていなければ
	return this;
}

/// <summary>
/// 描画
/// </summary>
void ResultScene::Draw()
{
	SetFontSize(64);
	DrawString(600, 500, "RESULT", GetColor(130, 155, 211));
}