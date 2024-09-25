#pragma once
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	float targetdistance;//2キャラの距離
	float targetCharaAngle;//目標のキャラとの角度
	VECTOR targetCharaPos;//追いかける目標のポジション
	float vx;
	float vz;

	//移動処理
	void Move();

	//攻撃開始処理
public:
	//コンストラクタ
	Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDir);
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(VECTOR position, VECTOR targetDir);
	//近くのキャラクターを確認
	void CheckNearCharacter(VECTOR charapos);
	//更新
	void Update();

	VECTOR GetPosition() { return position; }
};