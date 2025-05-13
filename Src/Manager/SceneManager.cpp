#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./InputManager.h"
#include"./ModelManager.h"
#include"../Application.h"
#include"../Common/Fade.h"
#include"./Camera.h"
#include"../Object/Grid.h"
#include"../Common/CommonData.h"
#include"../Scene/SceneTitle.h"
#include"../Scene/SceneGame.h"
#include"../Scene/SceneGameOver.h"
#include"../Scene/ResultScene.h"
#include"./SceneManager.h"


//instance_の初期化処理
SceneManager* SceneManager::instance_ = nullptr;

//デフォルトコンストラクタ
SceneManager::SceneManager(void)
{
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::NONE;
	//フェードインスタンス生成
	fader_ = new Fader();
	fader_->Init();
	isSceneChanging_ = false;

	//フェードインスタンス生成
	fader_ = new Fader();
	fader_->Init();

	//カメラインスタンス生成
	camera_ = new Camera();
	camera_->Init();

	//グリッドインスタンス生成
	grid_ = new Grid();
	grid_->Init();

	scene_ = nullptr;

	//データインスタンス生成
	CommonData::CreateData();

	//インスタンス生成処理がない
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;

	//シーン切り替え状態の初期化
	isSceneChanging_ = true;

	//対戦状態
	type_ = TYPE::PVE;
}

//デストラクタ
SceneManager::~SceneManager(void)
{

}
//初期化処理
bool SceneManager::Init(void)		
{
	Init3D();

	//データインスタンス生成
	CommonData::CreateData();

	//インスタンス生成処理がない
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;

	ChangeScene(SCENE_ID::TITLE, false);

	//タイトルシーンからフェードインで表示
	fader_->SetFade(Fader::STATE::FADE_IN);

	return true;
}

/// <summary>
/// 3Dの初期化処理
/// </summary>
/// <param name=""></param>
void SceneManager::Init3D(void)
{
	//背景色設定
	SetBackgroundColor(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B);

	//Zバッファを有効にする)
	SetUseZBuffer3D(true);

	//Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	//3Dバックカリング有効にする
	SetUseBackCulling(true);
}
//更新処理
void SceneManager::Update(void)
{
	//フェード処理
	fader_->Update();
	//フェード中
	if (isSceneChanging_ == true)
	{
		Fade();
	}
	else
	{
 		scene_->Update();
		camera_->Update();
	}
	UpdateEffekseer3D();

	////グリッドの更新処理
	grid_->Update();
}
//描画処理
void SceneManager::Draw(void)
{
	//描画先グラフィック領域の指定
	// (3D描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	//画面を初期化
	ClearDrawScreen();

	//カメラ設定
	camera_->SetBeforeDraw();
	

	//各シーンの描画処理
	scene_->Draw();

	//カメラデバッグ等
	camera_->Draw();

	//Effekseerにより再生中のエフェクト描画
	DrawEffekseer3D();

	//フェード
	fader_->Draw();

	

}
//解放処理
bool SceneManager::Release(void)		
{
	//シーンの開放処理
	ReleaseScene(sceneID_);

	//データの解放処理
	CommonData::GetData().Destroy();

	grid_->Release();
	delete grid_;
	grid_ = nullptr;

	camera_->Release();
	delete camera_;
	camera_ = nullptr;

	delete fader_;
	fader_ = nullptr;	
	return true;
}


//シーン切り替え
void SceneManager::ChangeScene(SCENE_ID nextID, bool isToFade)
{
	waitSceneID_ = nextID;
	if (isToFade)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else
	{
		DoChangeScene();
	}
}
//シーンを切り替える
void SceneManager::DoChangeScene(void)
{
	//現在のシーンの開放
	ReleaseScene(sceneID_);

		//次に移動するシーンが入ってる
		sceneID_ = waitSceneID_;
	switch (sceneID_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		break;
	case SCENE_ID::GAME:
		camera_->SetCameraWork(GAME_CAMERA_POS, GAME_CAMERA_ANGLE);
		scene_ = new SceneGame();
		break;
	case SCENE_ID::RESULT:
		camera_->SetCameraWork(TITLE_CAMERA_POS, TITLE_CAMERA_ANGLE);
		scene_ = new ResultScene();
	default:
		break;
	}
	scene_->Init();

	//シーンの遷移が終了したので、次のシーンをクリアする
	waitSceneID_ = SCENE_ID::NONE;
}

//フェード実施用関数
void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			//暗転後シーン変更
			DoChangeScene();
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			//明転後、シーン遷移終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	}
}

//シーンの解放
void SceneManager::ReleaseScene(SCENE_ID isceneID)
{
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}
//シングルトン化
//--------------------------------
void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}
//外部でインスタンスを利用可能とするためにインスタンスで返す関数を用意
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Destroy(void)
{
	delete instance_;		//インスタンス削除
	instance_ = nullptr;	//インスタンス領域を初期化
}

//対戦状態
bool SceneManager::GetType(TYPE value)
{
	if (type_ == value)
	{
		return true;
	}
	return false;
}

Camera* SceneManager::GetCamera(void)
{
	return camera_;
}
