#pragma once
#include<vector>

class StartScene
{
private:

	std::vector<int> image;
	/*int image1;
	int image2;
	int image3;*/
	int startimage;

	float cameraangle;
	VECTOR lookpos;
	VECTOR camerapos;

	int count;
	bool countflg;
	int countflame;

	//�����摜�ʒu
	bool sizechangeflg;
	int sizechangeflame;
	float numberlx;
	float numberly;
	float numberrx;
	float numberry;

public:
	//�R���X�g���N�^
	StartScene();
	//������
	void Initialize();
	//�X�V
	bool Update();
	//�`��
	void Draw();

	VECTOR GetLookPos() { return lookpos; }
	VECTOR GetCameraPos() { return camerapos; }
};