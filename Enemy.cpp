#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"DxLib.h"
#include"Utility.h"
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
	case(MoveKind::charachase):
	{
		//ターゲット設定
		SetTargetChara(outchara);

		//ターゲットとの距離を取る
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//角度設定
		if (attackflg == false)
		{
			targetLookDirection.x = targetPosition.x;
			targetLookDirection.z = targetPosition.z;
		}

		//射程に入り、差が一定以下でフラグが良ければ攻撃
		if (targetdistance < 1000 && attackflg == false && cooltimeflg == false)
		{
			cooltimeflg = true;
			cooltimeflame = 0;
			Attack();
		}
		//射程範囲外であれば進める
		if (targetdistance > 1000)
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
	case(MoveKind::randomwalk):
	{
		//目的地設定
		if (SetWalkTargetPositionflg == false)
		{
			targetPosition.x = (rand() % static_cast<int>((StageRight - StageLeft))) + StageLeft;
			targetPosition.z = (rand() % static_cast<int>((StageTop - StageBottom)))+ StageBottom;

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

	//角度設定
	moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);

	//速度設定
	vx = cos(moveangle) * Speed;
	vz = sin(moveangle) * Speed;

	//進ませる
	if (moveonflg && attackflg == false)
	{
		isanimflg = true;
		position.x += vx;
		position.z += vz;
	}
	else
	{
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

	//アニメーション再生
	PlayAnimation();

	//角度更新
	UpdateAngle();

	//カプセル更新
	UpdateCapsule();

	//ポジション反映
	MV1SetPosition(model, position);

	moveflame++;
}