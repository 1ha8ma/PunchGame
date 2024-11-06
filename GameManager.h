#pragma once

class SceneBase;

class GameManager
{
public:
	//コンストラクタ
	GameManager();
	//更新
	void Update();
	//描画
	void Draw();

private:
	//シーン
	SceneBase* nowscene;
	SceneBase* nextscene;

	//シーン切り替え
	void ChangeScene();
};