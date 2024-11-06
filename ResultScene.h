#pragma once

class Camera;
class BGMManager;

class ResultScene
{
public:
	ResultScene();
	~ResultScene();
	void Initialize(VECTOR position, float angle);
	bool Update(Camera*& camera);
	void Draw();

private:
	InputManager* input;
	Camera* camera;
	BGMManager* bgmmanager;

	int ribbonimage;//リボン画像

	bool inputpossibleflg;//入力可能

	VECTOR winnerposition;//勝者ポジション
	float winnerangle;//勝者角度
	VECTOR targetposition;//カメラの移動する場所

	float t;//Lerp用分割割合
};