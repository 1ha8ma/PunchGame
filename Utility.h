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

const int OllCharaNum = 4;//総人数

//ステージの各座標
const float StageRight = 1600.0f;//右
const float StageLeft = -1500.0f;//左
const float StageTop = 1500.0f;//上
const float StageBottom = -1000.0f;//下