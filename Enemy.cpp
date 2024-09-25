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
	angle = 0.0f;
	this->position = position;
	this->targetDirection = targetDirection;

	targetdistance = 0.0f;

	MV1SetPosition(model, this->position);
}

/// <summary>
/// 近いキャラクターの確認
/// </summary>
/// <param name="charapos">調べるキャラクターのポジション</param>
void Enemy::CheckNearCharacter(VECTOR charapos)
{
	//2キャラの距離を取る
	float calc = pow((position.x - charapos.x), 2.0f) + pow((position.y - charapos.y), 2.0f) + pow((position.z - position.z), 2.0f);
	float distance = sqrt(calc);

	//距離が前取ったのより短ければターゲットを更新
	if (distance < targetdistance)
	{
		targetCharaPos = charapos;
	}
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
	//動く

	//角度更新
	UpdateAngle();

	//ポジション反映
	MV1SetPosition(model, position);
}