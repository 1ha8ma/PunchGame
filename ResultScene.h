#pragma once

class Camera;

class ResultScene
{
private:
	InputManager* input;
	Camera* camera;

	int ribbonimage;//リボン画像

	bool inputpossibleflg;//入力可能

	VECTOR winnerposition;//勝者ポジション
	float winnerangle;//勝者角度
	VECTOR targetposition;//カメラの移動する場所

	float t;//Lerp用分割割合

public:
	ResultScene();
	~ResultScene();
	void Initialize(VECTOR position,float angle);
	bool Update(Camera*& camera);
	void Draw();
};