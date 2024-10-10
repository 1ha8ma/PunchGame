#pragma once

class Fist
{
private:
	const float PunchSpeed = 10.5f;

	int model;//���f��
	float modelangle;//���f���p�x
	VECTOR position;//�|�W�V����

	//�G�t�F�N�g�֌W
	int PlayingEffect;//�Đ����̃G�t�F�N�g
	bool playfiringefectflg;//���˃G�t�F�N�g�Đ��t���O
	int firingeffecthandle;//���˃G�t�F�N�g�n���h��
	VECTOR firingefectangle;//���˃G�t�F�N�g�p�x
	VECTOR firingefectposition;//���˃G�t�F�N�g�|�W�V����

	//�p���`�֌W
	bool punchingflg;//�p���`��
	float punchangle;//�p���`�̊p�x
	float vx;//x�����ɐi�ޗ�
	float vz;//z�����ɐi�ޗ�
	VECTOR capFront;//�O
	VECTOR capBack;//���


	void PunchMove(bool punchflg,float charaangle,VECTOR charapos,bool shieldhit);
	void UpdateAngle(float charaangle);
public:
	static const float FistCapsuleRadius;

	Fist();
	~Fist();
	void Initialize();
	void Update(VECTOR charapos, float charaangle,bool punchflg,bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
};