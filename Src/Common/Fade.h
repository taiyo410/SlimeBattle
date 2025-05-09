#pragma once

class Fader
{
public:
	//フェードが進む速さ
	static constexpr float SPEED_ALPHA = 5;

	//状態
	enum class STATE
	{
		NONE
		,FADE_OUT	//徐々に暗転
		,FADE_IN	//徐々に明転
	};

	//コンストラクタ
	Fader(void);

	//デストラクタ
	~Fader(void);
	

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	void Update(void);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	void Draw(void);

	/// <summary>
	/// フェード状態のゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns>フェード状態</returns>
	STATE GetState(void);

	/// <summary>
	/// フェード状態が終了しているか
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:終了している		false:終了していない</returns>
	bool IsEnd(void);

	/// <summary>
	/// フェードを設定する
	/// </summary>
	/// <param name="state">フェードの状態</param>
	void SetFade(STATE state);

private:
	//状態
	STATE state_;

	//透明度
	float alpha_;

	bool isPreEnd_;

	//フェード処理の終了判定
	bool isEnd_;

};