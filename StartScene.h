#pragma once
#include<vector>

class StartScene
{
private:

	std::vector<int> image;
	/*int image1;
	int image2;
	int image3;*/
	int startimage;

	float cameraangle;
	VECTOR lookpos;
	VECTOR camerapos;

	int count;
	bool countflg;
	int countflame;

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