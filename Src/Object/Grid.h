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
	static const int HNUM = NUM / 2;

	//コンストラクタ
	Grid(void);

	//デストラクタ
	~Grid(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
};