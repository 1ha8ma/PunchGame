#pragma once
#include<vector>


class WoodBoard
{
public:
	WoodBoard();
	void Initialize();
	void Draw();

private:
	const int MiddleBoardNum = 14;//�^�񒆂̔̐�
	const int LeftBoardNum = 24;//�E�̔̐�
	const int RightBoardNum = 24;//���̔̐�
	const int AllBoardNum = MiddleBoardNum + LeftBoardNum + RightBoardNum;//�S�Ă̔̐�

	int model;

	std::vector<int> eachmodel;//�e���f��
	std::vector<float> rotax;
	std::vector<float> rotay;
	std::vector<float> rotaz;
	std::vector<VECTOR> pos;
};