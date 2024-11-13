#pragma once
#include<vector>
#include"CharacterBase.h"

class Enemy :public CharacterBase
{
public:
	//cpu�̓����̎��
	enum MoveKind
	{
		charachase,//�L������ǂ�
		randomwalk,//�����_���ɕ���
	};

	//�R���X�g���N�^
	Enemy(int handle, float modelsize, VECTOR position, VECTOR targetDir, int cpunumber);
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(VECTOR position, VECTOR targetDir);
	//�X�V
	void Update(std::vector<int> outchara);
	//���Ə��̓����蔻��̍X�V
	void UpdateShieldWithShield(VECTOR shieldleft, VECTOR shieldright);
	//�|�W�V�����̍X�V
	void UpdatePosition();
	//�I������X�V
	void ForeverUpdate();

	//Get,Set
	VECTOR GetPosition() { return position; }
	int GetTarGetNumber() { return target; }
	void SetTargetCharaPosition(VECTOR targetcharapos) { targetCharaPosition = targetcharapos; }
	void SetTargetCharaAngle(float targetcharaangle) { targetCharaAngle = targetcharaangle; }
	bool GetOutflg() { return outflg; }
	bool GetAttackflg() { return attackflg; }
	int GetNowMoveKind() { return NowMoveKind; }

private:
	const int Range = 1000;//�˒��͈�

	int mynumber;//������CPU�ԍ�

	//�ړ��֌W
	int NowMoveKind;//���݂̓�������
	bool moveonflg;//�������ǂ����t���O
	VECTOR targetPosition;
	VECTOR targetCharaPosition;//�ǂ�������ڕW�̃|�W�V����
	float targetCharaAngle;//�ǂ�������ڕW�̊p�x
	int moveflame;//�ړ��J�n����̃t���[��
	float moveangle;//��������

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
};