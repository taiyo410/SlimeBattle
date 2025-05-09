//#pragma once
#include"./SceneBase.h"
class InputManager;
class SceneGameOver :public SceneBase
{
public:
	////メンバー関数
	//	//------------------------

	//	//デフォルトコンストラクタ
	//SceneGame(void);

	////デストラクタ
	//~SceneGame(void);

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理が続く	false:処理が止まる</returns>
	bool Init(void) override;		

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	void Update(void) override;		
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	void Draw(void) override;		

	/// <summary>
	/// 解放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理が続く	false:処理が止まる</returns>
	bool Release(void) override;		

private:
	//ポインタ宣言
	//--------------------------
	//操作制御
	InputManager *inputManager_;
	//メンバー変数
	//SceneManager* sceneManager_;
	int bgImage_;

	/// <summary>
	/// デバッグ用関数
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);
};

