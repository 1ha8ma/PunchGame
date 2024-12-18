#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"DxLib.h"
#include"Utility.h"
#include"Stage.h"
#include"Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="handle">モデルハンドル</param>
/// <param name="modelsize">モデルサイズ</param>
/// <param name="position">ポジション</param>
/// <param name="targetDirection">向く方向</param>
Enemy::Enemy(int handle,float modelsize,VECTOR position,VECTOR targetDirection,int cpunumber)
{
	model = handle;
	mynumber = cpunumber;

	MV1SetScale(model, VGet(modelsize, modelsize, modelsize));

	Initialize(position, targetDirection);
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	MV1DetachAnim(model, nowPlayAnim);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="targetDirection">向く方向</param>
void Enemy::Initialize(VECTOR position, VECTOR targetDirection)
{
	BaseInitialize();

	//乱数初期化
	srand((unsigned int)time(NULL));

	//ポジション初期化
	this->position = position;
	capsuleTop = VAdd(this->position, VGet(0, 600, 0));
	capsuleBottom = VAdd(this->position, VGet(0, 0, 0));
	this->targetLookDirection = targetDirection;
	
	//攻撃クールタイム
	cooltimeflg = false;
	cooltimeflame = 0;

	//移動関係
	NowMoveKind = MoveKind::charachase;
	moveflame = 0;
	moveangle = 0;
	moveonflg = true;

	//ランダム歩き関係
	SetWalkTargetPositionflg = false;

	//追いかけ関係初期化
	//ターゲット設定
	while (1)
	{
		target = rand() % OllCharaNum;
		if (target != mynumber)
		{
			break;
		}
	}

	InitializeAngle();
	OtherClassInitialize();
	MV1SetPosition(model, this->position);
}

/// <summary>
/// ターゲット設定
/// </summary>
void Enemy::SetTargetChara(std::vector<int> outchara)
{
	//ランダムで追うキャラを決める
	while (1)
	{
		bool ok = true;//キャラ決定フラグ
		bool charachange = false;//キャラ交代フラグ

		for (int i = 0; i < outchara.size(); i++)
		{
			if (target == outchara[i] || target == mynumber)
			{
				charachange = true;
			}
		}

		//脱落したか一定時間経っていればターゲット変更
		if (charachange)
		{
			target = rand() % OllCharaNum;

			//もし脱落していたらもう一度決める
			for (int i = 0; i < outchara.size(); i++)
			{
				if (target == outchara[i] || target == mynumber)
				{
					ok = false;
				}
			}
		}

		//決まったら
		if (ok)
		{
			break;
		}
	}
}

/// <summary>
/// 移動処理
/// </summary>
void Enemy::Move(std::vector<int> outchara)
{
	switch (NowMoveKind)
	{
	case(MoveKind::charachase)://目標を決めて移動
	{
		//ターゲット設定
		SetTargetChara(outchara);

		//ターゲットポジションを目標キャラの後ろで射程範囲の半分の位置に設定する
		targetPosition = targetCharaPosition;
		targetPosition.x += cos(targetCharaAngle + DX_PI_F) * Range / 2;
		targetPosition.z += sin(targetCharaAngle + DX_PI_F) * Range / 2;

		//ターゲットとの距離を取る
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//目標角度設定
		if (!attackflg)
		{
			targetLookDirection.x = targetCharaPosition.x;
			targetLookDirection.z = targetCharaPosition.z;
		}

		//射程に入り、フラグが良ければ攻撃
		if (targetdistance < Range && !attackflg && !cooltimeflg)
		{
			//目標と自分のポジションの角度を取る
			float characterWithcharacterAngle = atan2(targetCharaPosition.x-position.x, targetCharaPosition.z-position.z);
			//角度を目標のポジションに向ける
			angle = characterWithcharacterAngle;
			//モデル回転
			MV1SetRotationXYZ(model, VGet(0.0f, angle + DX_PI_F, 0.0f));
			//クールタイム設定
			cooltimeflg = true;
			cooltimeflame = 0;
			//攻撃
			Attack();
		}
		else
		{
			//角度設定
			moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);
			if (!attackflg)
			{
				//角度更新
				UpdateAngle();
			}
		}
		//射程範囲外であれば進める
		if (targetdistance > Range)
		{
			moveonflg = true;
		}
		else
		{
			moveonflg = false;
		}

		//フレーム加算
		if (cooltimeflg)
		{
			cooltimeflame++;
			if (cooltimeflame == 100)
			{
				cooltimeflg = false;
			}
		}

		//一定時間で追い方の再抽選
		if (moveflame >= 150)
		{
			int random = rand() % 3;
			if (random == MoveKind::charachase)
			{
				NowMoveKind = MoveKind::charachase;
			}
			else
			{
				NowMoveKind = MoveKind::randomwalk;
			}

			moveflame = 0;
		}

	}
	break;
	case(MoveKind::randomwalk)://ランダムな場所に移動
	{
		//目的地設定
		if (!SetWalkTargetPositionflg)
		{
			targetPosition.x = (rand() % static_cast<int>((Stage::StageRight - Stage::StageLeft))) + Stage::StageLeft;
			targetPosition.z = (rand() % static_cast<int>((Stage::StageTop - Stage::StageBottom))) + Stage::StageBottom;

			targetLookDirection.x = targetPosition.x;
			targetLookDirection.z = targetPosition.z;

			SetWalkTargetPositionflg = true;
		}

		//ターゲットとの距離を取る
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//至近距離になったら目的地にポジションを移す
		if (targetdistance <= Speed)
		{
			position.x = targetPosition.x;
			position.z = targetPosition.z;
			moveonflg = false;
		}
		else
		{
			moveonflg = true;
		}

		//角度設定
		moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);
		//角度更新
		UpdateAngle();

		//一定時間で追い方の再抽選
		if (moveflame >= 70)
		{
			int random = rand() % 3;
			if (random == MoveKind::charachase)
			{
				NowMoveKind = MoveKind::charachase;
			}
			else
			{
				NowMoveKind = MoveKind::randomwalk;
			}

			SetWalkTargetPositionflg = false;
			moveflame = 0;
		}

	}
	break;

	}

	//速度設定
	moveVec.x = cos(moveangle) * Speed;
	moveVec.y = 0.0f;
	moveVec.z = sin(moveangle) * Speed;

	//進ませる
	if (moveonflg && !attackflg)
	{
		isanimflg = true;
	}
	else
	{
		moveVec = VGet(0.0f, 0.0f, 0.0f);
		isanimflg = false;
	}
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update(std::vector<int> outchara)
{
	//動く
	Move(outchara);

	//当たり判定を付けるか判断
	CheckAttackOnCollision();

	//アニメーション再生
	PlayAnimation();

	//ポジション反映
	MV1SetPosition(model, position);

	//フレーム加算
	moveflame++;
}

/// <summary>
/// 盾同士の当たり判定更新
/// </summary>
/// <param name="shieldleft">対象キャラの盾左</param>
/// <param name="shieldright">対象キャラの盾右</param>
void Enemy::UpdateShieldWithShield(VECTOR shieldleft, VECTOR shieldright)
{
	//当たっていたら
	if (ShieldWithShield(GetShieldLeft(), GetShieldRight(), shieldleft, shieldright))
	{
		RemoveShield(shieldleft, shieldright);
	}
}

/// <summary>
/// ポジション更新
/// </summary>
void Enemy::UpdatePosition()
{
	ReflectPosition();
}