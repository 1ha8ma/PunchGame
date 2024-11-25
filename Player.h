#pragma once
#include"CharacterBase.h"

class Player :public CharacterBase
{
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
	//初期化
	void Initialize();
	//更新
	void Update(int inputstate,bool outpauseinputflg);

	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }
	bool GetAttackflg() { return attackflg; }

private:
	//入力処理
	void InputProcess(const int inputstate,bool outpauseinputflg);

	bool attackinputpossible;//攻撃の連続入力防止
};