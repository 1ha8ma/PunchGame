#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	int mynumber;//������CPU�ԍ�
	int target;//�ǂ�������ڕW
	float targetdistance;//2�L�����̋���
	float targetCharaAngle;//�ڕW�̃L�����Ƃ̊p�x
	VECTOR targetPosition;//�ǂ�������ڕW�̃|�W�V����
	int chaseflame;//�ǂ������Ă���t���[��
	float vx;
	float vz;

	bool attackaftercharachange;//�U����ڕW�L���������

	//�U���̃N�[���^�C��
	bool cooltimeflg;
	int cooltimeflame;

	float moveangle;

	//�^�[�Q�b�g�ݒ�
	void SetTarget(std::vector<int> outchara);
	//�ړ�����
	void Move(std::vector<int> outchara);

public:
	//�R���X�g���N�^
	Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDir,int cpunumber);
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(VECTOR position, VECTOR targetDir);
	//�X�V
	void Update(std::vector<int> outchara);

	VECTOR GetPosition() { return position; }
	int GetTarGetNumber() { return target; }
	void SetTargetPosition(VECTOR targetpos) { targetPosition = targetpos; }
	bool GetOutflg() { return outflg; }
	void SetShieldHit(bool hit) { shieldhit = hit; }
	bool GetShieldHit() { return shieldhit; }
	bool GetAttackflg() { return attackflg; }
};