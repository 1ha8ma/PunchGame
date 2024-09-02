#pragma once

class SceneBase
{
private:
public:
	//コンストラクタ
	SceneBase();
	//デストラクタ
	virtual ~SceneBase() {};
	//初期化
	static SceneBase* InitializeBase();
	//シーンごとの初期化
	virtual void Initialize() abstract;
	//シーンごとの更新
	virtual SceneBase* Update() abstract;
	//シーンごとの描画
	virtual void Draw() abstract;
};