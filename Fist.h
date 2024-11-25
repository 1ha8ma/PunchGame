#pragma once

class SEManager;
class Effect;

class Fist
{
public:
	const float FistCapsuleRadius = 120.0f;//カプセル半径

	Fist();
	~Fist();
	void Initialize();
	void Update(float multiply,VECTOR charapos, float charaangle, bool punchflg, bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
	float GetSize() { return size; }

private:
	SEManager* semanager;
	Effect* effect;

	const float PunchSpeed = 13.0f;//パンチスピード
	const float DistanceWithCharacter = 250.0f;//パンチをしたときの拳とキャラクターの距離
	const float CapsuleFrontLength = 200.0f;//カプセルの前の長さ
	const float CapsuleBackLength = 100.0f;//カプセルの後ろの長さ

	int model;//モデル
	float modelangle;//モデル角度
	VECTOR position;//ポジション
	float size;//モデルサイズ

	//エフェクト関係
	bool playfiringefectflg;//発射エフェクト再生フラグ

	//パンチ関係
	bool punchingflg;//パンチ中
	float punchangle;//パンチの角度
	VECTOR velocity;
	VECTOR capFront;//前
	VECTOR capBack;//後ろ
	bool shieldhitflg;//盾に当たった

	//パンチの動き
	void PunchMove(bool punchflg,float multiply, float charaangle, VECTOR charapos, bool shieldhit);
};