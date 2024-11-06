#pragma once

class Shield
{
public:
	//�R���X�g���N�^
	Shield();
	//�f�X�g���N�^
	~Shield();
	//������
	void Initialize(VECTOR charaposition, float characterangle);
	//�X�V
	void Update(VECTOR characterPosition, float characterangle);
	//�|�W�V�������f
	void ReflectPosition(VECTOR newposition);
	//�`��
	void Draw();

	const float ShieldCapsuleRadius = 20.0f;
	VECTOR GetPosition() { return position; }
	VECTOR GetcapLeft() { return capLeft; }
	VECTOR GetcapRight() { return capRight; }

private:
	const float DistanceWithCharacter = 330.0f;//�L�����N�^�[�Ə��̋���
	const float CapsuleRadius = 50.0f;//�J�v�Z�����a

	int model;//���f���n���h��
	VECTOR position;//�|�W�V����
	float angle;//�p�x

	//�J�v�Z��
	VECTOR capLeft;
	VECTOR capRight;

	//�p�x�X�V
	void UpdateAngle(float characterAngle);
	//�p�x������
	void InitializeAngle(float charaangle);
};