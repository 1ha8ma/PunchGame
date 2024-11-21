#pragma once
#include<vector>

class SEManager;

class StartScene
{
public:
	//�R���X�g���N�^
	StartScene(VECTOR playerpos);
	//������
	void Initialize(VECTOR playerpos);
	//�X�V
	bool Update();
	//�`��
	void Draw();

	VECTOR GetLookPos() { return lookpos; }
	VECTOR GetCameraPos() { return camerapos; }

private:
	SEManager* semanager;

	const float ScalingSpeed = 1.0f;//�����g��k�����x

	//�J�E���g�_�E���摜
	std::vector<int> image;
	int startimage;

	//�e�L�X�g�{�b�N�X�摜
	int textbox;
	
	//�v���C���[���摜
	int playerarrow;
	VECTOR playerarrowpos;

	//�J�����֌W
	float cameraangle;
	VECTOR lookpos;
	VECTOR camerapos;

	//�J�E���g�֌W
	int count;
	bool countflg;
	int countflame;
	bool startseflg;

	//�����摜�ʒu
	bool sizechangeflg;
	int sizechangeflame;
	float numberlx;
	float numberly;
	float numberrx;
	float numberry;
};