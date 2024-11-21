#include"DxLib.h"
#include"InputManager.h"

/// <summary>
/// 入力状態ゲッター
/// </summary>
/// <returns>入力状態</returns>
int InputManager::GetInputState()
{
	int inputstate = 0;

	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) || (CheckHitKey(KEY_INPUT_RIGHT)))//右
	{
		inputstate |= 4;//0100
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT || (CheckHitKey(KEY_INPUT_LEFT)))//左
	{
		inputstate |= 2;//00010
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP || (CheckHitKey(KEY_INPUT_UP)))//上
	{
		inputstate |= 8;//01000
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN || (CheckHitKey(KEY_INPUT_DOWN)))//下
	{
		inputstate |= 1;//00001
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_SPACE)))//Bボタン
	{
		inputstate |= 16;//10000
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_12||(CheckHitKey(KEY_INPUT_P)))//startボタン
	{
		inputstate |= 32;//100000
	}

	return inputstate;
}