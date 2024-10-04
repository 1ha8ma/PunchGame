#pragma once

//���N���X
class Shield;
class Fist;

class CharacterBase
{
protected:
	const float Speed = 10.0f;//����
	const float CharacterR = 120.0f;

	//�A�j���[�V�����̎��
	enum class AnimKind : int
	{
		None = -1,//����
		Run = 0,//����
		Punch = 1,//�p���`
	};

	

	//���N���X
	Shield* shield;
	Fist* fist;

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
	float angle;//���݂̃L�����N�^�[�p�x
	VECTOR capsuleTop;
	VECTOR capsuleBottom;

	//�U��
	bool attackflg;//�U���J�n�t���O
	
	bool outflg;//�E��
	bool shieldhit;//�U�������ɓ�������


	//�p�x�X�V
	void UpdateAngle();
	//�A�j���[�V�����؂�ւ�
	void ChangeAnimation(AnimKind nextkind);
	//�A�j���[�V�����Đ�
	void PlayAnimation();
	//���N���X�̏�����
	void OtherClassInitialize();
	//�J�v�Z���̍X�V
	void UpdateCapsule();
	//�U������
	void Attack();


public:
	//�����蔻��
	bool FistWithCharacter(VECTOR charatop, VECTOR charabottom,float charaR,bool charaout);
	bool FistWithShield(VECTOR Shieldleft, VECTOR Shieldright, float shieldR);
	//�R���X�g���N�^
	CharacterBase();
	//���N���X�̍X�V
	void OtherClassUpdate(bool shieldhit);
	//�������
	void Blow();
	//�A�E�g�m�F
	void CheckOut(bool hit);
	//�`��
	void Draw();

	VECTOR GetPositioncapsuleTop() { return capsuleTop; }
	VECTOR GetPositioncapsuleBotoom() { return capsuleBottom; }
	VECTOR GetShieldLeft();
	VECTOR GetShieldRight();
	bool GetOutflg() { return outflg; }
	bool GetAttackflg(){ return attackflg; }
};