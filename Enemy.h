#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	int mynumber;//自分のCPU番号
	int target;//追いかける目標
	float targetdistance;//2キャラの距離
	float targetCharaAngle;//目標のキャラとの角度
	VECTOR targetPosition;//追いかける目標のポジション
	int chaseflame;//追いかけているフレーム
	float vx;
	float vz;

	bool attackaftercharachange;//攻撃後目標キャラを交代

	//攻撃のクールタイム
	bool cooltimeflg;
	int cooltimeflame;

	float moveangle;

	//ターゲット設定
	void SetTarget(std::vector<int> outchara);
	//移動処理
	void Move(std::vector<int> outchara);

public:
	//コンストラクタ
	Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDir,int cpunumber);
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(VECTOR position, VECTOR targetDir);
	//更新
	void Update(std::vector<int> outchara);

	VECTOR GetPosition() { return position; }
	int GetTarGetNumber() { return target; }
	void SetTargetPosition(VECTOR targetpos) { targetPosition = targetpos; }
	bool GetOutflg() { return outflg; }
	void SetShieldHit(bool hit) { shieldhit = hit; }
	bool GetShieldHit() { return shieldhit; }
	bool GetAttackflg() { return attackflg; }
};