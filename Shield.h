#pragma once

class Shield
{
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

public:
	//コンストラクタ
	Shield();
	//デストラクタ
	~Shield();
	//初期化
	void Initialize();
	//更新
	void Update(VECTOR characterPosition,float characterangle);
	//描画
	void Draw();

	VECTOR GetcapLeft() { return capLeft; }
	VECTOR GetcapRight() { return capRight; }
};