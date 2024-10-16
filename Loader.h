#pragma once
#include<map>

class Loader
{
public:
	static Loader* GetInstance();//インスタンスゲット

	enum Kind
	{
		//3D
		PlayerModel,//プレイヤーモデル
		Enemy1Model,//敵1モデル
		Enemy2Model,//2
		Enemy3Model,//3
		ShieldModel,//盾モデル
		FistModel,//拳モデル
		WoodBoardModel,//木の板モデル
		DomeModel,//スカイドームモデル

		//2D
		TitleLogo,//タイトルロゴ
		RibbonImage,//リボン画像
		GamePadImage,//ゲームパッド画像
		StartImage,//スタート画像
		NumImage1,//1画像
		NumImage2,//2
		NumImage3,//3

		//エフェクト
		PlayerhitEffect,//プレイヤー衝突エフェクト
		PunchfiringEffect,//パンチしたときのエフェクト
		ShieldhitEffect,//盾衝突時のエフェクト
	};

	//ハンドルマップゲット
	int GetHandle(Kind kind) { return handle[kind]; }
	void LoadModel();


private:
	static Loader* loader_;//ローダークラスインスタンス
	//ハンドル持ちマップ
	std::map<Kind, int> handle;

	//3D
	//static int PlayerModel;//プレイヤーモデル
	//static int Enemy1Model;//敵1モデル
	//static int Enemy2Model;//2
	//static int Enemy3Model;//3
	//static int ShieldModel;//盾モデル
	//static int FistModel;//拳モデル
	//static int WoodBoardModel;//木の板モデル
	//static int DomeModel;//スカイドームモデル

	//2D
	/*static int TitleLogo;
	static int RibbonImage;
	static int GamePadImage;
	static int StartImage;
	static int NumImage1;
	static int NumImage2;
	static int NumImage3;*/

	//エフェクト
	/*static int PlayerhitEffect;
	static int PunchfiringEffect;
	static int ShieldhitEffect;*/

};