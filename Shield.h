#pragma once

class Shield
{
private:
	const float DistanceWithCharacter = 330.0f;//キャラクターと盾の距離
	const float AngleSpeed = 0.2f;//角度変更速度

	int model;//モデル
	VECTOR position;//ポジション
	float angle;//角度

	bool o;
	float anglecopy;

	
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
};