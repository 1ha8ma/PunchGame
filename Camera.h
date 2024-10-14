#pragma once

class Camera
{
private:
	VECTOR pos;//�J�����|�W�V����
	VECTOR lookpos;//�����_

	float angle;//��]�̊p�x
	const float initangle = -2.0f;//�ŏ��̊p�x
public:
	//�R���X�g���N�^
	Camera();
	//������
	void Initialize();
	//�Q�[�����X�V
	void UpdateForGame();
	//�^�C�g�����X�V
	void UpdateForTitle();
	//���U���g�X�V
	void UpdateForResult(VECTOR winnerpos,int winnernumber);

	VECTOR GetPosition() { return pos; }
	void SetPosition(VECTOR newpos) { pos = newpos; }
};