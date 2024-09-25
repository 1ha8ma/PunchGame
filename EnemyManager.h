#pragma once
#include<vector>

class Enemy;

class EnemyManager
{
private:
	std::vector<Enemy*> enemy;

public:
	//コンストラクタ
	EnemyManager();
	//デストラクタ
	~EnemyManager();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();

	//敵の数
	static const int NumberofEnemy;
};