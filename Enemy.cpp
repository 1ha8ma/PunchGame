#include<math.h>
#include"DxLib.h"
#include"Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="modelhandle">モデルハンドル番号</param>
/// <param name="modelsize">モデルサイズ</param>
/// <param name="position">ポジション</param>
/// <param name="targetDirection">向く方向</param>
Enemy::Enemy(const TCHAR *modelhandle,float modelsize,VECTOR position,VECTOR targetDirection)
{
	model = MV1LoadModel(modelhandle);
	nowPlayAnim = MV1AttachAnim(model, static_cast<int>(AnimKind::Run));
	animtotaltime = MV1GetAttachAnimTotalTime(model, nowPlayAnim);

	MV1SetScale(model, VGet(modelsize, modelsize, modelsize));

	Initialize(position, targetDirection);
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="targetDirection">向く方向</param>
void Enemy::Initialize(VECTOR position, VECTOR targetDirection)
{
	//アニメーション初期化
	animplaytime = 0.0f;
	nowPlayAnimKind = static_cast<int>(AnimKind::Run);
	nowPlayAnim = static_cast<int>(AnimKind::Run);
	prevPlayAnim = -1;

	angle = 0.0f;
	this->position = position;
	this->targetLookDirection = targetDirection;

	targetdistance = 10000.0f;
	targetCharaAngle = 0.0f;

	MV1SetPosition(model, this->position);
}

/// <summary>
/// 近いキャラクターの確認
/// </summary>
/// <param name="charapos">調べるキャラクターのポジション</param>
void Enemy::CheckNearCharacter(VECTOR charapos)
{
	//2キャラの距離を取る
	float calc = pow((position.x - charapos.x), 2.0f) + pow((position.y - charapos.y), 2.0f) + pow((position.z - charapos.z), 2.0f);
	float distance = sqrt(calc);

	//距離が前取ったのより短ければターゲットを更新
	if (distance < targetdistance)
	{
		targetdistance = distance;
		targetCharaPos = charapos;
	}
}

/// <summary>
/// 移動処理
/// </summary>
void Enemy::Move()
{
	//角度設定
	targetCharaAngle = atan2(targetCharaPos.z - position.z, targetCharaPos.x - position.x);
	vx = cos(targetCharaAngle) * Speed;
	vz = sin(targetCharaAngle) * Speed;

	//進ませる
	if (targetdistance > 1000)
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
void Enemy::Update()
{
	//動く
	Move();

	//アニメーション再生
	PlayAnimation();

	//角度更新
	UpdateAngle();

	//ポジション反映
	MV1SetPosition(model, position);
}