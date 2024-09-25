#pragma once

class CharacterBase
{
protected:
	const float Speed = 10.0f;//����

	//�A�j���[�V�����̎��
	enum class AnimKind : int
	{
		None = -1,//����
		Run = 0,//����
		Punch = 1,//�p���`
	};

	//���f���E�A�j���[�V����
	int model;//���f��
	int animtotaltime;//���A�j���[�V��������
	float animplaytime;//���݂̃A�j���[�V�����Đ�����
	bool isanimflg;//�A�j���[�V�������Đ����邩
	int nowPlayAnimKind;//���ݍĐ����̃A�j���[�V����
	int nowPlayAnim;//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int prevPlayAnim;//�ύX�O�̃A�j���[�V����

	//�|�W�V����
	VECTOR position;//�|�W�V����
	VECTOR moveVec;//���͂������Ă���̓�������
	VECTOR targetLookDirection;//���f���������ׂ������̃x�N�g��
	float angle;//���݂̃v���C���[�p�x

	//�U��
	bool attackflg;

	//�p�x�X�V
	void UpdateAngle();
	//�A�j���[�V�����؂�ւ�
	void ChangeAnimation(AnimKind nextkind);
	//�A�j���[�V�����Đ�
	void PlayAnimation();
	//�U������
	void Attack();

public:
	//�`��
	void Draw();
};