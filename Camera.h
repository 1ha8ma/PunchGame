#pragma once

class Camera
{
public:
	//�R���X�g���N�^
	Camera();
	//������
	void Initialize();
	//�Q�[���J�n��������
	void GamestartInitialize();
	//�Q�[���X�^�[�g�X�V
	void UpdateForStart(VECTOR position, VECTOR lookpos);
	//�Q�[�����X�V
	void UpdateForGame();
	//�^�C�g�����X�V
	void UpdateForTitle();
	//���U���g�X�V
	void UpdateForResult(VECTOR winnerpos, int winnernumber);

	VECTOR GetPosition() { return pos; }
	void SetPosition(VECTOR newpos) { pos = newpos; }

private:
	VECTOR pos;//�J�����|�W�V����
	VECTOR lookpos;//�����_

	float angle;//��]�̊p�x
	const float initangle = -2.0f;//�ŏ��̊p�x
};