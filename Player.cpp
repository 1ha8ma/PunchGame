#include<math.h>
#include"DxLib.h"
#include"Utility.h"
#include"Player.h"
#include"Loader.h"

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

}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	BaseInitialize();

	//ポジション初期化
	position = VGet(-1000.0f, 100.0f, -700.0f);

	//移動角度設定
	moveVec = VGet(0, 0, 0);
	targetLookDirection = VGet(1.0f, 0.0f, 1.0f);

	InitializeAngle();
	OtherClassInitialize();

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
/// 終了、脱落後も続く更新
/// </summary>
/// <param name="playerattackshieldhit">プレイヤーの攻撃が盾に当たっているか</param>
void Player::ForeverUpdate(bool playerattackshieldhit)
{
	//他クラスの処理
	OtherClassUpdate(playerattackshieldhit);

	//カプセル更新
	UpdateCapsule();

	//エフェクト更新
	UpdateEffect(playerattackshieldhit);

	Blow();
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
		if (position.x <= 1600 && (4 & inputstate) == 4)//右
		{
			moveVec = VAdd(moveVec, VGet(1.0f, 0.0f, 0.0f));
		}
		if (position.x >= -1500 && (2 & inputstate) == 2)//左
		{
			moveVec = VAdd(moveVec, VGet(-1.0f, 0.0f, 0.0f));
		}
		if (position.z<=1500&&(8 & inputstate) == 8)//上
		{
			moveVec = VAdd(moveVec, VGet(0.0f, 0.0f, 1.0f));
		}
		if (position.z >= -1000 && (1 & inputstate) == 1)//下
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
		targetLookDirection = moveVec;

		//正規化したベクトルにスピード倍したものを移動ベクトルとする
		moveVec = VScale(targetLookDirection, Speed);
	}

	//ポジションに適用
	position = VAdd(position, moveVec);
}