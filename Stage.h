#pragma once

class Stage
{
public:
	Stage();
	void Initialize();
	void Draw();

	//�X�e�[�W�̊e���W
	static const float StageRight;//�E
	static const float StageLeft;//��
	static const float StageTop;//��
	static const float StageBottom;//��

private:
	int model;//���f��
};