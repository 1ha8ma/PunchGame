#pragma once

class Camera
{
private:
	VECTOR pos;//�J�����|�W�V����
	VECTOR lookpos;//�����_

public:
	//�R���X�g���N�^
	Camera();
	//������
	void Initialize();
	//�X�V
	void Update();
};