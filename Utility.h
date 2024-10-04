#pragma once

//画面サイズ
const int SCREEN_W = 1600;
const int SCREEN_H = 900;

//キャラクターナンバー
enum class CharaNumber :int
{
	CPU0 = 0,
	CPU1 = 1,
	CPU2 = 2,
	Player = 3,
};

const float AngleSpeed = 0.2f;//角度変更速度