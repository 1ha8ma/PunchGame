#pragma once

class SceneBase;

class GameManager
{
private:
	//シーン
	SceneBase* nowscene;
	SceneBase* nextscene;

	//シーン切り替え
	void ChangeScene();

public:
	//コンストラクタ
	GameManager();
	//更新
	void Update();
	//描画
	void Draw();
};