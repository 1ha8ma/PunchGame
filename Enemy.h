#pragma once
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	float targetdistance;//2�L�����̋���
	VECTOR targetCharaPos;//�ǂ�������ڕW�̃|�W�V����

	//�ړ�����
	//�U���J�n����
public:
	//�R���X�g���N�^
	Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDir);
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(VECTOR position, VECTOR targetDir);
	//�߂��̃L�����N�^�[���m�F
	void CheckNearCharacter(VECTOR charapos);
	//�X�V
	void Update();

};