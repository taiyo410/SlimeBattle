#pragma once
#include"../Utility/SunUtility.h"
#include "ItemBase.h"
#include "SlimeBase.h"
class Speaker: public ItemBase
{
public:
	//広範囲攻撃ジャンプパワー
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//広範囲攻撃クールタイム
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//広範囲攻撃チャージ最大値
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 1.3;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//カメラシェイク関連
	//時間
	static constexpr int SHALE_CNT = 10;
	//振れ幅
	static constexpr int SHAKE_LIMIT = 10;

	////範囲攻撃の当たり判定用
	//static constexpr float WAID_ATK_COL = SlimeBase::RADIUS * 3;

	//広範囲攻撃の落下時用の重力
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;
	//広範囲攻撃
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};

	void Update(void)override;
	void Draw(void)override;
	void SetParam(void)override;
	//広範囲攻撃
	void UpdateWaidAttack(void)override;

	


	
private:
	
};

