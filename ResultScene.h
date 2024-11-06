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

	int ribbonimage;//���{���摜

	bool inputpossibleflg;//���͉\

	VECTOR winnerposition;//���҃|�W�V����
	float winnerangle;//���Ҋp�x
	VECTOR targetposition;//�J�����̈ړ�����ꏊ

	float t;//Lerp�p��������
};