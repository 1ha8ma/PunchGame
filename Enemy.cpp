#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"DxLib.h"
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

	//追いかけ関係初期化
	attackaftercharachange = false;
	targetCharaAngle = 0.0f;
	chaseflame = 0;
	moveangle = 0;

	win = false;

	//ターゲット設定
	while (1)
	{
		target = rand() % 4;
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
void Enemy::SetTarget(std::vector<int> outchara)
{
	//ランダムで追うキャラを決める
	while (1)
	{
		bool ok = true;//キャラ決定フラグ
		bool charachange = false;//追う対象が脱落した場合

		for (int i = 0; i < outchara.size(); i++)
		{
			if (target == outchara[i] || target == mynumber || attackaftercharachange)
			{
				if (attackaftercharachange)
				{
					int a = 0;
				}
				charachange = true;
			}
		}

		//脱落したか一定時間経っていればターゲット変更
		if (chaseflame >= 500 || charachange)
		{
			target = rand() % 4;
			chaseflame = 0;

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
	switch (win)
	{
	case false://勝利していない場合
	{
		//ターゲット設定
		SetTarget(outchara);

		if (outchara.size() == 4 && outflg == false)
		{
			win = true;
			break;
		}

		//角度設定
		moveangle = atan2(targetPosition.z - position.z, targetPosition.x - position.x);

		//ターゲットとの距離を取る
		float calc = pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2) + pow(targetPosition.z - position.z, 2);
		targetdistance = sqrt(calc);

		//速度設定
		vx = cos(moveangle) * Speed;
		vz = sin(moveangle) * Speed;

		//角度設定
		if (attackflg == false)
		{
			targetLookDirection.x = targetPosition.x;
			targetLookDirection.z = targetPosition.z;
		}

		//目標との角度の差を取る
		float targetAngle = static_cast<float>(atan2(targetLookDirection.x, targetLookDirection.z));
		float angledif = abs(targetAngle - angle);

		if (angledif > 10)
		{
			int a = 0;
		}

		//射程に入り、差が一定以下でフラグが良ければ攻撃
		if (targetdistance < 1000 && angledif < 0.2 && attackflg == false && cooltimeflg == false)
		{
			cooltimeflg = true;
			cooltimeflame = 0;
			Attack();
		}

		//進ませる
		if (targetdistance > 1000 && attackflg == false)
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
	break;

	case true:
	{

	}
	break;

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

	//フレーム加算
	if (cooltimeflg)
	{
		cooltimeflame++;
		if (cooltimeflame == 100)
		{
			cooltimeflg = false;
			attackaftercharachange = true;
		}
		else
		{
			attackaftercharachange = false;
		}
	}
	else
	{
		attackaftercharachange = false;
	}
	chaseflame++;
}