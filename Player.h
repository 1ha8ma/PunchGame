#pragma once
#include"CharacterBase.h"

class Player :public CharacterBase
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize();
	//�X�V
	void Update(int inputstate);

	void ForeverUpdate();

	VECTOR GetPosition() { return position; }
	float GetAngle() { return angle; }
	bool GetAttackflg() { return attackflg; }

private:
	//���͏���
	void InputProcess(const int inputstate);
};