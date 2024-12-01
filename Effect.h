#pragma once
#include<vector>
#include<map>

class Effect
{
public:
	enum EffectKind
	{
		Attack,
		LastCharacterHit,
		ShieldHit,
		Blow,
	};

	Effect();
	~Effect();
	void Initialize();
	void PlayEffect(EffectKind kind, VECTOR playposition, VECTOR initsize, float playangle, float playspeed);
	void Update();
	void Draw();

private:
	std::vector<int> PlayingEffectKind;//再生中のエフェクトの種類
	std::vector<int> PlayingEffecthandle;//再生中のエフェクトのハンドル
	std::vector<VECTOR> PlayingEffectScale;//エフェクトサイズ
	std::map<EffectKind, int> Effecthandle;//エフェクトハンドル

	//ハンドル
	int attackeffecthandle;
	int characterhiteffecthandle;
	int shieldhiteffecthandle;

	const float ExpansionSpeed = 0.02f;//盾衝突エフェクト拡大速度
};