#pragma once

//��ʃT�C�Y
const int SCREEN_W = 1600;
const int SCREEN_H = 900;

//�L�����N�^�[�i���o�[
enum class CharaNumber :int
{
	CPU0 = 0,
	CPU1 = 1,
	CPU2 = 2,
	Player = 3,
};

const float AngleSpeed = 0.2f;//�p�x�ύX���x

const int OllCharaNum = 4;//���l��

//�X�e�[�W�̊e���W
const float StageRight = 1600.0f;//�E
const float StageLeft = -1500.0f;//��
const float StageTop = 1500.0f;//��
const float StageBottom = -1000.0f;//��