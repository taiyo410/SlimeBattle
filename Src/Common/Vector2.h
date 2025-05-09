#pragma once
class Vector2F;
class Vector2
{
public:

	//デフォルトコンストラクタ
	Vector2(void);

	//コンストラクタ
	Vector2(int ix, int iy);

	//デストラクタ
	~Vector2();

	//Vector2Fに変換する関数
	Vector2F ToVector2F(void);

	//メンバー変数
	int x;
	int y;
	int z;

private:
};
