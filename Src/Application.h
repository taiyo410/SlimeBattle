#pragma once
#include<string>
class InputManager;
class Application
{
public:
	//定数
	static constexpr int SCREEN_SIZE_X = 1200;
	static constexpr int SCREEN_SIZE_Y = 800;

	//static constexpr int SCREEN_SIZE_X = 1920;
	//static constexpr int SCREEN_SIZE_Y = 1080;


	static constexpr float FRAME_RATE = 1000 / 60;
#pragma region Path
	static const std::string PATH_MODEL;
	static const std::string PATH_IMAGE;
	static const std::string PATH_FONT;
	static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND;
#pragma endregion

	

	bool Init(void);		//初期化処理
	void Run(void);			//ゲームループ処理
	bool Release(void);		//解放処理

	//シングルトン化
	static void CreateInstance(void);
	//外部でインスタンスを利用可能とする
	static Application& GetInstance(void);

private:
#pragma region シングルトン化
	//インスタンス生成
	InputManager* inputManager_;

	//デフォルトコンストラクタ
	Application(void);
	//デストラクタ
	~Application(void);

	//コピーコンストラクタを利用不可にする
	Application(const Application& ins);

	//インスタンスの削除
	void Destroy(void);

	//静的なインスタンス初期化
	static Application* instance_;
#pragma endregion
	int currentTime_;			//現在の時間
	int lastFrameTime_;			//前回のフレーム実行の時間

	int frameCnt_;				//フレームカウント用
	int updateFrameRateTime_;	//フレームレートを更新した時間

	float frameRate_;			//フレームレート(表示用)

	//フレームレート計算
	void CalcFrameRate(void);

	//フレームレート表示（デバッグ用）
	void DrawFrameRate(void);


	
};
