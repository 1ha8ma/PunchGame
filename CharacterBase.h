#pragma once

//���N���X
class Shield;
class Fist;
class SEManager;
class Effect;
class Collision;

class CharacterBase
{
public:	
	//�R���X�g���N�^
	CharacterBase();
	//�f�X�g���N�^
	~CharacterBase();
	//���Փ�se�Đ�
	void PlayShieldHitSE(bool hit);
	//�A�E�g�m�F
	void CheckOut(bool hit);
	//�|�W�V�������f
	void ReflectPosition();
	//�I������X�V
	void ForeverUpdate(bool settlement);
	//�`��
	void Draw();

	//�U���ɓ����蔻���t���邩���f
	void CheckAttackOnCollision();
	//�����蔻��
	bool FistWithCharacter(VECTOR charatop, VECTOR charabottom, bool charaout);
	bool FistWithShield(VECTOR Shieldleft, VECTOR Shieldright);
	bool ShieldWithShield(VECTOR myshieldleft, VECTOR myshieldright, VECTOR shieldleft, VECTOR shieldright);
	void RemoveShield(VECTOR shieldleft, VECTOR shieldright);

	//Get�ESet
	VECTOR GetPositioncapsuleTop() { return capsuleTop; }
	VECTOR GetPositioncapsuleBotoom() { return capsuleBottom; }
	VECTOR GetShieldPosition();
	VECTOR GetShieldLeft();
	VECTOR GetShieldRight();
	void SetShieldHit(bool hit);
	bool GetShieldHit() { return shieldhit; }
	bool GetOutflg() { return outflg; }
	float GetAngle() { return angle; }

protected:
	const float Speed = 10.0f;//����
	const float CharacterCapsuleRadius = 120.0f;

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
	SEManager* semanager;
	Effect* effect;
	Collision* collision;

	//������
	void BaseInitialize();
	//�p�x������
	void InitializeAngle();
	//�J�v�Z���̍X�V
	void UpdateCapsule();
	//���N���X�̍X�V
	void OtherClassUpdate(bool Settlement);
	//�G�t�F�N�g�X�V
	void UpdateEffect();
	//�������
	void Blow(bool Settlement);

	//���f���E�A�j���[�V����
	int model;//���f��
	int animtotaltime;//���A�j���[�V��������
	float animplaytime;//���݂̃A�j���[�V�����Đ�����
	bool isanimflg;//�A�j���[�V�������Đ����邩
	int nowPlayAnimKind;//���ݍĐ����̃A�j���[�V����
	int nowPlayAnim;//���݂̃A�j���[�V�����A�^�b�`�ԍ�
	int prevPlayAnim;//�ύX�O�̃A�j���[�V����

	//�G�t�F�N�g
	bool Playplayerhiteffectflg;//�v���C���[�Փ˃G�t�F�N�g�Đ��t���O
	bool Playshieldhiteffectflg;//���Փ˃G�t�F�N�g�t���O

	//�|�W�V����
	VECTOR position;//�|�W�V����
	VECTOR moveVec;//���͂������Ă���̓�������
	VECTOR targetLookDirection;//���f���������ׂ������̃x�N�g��
	float angle;//���݂̃L�����N�^�[�p�x
	VECTOR capsuleTop;//�J�v�Z����
	VECTOR capsuleBottom;//�J�v�Z����

	//�U��
	bool attackflg;//�U�����t���O
	bool attackOnCollision;//�U���ɓ����蔻���t����t���O

	bool outflg;//�E��
	bool shieldhit;//�U�������ɓ�������
	bool shieldhitseflg;//���Փ�se�t���O

	//�p�x�X�V
	void UpdateAngle();
	//�A�j���[�V�����؂�ւ�
	void ChangeAnimation(AnimKind nextkind);
	//�A�j���[�V�����Đ�
	void PlayAnimation();
	//���N���X�̏�����
	void OtherClassInitialize();
	//�U������
	void Attack();
};