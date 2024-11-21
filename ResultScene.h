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

	float FontScalingSpeed = 1.0f;//拡大縮小スピード

	int ribbonimage;//リボン画像

	bool inputpossibleflg;//入力可能

	VECTOR winnerposition;//勝者ポジション
	float winnerangle;//勝者角度
	VECTOR targetposition;//カメラの移動する場所

	float t;//Lerp用分割割合

	int fontsize;//フォントサイズ
	int fontsizechangeflame;//フォント拡大縮小フレーム
	bool fontsizechangeflg;//フォント拡大縮小フラグ
	VECTOR explanationpos;//次のシーンへの説明のポジション
};