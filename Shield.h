#pragma once

class Shield
{
private:
	const float DistanceWithCharacter = 330.0f;//�L�����N�^�[�Ə��̋���
	const float AngleSpeed = 0.2f;//�p�x�ύX���x

	int model;//���f��
	VECTOR position;//�|�W�V����
	float angle;//�p�x

	bool o;
	float anglecopy;

	
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
};