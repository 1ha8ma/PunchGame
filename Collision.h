#pragma once

class Collision
{
public:
	//カプセルどうしの当たり判定
	bool CapsuleWithCapsule(VECTOR cap1side1, VECTOR cap1side2, VECTOR cap2side1, VECTOR cap2side2, float cap1R, float cap2R);

private:
};