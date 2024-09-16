#pragma once

class Player
{
private:
	const float AngleSpeed = 0.2f;//�p�x�ύX���x
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
	int runanim;//���郂�[�V����
	int animtotaltime;//���A�j���[�V��������
	float animplaytime;//���݂̃A�j���[�V�����Đ�����
	bool isanimflg;//�A�j���[�V�������Đ����邩
	int nowPlayAnimKind;//���ݍĐ����̃A�j���[�V����
	int nowPlayAnim;//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int prevPlayAnim;//�ύX�O�̃A�j���[�V����

	//�|�W�V����
	VECTOR position;//�|�W�V����
	VECTOR moveVec;//���͂������Ă���̓�������
	VECTOR targetDirection;//���f���������ׂ������̃x�N�g��
	float angle;//���݂̃v���C���[�p�x

	//�U��
	bool attackflg;

	//���͏���
	void InputMoveProcess(const int inputstate);
	//�A�j���[�V�����؂�ւ�
	void ChangeAnimation(AnimKind nextkind);
	//�A�j���[�V�����Đ�
	void PlayAnimation();
	//������ݒ�
	void UpdateAngle();
	//�U������
	void Attack();

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize();
	//�X�V
	void Update(int inputstate);
	//�`��
	void Draw();

	VECTOR GetPos() { return position; }
	float GetAngle() { return angle; }
};