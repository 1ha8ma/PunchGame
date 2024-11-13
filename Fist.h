#pragma once

class SEManager;
class Effect;

class Fist
{
public:
	const float FistCapsuleRadius = 120.0f;

	Fist();
	~Fist();
	void Initialize();
	void Update(VECTOR charapos, float charaangle, bool punchflg, bool shieldhit);
	void Draw();

	VECTOR GetcapFront() { return capFront; }
	VECTOR GetcapBack() { return capBack; }
	float GetSize() { return size; }

private:
	SEManager* semanager;
	Effect* effect;

	const float PunchSpeed = 13.0f;

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
	void PunchMove(bool punchflg, float charaangle, VECTOR charapos, bool shieldhit);
};