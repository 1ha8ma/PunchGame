#pragma once

class Fist
{
private:
	const float PunchSpeed = 10.5f;

	int model;//モデル
	float modelangle;//モデル角度
	VECTOR position;//ポジション

	//エフェクト関係
	int PlayingEffect;//再生中のエフェクト
	bool playfiringefectflg;//発射エフェクト再生フラグ
	int firingeffecthandle;//発射エフェクトハンドル
	VECTOR firingefectangle;//発射エフェクト角度
	VECTOR firingefectposition;//発射エフェクトポジション

	//パンチ関係
	bool punchingflg;//パンチ中
	float punchangle;//パンチの角度
	float vx;//x方向に進む力
	float vz;//z方向に進む力
	VECTOR capFront;//前
	VECTOR capBack;//後ろ


	void PunchMove(bool punchflg,float charaangle,VECTOR charapos,bool shieldhit);
	void UpdateAngle(float charaangle);
public:
	static const float FistCapsuleRadius;

	Fist();
	~Fist();
	void Initialize();
	void Update(VECTOR charapos, float charaangle,bool punchflg,bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
};