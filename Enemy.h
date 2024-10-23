#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	int mynumber;//自分のCPU番号

	//移動関係
	int NowMoveKind;//現在の動きかた
	bool moveonflg;//動くかどうかフラグ
	VECTOR targetPosition;//追いかける目標のポジション
	int moveflame;//追いかけているフレーム
	float moveangle;//動く方向
	//移動速度
	float vx;
	float vz;

	//キャラ追い関係
	int target;//追いかける目標
	float targetdistance;//2キャラの距離

	//ランダム歩き関係
	bool SetWalkTargetPositionflg;

	//攻撃のクールタイム
	bool cooltimeflg;
	int cooltimeflame;

	//ターゲット設定
	void SetTargetChara(std::vector<int> outchara);
	//移動処理
	void Move(std::vector<int> outchara);

public:
	enum MoveKind
	{
		charachase,//キャラを追う
		randomwalk,//ランダムに歩く
	};
	
	//コンストラクタ
	Enemy(int handle,float modelsize,VECTOR position,VECTOR targetDir,int cpunumber);
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
	int GetNowMoveKind() { return NowMoveKind; }
};