#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
private:
	int mynumber;//������CPU�ԍ�

	//�ړ��֌W
	int NowMoveKind;//���݂̓�������
	bool moveonflg;//�������ǂ����t���O
	VECTOR targetPosition;//�ǂ�������ڕW�̃|�W�V����
	int moveflame;//�ǂ������Ă���t���[��
	float moveangle;//��������
	//�ړ����x
	float vx;
	float vz;

	//�L�����ǂ��֌W
	int target;//�ǂ�������ڕW
	float targetdistance;//2�L�����̋���

	//�����_�������֌W
	bool SetWalkTargetPositionflg;

	//�U���̃N�[���^�C��
	bool cooltimeflg;
	int cooltimeflame;

	//�^�[�Q�b�g�ݒ�
	void SetTargetChara(std::vector<int> outchara);
	//�ړ�����
	void Move(std::vector<int> outchara);

public:
	enum MoveKind
	{
		charachase,//�L������ǂ�
		randomwalk,//�����_���ɕ���
	};
	
	//�R���X�g���N�^
	Enemy(int handle,float modelsize,VECTOR position,VECTOR targetDir,int cpunumber);
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
	int GetNowMoveKind() { return NowMoveKind; }
};