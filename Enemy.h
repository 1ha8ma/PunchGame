#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
public:
	//cpuの動きの種類
	enum MoveKind
	{
		charachase,//キャラを追う
		randomwalk,//ランダムに歩く
	};

	//コンストラクタ
	Enemy(int handle, float modelsize, VECTOR position, VECTOR targetDir, int cpunumber);
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize(VECTOR position, VECTOR targetDir);
	//更新
	void Update(std::vector<int> outchara);
	//盾と盾の当たり判定の更新
	void UpdateShieldWithShield(VECTOR shieldleft, VECTOR shieldright);
	//ポジションの更新
	void UpdatePosition();
	//終了後も更新
	void ForeverUpdate();

	//Get,Set
	VECTOR GetPosition() { return position; }
	int GetTarGetNumber() { return target; }
	void SetTargetCharaPosition(VECTOR targetcharapos) { targetCharaPosition = targetcharapos; }
	void SetTargetCharaAngle(float targetcharaangle) { targetCharaAngle = targetcharaangle; }
	bool GetOutflg() { return outflg; }
	bool GetAttackflg() { return attackflg; }
	int GetNowMoveKind() { return NowMoveKind; }

private:
	const int Range = 1000;//射程範囲

	int mynumber;//自分のCPU番号

	//移動関係
	int NowMoveKind;//現在の動きかた
	bool moveonflg;//動くかどうかフラグ
	VECTOR targetPosition;
	VECTOR targetCharaPosition;//追いかける目標のポジション
	float targetCharaAngle;//追いかける目標の角度
	int moveflame;//移動開始からのフレーム
	float moveangle;//動く方向

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
};