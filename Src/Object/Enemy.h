#pragma once
#include<DxLib.h>
#include"../Utility/SunUtility.h"
#include"./SlimeBase.h"
class SceneGame;
class Player;
class Enemy:public SlimeBase
{
public:

	//定数
	//敵が近づくスピード
	static constexpr float MOVE_SPEED = 1.0f;
	//体力
	static constexpr int MAX_HP = 200;

	//敵の移動を続ける条件までの差
	static constexpr int MOVE_POS_E2P = 90;

	//クールタイム
	static constexpr int COOL_TIME_MAX = SunUtility::DEFAULT_FPS * 1;

	//広範囲攻撃ジャンプパワー
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//広範囲攻撃クールタイム
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//広範囲攻撃チャージ最大値
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 1.3;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//スタミナ回復状態のカウント
	static constexpr float STAMINA_RECOV_TIME = SunUtility::DEFAULT_FPS * 5;

	//突進攻撃が終わった後のクールタイム
	static constexpr float NORMAL_ATK_COOLTIME = SunUtility::DEFAULT_FPS * 2;

	//広範囲攻撃の落下時用の重力
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;
	//溜め時間
	static constexpr float CHARGE_CNT = 5.0f;
	//落ちている時間
	static constexpr int FALL_CNT = SunUtility::DEFAULT_FPS * 2;

	//

	//復活カウント
	static constexpr int REVIVAL_CNT_MAX = SunUtility::DEFAULT_FPS * 2;


	

	////敵がプレイヤーに近づく処理
	//enum class MOVE_DIR
	//{
	//	NONE
	//	, FLONT
	//	, BACK
	//	, LEFT
	//	, RIGHT
	//	, MAX
	//};

	//広範囲攻撃
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};

	//敵の攻めと逃げ
	enum class ACT
	{
		Attack
		,ESCAPE
	};

	

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	//bool Init (SceneGame* parent)override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	
	void Update(void) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	void Draw(void) override;

	/// <summary>
	/// 解放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void) override;

	/// <summary>
	/// デバッグ用の関数
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);

	//状態変化用関数
	void ChangeState(CommonData::ENEMYSTATE state);

	//広範囲攻撃用の状態変化用
	//void ChangeWaidAtkState(const WAID_ATK waidAtk);

	//スタミナとフレームの減算
	void FrameComsumption(void);

	//スタミナ回復処理
	void StaminaRecovery(void);

	//敵の状態ゲッタ
	CommonData::ENEMYSTATE GetState(void);


	//広範囲攻撃状態ヘッダ
	//Enemy::WAID_ATK GetWaidAtkState(void) const;

	//敵状態のセッター
	void SetEnemyState(const CommonData::ENEMYSTATE enemyState);
	//方向を決める関数
	void MoveDir(void);

	//状態ごとの更新
	void StateUpdate(void)override;

#pragma region 状態ごとの処理
	//クール中
	void UpdateNone(void);

	//考え中
	void UpdateThink(void);

	//プレイヤーまで近づく
	void UpdateMove(void);

	//ステップ
	void UpdateStep(void);

	//チャージ
	void UpdateCharge(void);

	//ノックバック
	void UpdateKnockBuck(void);

	//突進
	void UpdateNormalAttack(void);

	//広範囲攻撃
	void UpdateWaidAttack(void);

	//落ちている状態
	void FallUpdate(void);

	//復活処理
	void RevivalUpdate(void);

	//共通の状態処理
	void DebuffUpdate(void);

#pragma endregion
	

	

	//当たり判定のゲッタ
	float GetWaidCol(void)const;
	void ChangeWaidAtkState(const SlimeBase::WAID_ATK waidAtk)override;
	
private:
	//ポインタ格納領域
	Player* player_;
	bool isMove_;	//動いてるか判定


	int waidChargeCnt_;	//広範囲攻撃の溜めカウント
	int waidAtkCoolTime_;	//広範囲攻撃のクールタイム
	float waidAtkRadius_;		//広範囲攻撃の当たり判定を大きくしていく
	CommonData::ENEMYSTATE state_;	//状態変数
	//WAID_ATK waidAtk_;
	ACT act_;			//行動パターン

	float jumpCnt_;		//広範囲攻撃のジャンプカウント

	
	
	SunUtility::DIR_3D moveDir_;	//動く方向

	VECTOR moveRoute_;	//行先の座標
	
	//パラメタの初期化
	void SetParam(void)override;		

	//ノックバック処理
	void KnockBack(void);




};
