#include<math.h>
#include"DxLib.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	//モデルロード・アニメーション設定
	model = MV1LoadModel("3D/player.mv1");
	runanim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, runanim);

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
	targetMoveDirection = VGet(1.0f, 0.0f, 1.0f);
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
	//移動
	InputMoveProcess(inputstate);

	//攻撃
	
	//アニメーション
	PlayAnimation();
	
	//向き設定
	UpdateAngle();

	//モデルポジション更新
	MV1SetPosition(model, position);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(model);
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="inputstate">入力状態</param>
/// <param name="wallhit">どこかの壁に当たっているか</param>
void Player::InputMoveProcess(const int inputstate)
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
		targetMoveDirection = moveVec;

		//正規化したベクトルにスピード倍したものを移動ベクトルとする
		moveVec = VScale(targetMoveDirection, Speed);
	}

	//ポジションに適用
	position = VAdd(position, moveVec);
}

/// <summary>
/// 向きを設定
/// </summary>
void Player::UpdateAngle()
{
	//プレイヤーの移動方向にモデルの方向を近づける
	float targetAngle;//目標の角度
	float difference;//目標角度と現在の角度の差

	//目標の方向ベクトルから角度値を算出する
	targetAngle = static_cast<float>(atan2(targetMoveDirection.x, targetMoveDirection.z));

	//目標の角度と現在の角度との差を割り出す
	//最初は引き算
	difference = targetAngle - angle;

	//ある方向からある方向の差が180度以上になることはないので差が180度以上になっていたら修正する
	if (difference < -DX_PI_F)
	{
		difference += DX_TWO_PI_F;
	}
	else if (difference > DX_PI_F)
	{
		difference -= DX_TWO_PI_F;
	}

	//角度の差を0に近づける
	if (difference > 0.0f)//差がマイナスの場合
	{
		difference -= AngleSpeed;
		if (difference < 0.0f)
		{
			difference = 0.0f;
		}
	}
	else//差がプラスの場合
	{
		difference += AngleSpeed;
		if (difference > 0.0f)
		{
			difference = 0.0f;
		}
	}

	//モデルの角度を更新
	angle = targetAngle - difference;

	MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
}

/// <summary>
/// アニメーション切り替え
/// </summary>
/// <param name="nextkind">次のアニメーション</param>
void Player::ChangeAnimation(AnimKind nextkind)
{
	//入れ替え時に前のモーションが有効だったらデタッチする
	if (nowPlayAnim != -1)
	{
		MV1DetachAnim(model, nowPlayAnim);
		nowPlayAnim = -1;
	}

	//新しくアニメーションをアタッチ
	nowPlayAnimKind = static_cast<int>(nextkind);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(nextkind));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);
	animplaytime = 0.0f;
}

/// <summary>
/// アニメーション再生
/// </summary>
void Player::PlayAnimation()
{
	//攻撃中の場合
	if (attackflg)
	{
		isanimflg = true;
	}

	//アニメーション再生
	if (isanimflg)
	{
		animplaytime += 0.5f;
	}

	//アニメーションがトータル時間に達したら
	if (animplaytime >= animtotaltime)
	{
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Punch))//攻撃モーションが終わった場合
		{
			attackflg = false;
			ChangeAnimation(AnimKind::Run);
		}
		if (nowPlayAnimKind == static_cast<int>(AnimKind::Run))//走るモーションが終わった場合
		{
			animplaytime = 0.0f;
		}
	}

	//再生時間をセット
	MV1SetAttachAnimTime(model, nowPlayAnim, animplaytime);
}

/// <summary>
/// 攻撃処理
/// </summary>
void Player::Attack()
{
	//攻撃モーションに変更
	if (attackflg == false)
	{
		ChangeAnimation(AnimKind::Punch);
		attackflg = true;
	}

}