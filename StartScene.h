#pragma once
#include<vector>

class SEManager;

class StartScene
{
private:
	SEManager* semanager;

	//カウントダウン画像
	std::vector<int> image;
	int startimage;

	//テキストボックス画像
	int textbox;

	//カメラ関係
	float cameraangle;
	VECTOR lookpos;
	VECTOR camerapos;

	//カウント関係
	int count;
	bool countflg;
	int countflame;
	bool startseflg;

	//数字画像位置
	bool sizechangeflg;
	int sizechangeflame;
	float numberlx;
	float numberly;
	float numberrx;
	float numberry;

public:
	//コンストラクタ
	StartScene();
	//初期化
	void Initialize();
	//更新
	bool Update();
	//描画
	void Draw();

	VECTOR GetLookPos() { return lookpos; }
	VECTOR GetCameraPos() { return camerapos; }
};