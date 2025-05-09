#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./Manager/InputManager.h"
#include"./Manager/EffectManager.h"
#include"Application.h"
#include"./Manager/SceneManager.h"


//シングルトン化
//------------------------------------
//インスタンスの初期化処理
Application* Application::instance_ = nullptr;

const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_SOUND = "Data/Sound/";

//デフォルトコンストラクタ
Application::Application(void)
{

}

//デストラクタ
Application::~Application(void)
{

}

//初期化処理
bool Application::Init(void)
{

	//システム処理
	SetWindowText("2316004 井東太陽");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);		//ゲームウィンドウの表示方法

	if (DxLib_Init() == -1)
	{
		OutputDebugString("DxLibの初期化失敗");
		return false;
	}
	currentTime_ = 0;			
	lastFrameTime_ = 0;			

	frameCnt_;				
	updateFrameRateTime_ = 0;	

	frameRate_ = 0;			

	//操作制御インスタンス生成
	InputManager::CreateInput();

	//Effekseerの初期化
	EffectManager::CreateEffect();


	//インスタンスを生成
	SceneManager::CreateInstance();

	return true;
}

//ゲームループ処理
void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Sleep(1);	//システムに処理を返す

		//現在の時刻を取得
		currentTime_ = GetNowCount();
		//1/60秒経過していたら処理を実行する
		if (currentTime_ - lastFrameTime_ >= FRAME_RATE)
		{
			//フレーム実行時の時間を更新
			lastFrameTime_ = currentTime_;

			//フレーム数をカウント
			frameCnt_++;

			//ゲームのメイン処理
		//---------------------------------

		//描画処理
		//-------------------------------
		//描画する画面を裏の画面に設定
			SetDrawScreen(DX_SCREEN_BACK);

			//描画する画面の内容を消去
			ClearDrawScreen();

			SceneManager::GetInstance().Draw();	//各シーンの描画処理を呼び出す

			InputManager::GetInput().StepInput();			//入力ステップ
			InputManager::GetInput().StepPadInput();
			EffectManager::GetEffect().Update();
			SceneManager::GetInstance().Update();

			//フレームレート計算
			CalcFrameRate();

			//フレームレート表示（デバッグ用）
			//DrawFrameRate();

			ScreenFlip();						//裏の画面を表の画面に瞬間コピー
		}
		
	}
}

//解放処理
bool Application::Release(void)
{
	//管理マネージャの解放処理
	//シーン管理用
	SceneManager::GetInstance().Release();

	//操作マネージャの開放
	InputManager::GetInput().Destroy();

	//Effekseerを終了する
	Effkseer_End();

	//シングルトン化
	Destroy();

	

	//システム終了処理
	//----------------------------------
	DxLib_End();	//DXライブラリの終了
	return true;
}

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

//インスタンスのゲッタ
Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Destroy(void)
{
	delete instance_;		//インスタンス削除
	instance_ = nullptr;	//インスタンス領域を初期化
}

void Application::CalcFrameRate(void)
{
	//前回のフレームレート更新からの経過時間を求める
	int nDifTime = currentTime_ - updateFrameRateTime_;
	//前回のフレームレート更新から
	//1秒以上経過していたらフレームレートを更新する
	if (nDifTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//小数まで出したのでfloatにキャスト
		float fFrameCnt = static_cast<float>(frameCnt_ * 1000);

		//フレームレートを求める
		//理想通りなら60000 / 1000で60となる
		frameRate_ = fFrameCnt / nDifTime;

		//フレームカウントをクリア
		frameCnt_ = 0;

		//フレームレート更新時間を更新
		updateFrameRateTime_ = currentTime_;
	}
}

void Application::DrawFrameRate(void)
{
	DrawFormatString(SCREEN_SIZE_X - 90, 0, GetColor(255, 30, 30), "FPS[%.2f]", frameRate_);
}
