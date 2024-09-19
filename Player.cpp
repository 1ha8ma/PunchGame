#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	//モデルロード・アニメーション設定
	model = MV1LoadModel("3D/player.mv1");
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);

	//初期化処理
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	//アニメーション初期化
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = static_cast<int>(AnimKind::Run);
	prevPlayAnim = -1;

	isanimflg = false;
	angle = 0.0f;
	moveVec = VGet(0, 0, 0);
	targetDirection = VGet(1.0f, 0.0f, 1.0f);
	attackflg = false;

	//ポジション初期化
	position = VGet(-1000.0f, 100.0f, -700.0f);
	MV1SetPosition(model, position);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(int inputstate)
{
	//入力処理
	InputProcess(inputstate);
	
	//アニメーション
	PlayAnimation();
	
	//向き設定
	UpdateAngle();

	//モデルポジション更新
	MV1SetPosition(model, position);
}

/// <summary>
/// 入力されてからの処理
/// </summary>
/// <param name="inputstate">入力状態</param>
/// <param name="wallhit">どこかの壁に当たっているか</param>
void Player::InputProcess(const int inputstate)
{
	//moveVec初期化
	moveVec = VGet(0, 0, 0);

	//移動
	if (attackflg == false)
	{
		if ((4 & inputstate) == 4)//右
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
		}
		if ((2 & inputstate) == 2)//左
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
		}
		if ((8 & inputstate) == 8)//上
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
		}
		if ((1 & inputstate) == 1)//下
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -1.0f));
		}
	}

	//アニメーションフラグ変更
	if (inputstate != 0)
	{
		isanimflg = true;
	}
	else
	{
		isanimflg = false;
	}

	//攻撃
	if ((16 & inputstate) == 16)//Bボタン
	{
		Attack();
	}

	if (inputstate != 0 && attackflg == false)
	{
		//移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		//targetMoveDirection = VNorm(moveVec);
		targetDirection = moveVec;

		//正規化したベクトルにスピード倍したものを移動ベクトルとする
		moveVec = VScale(targetDirection, Speed);
	}

	//ポジションに適用
	position = VAdd(position, moveVec);
}