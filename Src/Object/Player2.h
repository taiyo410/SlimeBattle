#pragma once
#include "Player.h"
class Player2 :public Player 
{
public:
	//定数
	//スライムの色
	static constexpr int SLIME_COLOR = 0xED784A;

	//初期座標
	static constexpr VECTOR INIT_POS = { Stage::STAGE_ONE_SQUARE * 3,RADIUS,0.0f };

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
	/// <returns></returns>
	bool Release(void) override;

	void DrawDebug(void)override;
	
protected:
	
	void KnockBuckUpdate(void);

	void KnockBack(void)override;

	/// <summary>
	/// パラメタの初期化
	/// </summary>
	/// <param name=""></param>
	void SetParam(void)override;

	

private:

};

