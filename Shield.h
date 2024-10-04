#pragma once

class Shield
{
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

public:
	//�R���X�g���N�^
	Shield();
	//�f�X�g���N�^
	~Shield();
	//������
	void Initialize();
	//�X�V
	void Update(VECTOR characterPosition,float characterangle);
	//�`��
	void Draw();

	VECTOR GetcapLeft() { return capLeft; }
	VECTOR GetcapRight() { return capRight; }
};