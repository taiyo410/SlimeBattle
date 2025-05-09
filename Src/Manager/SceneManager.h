//#pragma once
#include<DxLib.h>
#include"../Common/CommonData.h"
//前方宣言
class Fader;
class InputManager;
class ModelManager;
class SceneBase;
class CommonData;
class SceneTitle;
class SceneGame;
class Camera;
class Grid;

class SceneManager
{

public:
	//定数
	//************************************
	//各シーンのカメラ座標と角度
	//ゲームシーン
	static constexpr VECTOR GAME_CAMERA_POS = { 0.0f,600.0f,-200.0f };
	static constexpr VECTOR GAME_CAMERA_ANGLE = { 75.0f * DX_PI_F / 180.0f,0.0f,0.0f };

	//タイトルシーン
	static constexpr VECTOR TITLE_CAMERA_POS = { 0.0f,100.0f,-200.0f };
	static constexpr VECTOR TITLE_CAMERA_ANGLE = { 20.0f * DX_PI_F / 180.0f,0.0f,0.0f };

	//************************************
	//列挙型
	enum class SCENE_ID
	{
		NONE		//未設定
		,TITLE		//タイトル
		,GAME		//ゲーム
		,RESULT		//リザルト
		,MAX
	};

	//敵味方種別
	enum class TYPE
	{
		PVP
		,PVE
	};
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理続行		false:処理停止</returns>
	bool Init(void);		

	/// <summary>
	/// 3Dの初期化処理
	/// </summary>
	/// <param name=""></param>
	void Init3D(void);

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
	/// 解放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理続行		false:処理停止</returns>
	bool Release(void);		//解放処理

	/// <summary>
	/// シーン遷移用関数
	/// </summary>
	/// <param name="nextID">次のシーンの設定</param>
	/// <param name="isToFade">true:フェードする	false:フェードしない</param>
	void ChangeScene(SCENE_ID nextID, bool isToFade);

	//シングルトン化
	//--------------------------------
	static void CreateInstance(void);
	//外部でインスタンスを利用可能とするためにインスタンスで返す関数を用意
	static SceneManager& GetInstance(void);

	//対戦状態
	bool GetType(TYPE value);

	//カメラのインスタンスを返す
	Camera* GetCamera(void);

private:
	//メンバー変数
	SCENE_ID sceneID_;		//今のシーン格納
	SCENE_ID waitSceneID_;	//次のシーン格納

	bool isSceneChanging_;	//シーン遷移中かどうか（true:遷移中）
	//管理マネージャ
	SceneBase* scene_;		//シーンインスタンス
	SceneTitle* title_;		//タイトル
	SceneGame* game_;       //ゲーム

	InputManager* inputManager_;	//操作制御インスタンス
	CommonData* data_;
	Fader* fader_;					//フェードインスタンス
	Camera* camera_;				//カメラインスタンス
	Grid* grid_;					//グリッドインスタンス
	ModelManager* model_;			//モデルインスタンス
	//メンバー変数
	//対戦状態
	TYPE type_;
	CommonData::MODE mode_;
	
	
	/// <summary>
	/// シーン切り替え
	/// </summary>
	/// <param name=""></param>
	void DoChangeScene(void);

	/// <summary>
	/// フェード実施用
	/// </summary>
	/// <param name=""></param>
	void Fade(void);

	/// <summary>
	/// 指定シーンの開放
	/// </summary>
	/// <param name="isceneID"></param>
	void ReleaseScene(SCENE_ID isceneID);

	//シングルトン化
	//-------------------------------------
	//デフォルトコンストラクタ
	SceneManager(void);
	
	//デストラクタ
	~SceneManager(void);

	//コピーコンストラクタを利用不可にする
	SceneManager(const SceneManager& ins);

	/// <summary>
	/// インスタンスの削除
	/// </summary>
	/// <param name=""></param>
	void Destroy(void);

	//静的なインスタンス初期化
	static SceneManager* instance_;
};

