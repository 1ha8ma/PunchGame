#pragma once
#include"CharacterBase.h"

class Player :public CharacterBase
{
private:
	//���͏���
	void InputProcess(const int inputstate);

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize();
	//�X�V
	void Update(int inputstate,bool shieldhit);

	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }
	bool GetAttackflg() { return attackflg; }
};