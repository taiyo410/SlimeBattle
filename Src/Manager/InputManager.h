#pragma once
class InputManager
{
	//メンバー関数
public:
	//定数
	//-----------------------
	static constexpr int KEY_BUF_LEN = 256;

	static constexpr int PAD_NUM = 2;



	



	/// <summary>
	/// 文字列の分割
	/// </summary>
	/// <param name=""></param>
	void InitInput(void);

	/// <summary>
	/// 文字列の分割
	/// </summary>
	/// <param name=""></param>
	void StepInput(void);

#pragma region キーボード操作
	/// <summary>
	/// 単純に押されているか(Check_Hit_Keyと同じ処理)
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns>true:押された		false:押されてない</returns>
	bool IsKeyDown(int key_code);

	/// <summary>
	/// 今押された
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns></returns>
	bool IsKeyPush(int key_code);

	/// <summary>
	/// 長押し
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns>true:長押しされた		false:長押しされてない</returns>
	bool IsKeyKeep(int key_code);

	/// <summary>
	/// 今離された
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns>true:離された		false:離されてない</returns>
	bool IsKeyRelease(int key_code);
#pragma endregion
#pragma region コントローラー
	//制御処理
	void StepPadInput(void);

	/// <summary>
/// 単純に押されているか(Check_Hit_Keyと同じ処理)
/// </summary>
/// <param name="key_code">キーの場所</param>
/// <returns>true:押された		false:押されてない</returns>
	bool IsPadDown(int padNum,int key_code);

	/// <summary>
	/// 今押された
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns></returns>
	bool IsPadPush(int padNum, int key_code);

	/// <summary>
	/// 長押し
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns>true:長押しされた		false:長押しされてない</returns>
	bool IsPadKeep(int padNum, int key_code);

	/// <summary>
	/// 今離された
	/// </summary>
	/// <param name="key_code">キーの場所</param>
	/// <returns>true:離された		false:離されてない</returns>
	bool IsPadRelease(int padNum, int key_code);
#pragma endregion

	

	//インスタンスの解放
	void ReleaseInput(void);

	//シングルトン化
	//------------------------------
	static void CreateInput(void);

	//外部でインスタンスを利用可能にするために
	//インスタンスで返す関数を用意
	static InputManager& GetInput(void);

	//インスタンスの削除
	void Destroy(void);
	
private:
	//シングルトン化
	//デフォルトコンストラクタ
	InputManager(void);
	//デストラクタ
	~InputManager(void);
	

	//コピーコンストラクタを利用不可にする
	InputManager(const InputManager& ins);


	//前フレームのキー情報
	int prePadBuf_[PAD_NUM];

	//現在フレームのキー情報
	int currentPadBuf_[PAD_NUM];

	//メンバー変数
	//現在フレームのキー情報
	char currentKeyBuf_[256];

	//前フレームのキー情報
	char preKeyBuf_[256];


	//静的なインスタンス初期化
	static InputManager* input_;
};
