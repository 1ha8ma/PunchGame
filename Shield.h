#pragma once

class Shield
{
public:
	//コンストラクタ
	Shield();
	//デストラクタ
	~Shield();
	//初期化
	void Initialize(VECTOR charaposition, float characterangle);
	//更新
	void Update(VECTOR characterPosition, float characterangle);
	//ポジション反映
	void ReflectPosition(VECTOR newposition);
	//描画
	void Draw();

	const float ShieldCapsuleRadius = 20.0f;
	VECTOR GetPosition() { return position; }
	VECTOR GetcapLeft() { return capLeft; }
	VECTOR GetcapRight() { return capRight; }

private:
	const float DistanceWithCharacter = 330.0f;//キャラクターと盾の距離
	const float CapsuleRadius = 50.0f;//カプセル半径

	int model;//モデルハンドル
	VECTOR position;//ポジション
	float angle;//角度

	//カプセル
	VECTOR capLeft;
	VECTOR capRight;

	//角度更新
	void UpdateAngle(float characterAngle);
	//角度初期化
	void InitializeAngle(float charaangle);
};