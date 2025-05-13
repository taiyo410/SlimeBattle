#pragma once
class Grid
{
public:
	//線の長さ
	static constexpr float LEN = 800.0f;

	//線の長さの半分
	static constexpr float HLEN = LEN / 2.0f;

	//線の間隔
	static constexpr float TERM = 60.0f;

	//線の数
	static constexpr float NUM = static_cast<int>(LEN / TERM);

	//線の数の半分
	static const int HNUM = static_cast<int>(NUM / 2);

	//球の半径
	static constexpr float RADIUS = 15.0f;

	//球の角度の分割数
	static constexpr int DIV_NUM = 8;

	//コンストラクタ
	Grid(void);

	//デストラクタ
	~Grid(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
};