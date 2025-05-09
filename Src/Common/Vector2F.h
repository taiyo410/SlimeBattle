#pragma once
class Vector2F
{
public:

	//デフォルトコンストラクタ
	Vector2F(void);

	//コンストラクタ
	Vector2F(float ix, float iy,float iz);

	//デストラクタ
	~Vector2F();

	//Vector2Fへ変換する
	Vector2 ToVector2(void);

	//メンバー変数
	float x;
	float y;
	float z;
private:
};
