#pragma once
#include<vector>

const int BoardNum = 62;

class WoodBoard
{
private:
	int model;
	
	std::vector<int> eachmodel;//Šeƒ‚ƒfƒ‹
	std::vector<float> rotax;
	std::vector<float> rotay;
	std::vector<float> rotaz;
	std::vector<VECTOR> pos;

public:
	WoodBoard();
	void Initialize();
	void Update();
	void Draw();
};