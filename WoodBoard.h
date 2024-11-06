#pragma once
#include<vector>


class WoodBoard
{
public:
	WoodBoard();
	void Initialize();
	void Draw();

private:
	const int MiddleBoardNum = 14;//真ん中の板の数
	const int LeftBoardNum = 24;//右の板の数
	const int RightBoardNum = 24;//左の板の数
	const int AllBoardNum = MiddleBoardNum + LeftBoardNum + RightBoardNum;//全ての板の数

	int model;

	std::vector<int> eachmodel;//各モデル
	std::vector<float> rotax;
	std::vector<float> rotay;
	std::vector<float> rotaz;
	std::vector<VECTOR> pos;
};