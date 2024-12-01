#pragma once

class UI
{
public:
	//コンストラクタ
	UI();
	//更新
	void Update();
	//操作説明描画
	void DrawOperationExplanation();

private:
	int gamepadimage;//ゲームパッド画像
};