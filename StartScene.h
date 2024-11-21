#pragma once
#include<vector>

class SEManager;

class StartScene
{
public:
	//コンストラクタ
	StartScene(VECTOR playerpos);
	//初期化
	void Initialize(VECTOR playerpos);
	//更新
	bool Update();
	//描画
	void Draw();

	VECTOR GetLookPos() { return lookpos; }
	VECTOR GetCameraPos() { return camerapos; }

private:
	SEManager* semanager;

	const float ScalingSpeed = 1.0f;//文字拡大縮小速度

	//カウントダウン画像
	std::vector<int> image;
	int startimage;

	//テキストボックス画像
	int textbox;
	
	//プレイヤー矢印画像
	int playerarrow;
	VECTOR playerarrowpos;

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
};