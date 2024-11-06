#pragma once

class Camera
{
public:
	//コンストラクタ
	Camera();
	//初期化
	void Initialize();
	//ゲーム開始時初期化
	void GamestartInitialize();
	//ゲームスタート更新
	void UpdateForStart(VECTOR position, VECTOR lookpos);
	//ゲーム中更新
	void UpdateForGame();
	//タイトル中更新
	void UpdateForTitle();
	//リザルト更新
	void UpdateForResult(VECTOR winnerpos, int winnernumber);

	VECTOR GetPosition() { return pos; }
	void SetPosition(VECTOR newpos) { pos = newpos; }

private:
	VECTOR pos;//カメラポジション
	VECTOR lookpos;//注視点

	float angle;//回転の角度
	const float initangle = -2.0f;//最初の角度
};