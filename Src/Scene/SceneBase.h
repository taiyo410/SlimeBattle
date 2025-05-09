#pragma once
class SceneBase
{
public:
	//デフォルトコンストラクタ
	SceneBase(void);

	//デストラクタ(仮想が分からんから聞く)
	virtual	~SceneBase(void);

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理続行		false:処理停止</returns>
	virtual bool Init(void);

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	virtual void Draw(void);

	/// <summary>
	/// 解放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理続行		false:処理停止</returns>
	virtual bool Release(void);		//解放処理


private:
	//メンバー変数
};