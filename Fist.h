#pragma once

class SEManager;
class Effect;

class Fist
{
public:
	const float FistCapsuleRadius = 120.0f;//�J�v�Z�����a

	Fist();
	~Fist();
	void Initialize();
	void Update(float multiply,VECTOR charapos, float charaangle, bool punchflg, bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
	float GetSize() { return size; }

private:
	SEManager* semanager;
	Effect* effect;

	const float PunchSpeed = 13.0f;//�p���`�X�s�[�h
	const float DistanceWithCharacter = 250.0f;//�p���`�������Ƃ��̌��ƃL�����N�^�[�̋���
	const float CapsuleFrontLength = 200.0f;//�J�v�Z���̑O�̒���
	const float CapsuleBackLength = 100.0f;//�J�v�Z���̌��̒���

	int model;//���f��
	float modelangle;//���f���p�x
	VECTOR position;//�|�W�V����
	float size;//���f���T�C�Y

	//�G�t�F�N�g�֌W
	bool playfiringefectflg;//���˃G�t�F�N�g�Đ��t���O

	//�p���`�֌W
	bool punchingflg;//�p���`��
	float punchangle;//�p���`�̊p�x
	VECTOR velocity;
	VECTOR capFront;//�O
	VECTOR capBack;//���
	bool shieldhitflg;//���ɓ�������

	//�p���`�̓���
	void PunchMove(bool punchflg,float multiply, float charaangle, VECTOR charapos, bool shieldhit);
};