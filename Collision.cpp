#include"DxLib.h"
#include"Collision.h"

/// <summary>
/// �J�v�Z���ǂ����̓����蔻��
/// </summary>
/// <param name="cap1side1">�J�v�Z��1�̕Е��̓_</param>
/// <param name="cap1side2">�J�v�Z��1�̂����Е��̓_</param>
/// <param name="cap2side1">�J�v�Z��2�̕Е��̓_</param>
/// <param name="cap2side2">�J�v�Z��2�̂����Е��̓_</param>
/// <param name="cap1R">�J�v�Z��1���a</param>
/// <param name="cap2R">�J�v�Z��2���a</param>
/// <returns>�������Ă��邩</returns>
bool Collision::CapsuleWithCapsule(VECTOR cap1side1, VECTOR cap1side2, VECTOR cap2side1, VECTOR cap2side2, float cap1R, float cap2R)
{
	float len;//2�J�v�Z���̋���
	bool hit = false;//�U������������

	//2�̐����̍ŒZ���������߂�
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