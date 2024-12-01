#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//インスタンスゲット

	/// <summary>
	/// モデル等のデータの種類
	/// </summary>
	enum Kind
	{
		//3D
		PlayerModel,//プレイヤーモデル
		Enemy1Model,//敵1モデル
		Enemy2Model,//2
		Enemy3Model,//3
		ShieldModel,//盾モデル
		FistModel,//拳モデル
		StageModel,//ステージモデル
		DomeModel,//スカイドームモデル

		//2D
		TitleLogo,//タイトルロゴ
		RibbonImage,//リボン画像
		GamePadImage,//ゲームパッド画像
		StartImage,//スタート画像
		NumImage1,//1画像
		NumImage2,//2
		NumImage3,//3
		TextBoxImage,//テキストボックス
		PlayerArrowImage,//プレイヤー矢印画像
		ButtonImage,//ボタン(未選択)
		BUttonHoverImage,//ボタン(選択)

		//エフェクト
		LasthitEffect,//プレイヤー衝突エフェクト
		PunchfiringEffect,//パンチしたときのエフェクト
		ShieldhitEffect,//盾衝突時のエフェクト
		BlowEffect,//キャラ吹っ飛びエフェクト

		//BGM
		TitleBGM,//タイトルBGM
		GameBGM,//ゲーム中BGM
		ResultBGM,//リザルトBGM

		//SE
		StartSceneSE,//スタート演出SE
		StartSE,//スタート表示のSE
		CountSE,//カウントSE
		ShieldHitSE,//盾衝突SE
		CharacterHitSE,//キャラクターに当たった時のSE
		AttackSE,//攻撃時SE
		CrickSE,//決定SE
		CursorMoveSE,//カーソル移動SE
		CursorSelectSE,//カーソル決定SE
		OpenPauseSE,//一時停止を開いたときのSE
	};

	//ハンドルマップゲット
	int GetHandle(Kind kind) { return handle[kind]; }
	//モデル等をロード
	void LoadModel();

private:
	static Loader* loader_;//ローダークラスインスタンス
	//ハンドル持ちマップ
	std::map<Kind, int> handle;

};