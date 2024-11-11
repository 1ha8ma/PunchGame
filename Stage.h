#pragma once

class Stage
{
public:
	Stage();
	void Initialize();
	void Draw();

	//ステージの各座標
	static const float StageRight;//右
	static const float StageLeft;//左
	static const float StageTop;//上
	static const float StageBottom;//下

private:
	int model;//モデル
};