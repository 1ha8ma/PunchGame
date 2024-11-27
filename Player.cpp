#include<math.h>
#include"DxLib.h"
#include"Stage.h"
#include"InputManager.h"
#include"Loader.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	//モデルロード・アニメーション設定
	Loader* loader = Loader::GetInstance();
	model = loader->GetHandle(Loader::Kind::PlayerModel);

	//初期化処理
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	MV1DetachAnim(model, nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	BaseInitialize();

	//ポジション初期化
	position = VGet(-1000.0f, 100.0f, -700.0f);
	capsuleTop = VAdd(position, VGet(0, 600, 0));
	capsuleBottom = VAdd(position, VGet(0, 0, 0));

	//移動角度設定
	moveVec = VGet(0, 0, 0);
	targetLookDirection = VGet(1.0f, 0.0f, 1.0f);

	attackinputpossible = false;

	InitializeAngle();
	OtherClassInitialize();

	MV1SetPosition(model, position);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(int inputstate,bool outpauseinputflg)
{
	//入力処理
	InputProcess(inputstate, outpauseinputflg);
	
	//当たり判定を付けるか判断
	CheckAttackOnCollision();

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
void Player::InputProcess(const int inputstate,bool outpauseinputflg)
{
	//moveVec初期化
	moveVec = VGet(0, 0, 0);
	isanimflg = false;

	//移動
	if (attackflg == false)
	{
		if (position.x <= Stage::StageRight && (InputManager::InputNumber::Right & inputstate) == InputManager::InputNumber::Right)//右
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
			isanimflg = true;
		}
		if (position.x >= Stage::StageLeft && (InputManager::InputNumber::Left & inputstate) == InputManager::InputNumber::Left)//左
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
			isanimflg = true;
		}
		if (position.z <= Stage::StageTop && (InputManager::InputNumber::Up & inputstate) == InputManager::InputNumber::Up)//上
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
			isanimflg = true;
		}
		if (position.z >= Stage::StageBottom && (InputManager::InputNumber::Down & inputstate) == InputManager::InputNumber::Down)//下
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, -1.0f));
			isanimflg = true;
		}
	}

	//攻撃
	if ((InputManager::InputNumber::BButton & inputstate) == InputManager::InputNumber::BButton)//Bボタン
	{
		if (attackinputpossible && !outpauseinputflg)
		{
			Attack();
		}

		attackinputpossible = false;
	}
	else
	{
		attackinputpossible = true;
	}

	if (inputstate != 0 && attackflg == false)
	{
		//移動ベクトルをプレイヤーが向くべき方向として保存
		targetLookDirection = moveVec;

		//正規化したベクトルにスピード倍したものを移動ベクトルとする
		if (VSize(moveVec) > 0)
		{
			moveVec = VNorm(moveVec);
		}
		moveVec = VScale(targetLookDirection, Speed);
	}
}