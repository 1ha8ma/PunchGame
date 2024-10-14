#pragma once

class Camera;

class ResultScene
{
private:
	InputManager* input;
	Camera* camera;

	int ribbonimage;//���{���摜

	bool inputpossibleflg;//���͉\

	VECTOR winnerposition;//���҃|�W�V����
	float winnerangle;//���Ҋp�x
	VECTOR targetposition;//�J�����̈ړ�����ꏊ

	float t;//Lerp�p��������

public:
	ResultScene();
	~ResultScene();
	void Initialize(VECTOR position,float angle);
	bool Update(Camera*& camera);
	void Draw();
};