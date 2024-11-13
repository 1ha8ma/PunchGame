#pragma once

class SEManager;
class Effect;

class Fist
{
public:
	const float FistCapsuleRadius = 120.0f;

	Fist();
	~Fist();
	void Initialize();
	void Update(VECTOR charapos, float charaangle, bool punchflg, bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
	float GetSize() { return size; }

private:
	SEManager* semanager;
	Effect* effect;

	const float PunchSpeed = 13.0f;

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
	void PunchMove(bool punchflg, float charaangle, VECTOR charapos, bool shieldhit);
};