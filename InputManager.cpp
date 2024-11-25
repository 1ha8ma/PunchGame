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
		inputstate |= InputNumber::Right;//0100
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT || (CheckHitKey(KEY_INPUT_LEFT)))//左
	{
		inputstate |= InputNumber::Left;//00010
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP || (CheckHitKey(KEY_INPUT_UP)))//上
	{
		inputstate |= InputNumber::Up;//01000
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN || (CheckHitKey(KEY_INPUT_DOWN)))//下
	{
		inputstate |= InputNumber::Down;//00001
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4 || (CheckHitKey(KEY_INPUT_SPACE)))//Bボタン
	{
		inputstate |= InputNumber::Decision;//10000
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_12||(CheckHitKey(KEY_INPUT_P)))//startボタン
	{
		inputstate |= InputNumber::Start;//100000
	}

	return inputstate;
}