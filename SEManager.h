#pragma once
#include<map>

class SEManager
{
public:

	enum SEKind
	{
		CharahitSE,//�L�����ɍU��������������
		ShieldhitSE,//���Ŗh������
		AttackSE,//�U����
		StartCountSE,//�J�E���gse
		StartSceneSE,//�X�^�[�g���o�̎���se
		StartSE,//�X�^�[�g�\����se
		CrickSE,//����{�^�����������Ƃ�
		WinnerSE,//���U���g�ł̏��҂��o�Ă�������SE
	};

	//�R���X�g���N�^
	SEManager();

	//�Đ�
	void PlaySE(SEKind kind);

private:
	std::map<SEKind, int> handle;


};