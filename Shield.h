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

	const float ShieldCapsuleRadius = 70.0f;//�J�v�Z�����a
	const float DisttanceWithGround = 200.0f;//�n�ʂ���̋���(�X�e�[�W����̋���)
	const float HalfWidthSize = 100.0f;//�����̔����̃T�C�Y
	const float AngleCorrection = DX_PI_F / 2;//�p�x�␳�l

	//Get.Set

	VECTOR GetPosition() { return position; }
	VECTOR GetcapLeft() { return capLeft; }
	VECTOR GetcapRight() { return capRight; }

private:
	const float DistanceWithCharacter = 330.0f;//�L�����N�^�[�Ə��̋���

	int model;//���f���n���h��
	VECTOR position;//�|�W�V����
	float angle;//�p�x

	//�J�v�Z��
	VECTOR capLeft;
	VECTOR capRight;

	//�p�x�X�V
	void UpdateAngle(float characterAngle);
};