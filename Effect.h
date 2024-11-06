#pragma once
#include<vector>
#include<map>

class Effect
{
public:
	enum EffectKind
	{
		Attack,
		CharacterHit,
		ShieldHit,
	};

	Effect();
	~Effect();
	void Initialize();
	void PlayEffect(EffectKind kind, VECTOR playposition, VECTOR initsize, float playangle, float playspeed);
	void Update();
	void Draw();

private:
	std::vector<int> PlayingEffectKind;//�Đ����̃G�t�F�N�g�̎��
	std::vector<int> PlayingEffecthandle;//�Đ����̃G�t�F�N�g�̃n���h��
	std::vector<VECTOR> PlayingEffectSize;//�G�t�F�N�g�T�C�Y
	std::map<EffectKind, int> Effecthandle;//�G�t�F�N�g�n���h��

	int attackeffecthandle;
	int characterhiteffecthandle;
	int shieldhiteffecthandle;

	const float ExpansionSpeed = 0.01f;//���Փ˃G�t�F�N�g�g�呬�x
};