#pragma once

class Camera
{
private:
	VECTOR pos;//カメラポジション
	VECTOR lookpos;//注視点

public:
	//コンストラクタ
	Camera();
	//初期化
	void Initialize();
	//更新
	void Update();
};