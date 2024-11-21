#pragma once

class Camera;
class BGMManager;

class ResultScene
{
public:
	ResultScene();
	~ResultScene();
	void Initialize(VECTOR position, float angle);
	bool Update(Camera*& camera);
	void Draw();

private:
	InputManager* input;
	Camera* camera;
	BGMManager* bgmmanager;

	float FontScalingSpeed = 1.0f;//�g��k���X�s�[�h

	int ribbonimage;//���{���摜

	bool inputpossibleflg;//���͉\

	VECTOR winnerposition;//���҃|�W�V����
	float winnerangle;//���Ҋp�x
	VECTOR targetposition;//�J�����̈ړ�����ꏊ

	float t;//Lerp�p��������

	int fontsize;//�t�H���g�T�C�Y
	int fontsizechangeflame;//�t�H���g�g��k���t���[��
	bool fontsizechangeflg;//�t�H���g�g��k���t���O
	VECTOR explanationpos;//���̃V�[���ւ̐����̃|�W�V����
};