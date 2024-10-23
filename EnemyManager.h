#pragma once
#include<vector>

class Enemy;

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;
	const float ModelSize = 4.5f;
	const VECTOR InitialPosition0 = VGet(-1000.0f, 100.0f, 1000.0f);
	const VECTOR InitialTargetDir0 = VGet(1.0f, 0.0f, -1.0f);
	const VECTOR InitialPosition1 = VGet(1000.f, 100.0f, 1000.0f);
	const VECTOR InitialTargetDir1 = VGet(-1.0f, 0.0f, -1.0f);
	const VECTOR InitialPosition2 = VGet(1000.0f, 100.0f, -700.0f);
	const VECTOR InitialTargetDir2 = VGet(-1.0f, 0.0f, 1.0f);

	bool playerhit;//プレイヤーに攻撃が当たっているか
	

public:
	//コンストラクタ
	EnemyManager();
	//デストラクタ
	~EnemyManager();
	//初期化
	void Initialize();
	//更新
	void Update(VECTOR playerpos, VECTOR playerTop, VECTOR playerBottom, VECTOR playershieldLeft, VECTOR playershieldRight, bool playeroutflg, std::vector<int> outchara);
	//終了後、脱落後も続く更新
	void ForeverUpdate();
	//描画
	void Draw();

	void CheckOut(int i, bool hit);

	//敵の数
	static const int NumberofEnemy;

	VECTOR GetPosition(int i);
	VECTOR GetCapsuleTop(int i);
	VECTOR GetCapsuleBottom(int i);
	VECTOR GetShieldLeft(int i);
	VECTOR GetShieldRight(int i);
	bool GetOutflg(int i);
	int GetTargetNumber(int i);
	void SetTargetPosition(int i, VECTOR targetpos);
	float GetAngle(int i);
	bool GetPlayerhit() { return playerhit; }
	int GetNowMoveKind(int i);
};