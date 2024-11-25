#include"DxLib.h"
#include"Loader.h"
#include"GameUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameUI::GameUI()
{
	Loader* loader = loader->GetInstance();
	gamepadimage = loader->GetHandle(Loader::Kind::GamePadImage);
}

/// <summary>
/// 更新
/// </summary>
void GameUI::Update()
{

}

/// <summary>
/// 描画
/// </summary>
void GameUI::Draw()
{
	DrawExtendGraph(1200, -50, 1500, 250, gamepadimage, TRUE);

	DrawLineAA(1315, 110, 1330, 170, GetColor(255, 165, 0));
	SetFontSize(40);
	DrawString(1300, 170, "移動", GetColor(255, 165, 0));
	DrawLineAA(1433, 80, 1500, 150, GetColor(255, 165, 0));
	SetFontSize(40);
	DrawString(1450, 150, "攻撃", GetColor(255, 165, 0));
	SetFontSize(40);
	DrawString(1420, 10, "一時停止", GetColor(255, 165, 0));
	DrawLineAA(1375, 67, 1470, 50, GetColor(255, 165, 0));
}