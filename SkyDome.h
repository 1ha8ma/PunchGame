#pragma once

class SkyDome
{
private:
	int model;

public:
	//コンストラクタ
	SkyDome();
	//デストラクタ
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
};