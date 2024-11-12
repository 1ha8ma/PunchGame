#include"DxLib.h"
#include"Collision.h"

/// <summary>
/// カプセルどうしの当たり判定
/// </summary>
/// <param name="cap1side1">カプセル1の片方の点</param>
/// <param name="cap1side2">カプセル1のもう片方の点</param>
/// <param name="cap2side1">カプセル2の片方の点</param>
/// <param name="cap2side2">カプセル2のもう片方の点</param>
/// <param name="cap1R">カプセル1半径</param>
/// <param name="cap2R">カプセル2半径</param>
/// <returns>当たっているか</returns>
bool Collision::CapsuleWithCapsule(VECTOR cap1side1, VECTOR cap1side2, VECTOR cap2side1, VECTOR cap2side2, float cap1R, float cap2R)
{
	float len;//2カプセルの距離
	bool hit = false;//攻撃が当たった

	//2つの線分の最短距離を求める
	len = Segment_Segment_MinLength(cap1side1, cap1side2, cap2side1, cap2side2);

	if (len < cap1R + cap2R)
	{
		hit = true;
	}
	else
	{
		hit = false;
	}

	return hit;
}