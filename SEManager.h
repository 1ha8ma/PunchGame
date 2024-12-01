#pragma once
#include<map>

class SEManager
{
public:
	enum SEKind
	{
		CharahitSE,//キャラに攻撃が当たった時
		ShieldhitSE,//盾で防いだ時
		AttackSE,//攻撃時
		StartCountSE,//カウントse
		StartSceneSE,//スタート演出の時のse
		StartSE,//スタート表示のse
		CrickSE,//決定ボタンを押したとき
		WinnerSE,//リザルトでの勝者が出てきた時のSE
		CursorMoveSE,//カーソル移動SE
		CursorSelectSE,//カーソル決定SE
		OpenPauseSE,//一時停止を開いたときのSE
	};

	//コンストラクタ
	SEManager();

	//再生
	void PlaySE(SEKind kind);
	//特定のSEを終了
	void StopSE(SEKind kind);

private:
	std::map<SEKind, int> handle;

};