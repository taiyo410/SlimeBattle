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
	static constexpr float WAID_CHARGE_MAX = static_cast<float>(SunUtility::DEFAULT_FPS) * 1.3f;
	static constexpr float WAID_JUMPCNT_MAX = static_cast<float>(SunUtility::DEFAULT_FPS) * 0.3f;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//スタミナ回復状態のカウント
	static constexpr int STAMINA_RECOV_TIME = SunUtility::DEFAULT_FPS * 5;

	//突進攻撃が終わった後のクールタイム
	static constexpr float NORMAL_ATK_COOLTIME = SunUtility::DEFAULT_FPS * 2;

	//広範囲攻撃の落下時用の重力
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;
	//溜め時間
	static constexpr float CHARGE_CNT = 5.0f;
	//落ちている時間
	static constexpr int FALL_CNT = SunUtility::DEFAULT_FPS * 2;


	//復活カウント
	static constexpr int REVIVAL_CNT_MAX = SunUtility::DEFAULT_FPS * 2;

	// 敵からプレイヤーへのY軸方向のオフセット値
	static constexpr float ENEMY_TO_PLAYER_Y_OFFSET = 50.0f;

	// 逃走時のX軸方向のマージン
	static constexpr float ESCAPE_MARGIN_X = 210.0f;
	// 逃走時のZ軸方向のマージン
	static constexpr float ESCAPE_MARGIN_Z = 210.0f;

	//攻撃開始時のプレイヤーとのマージン
	static constexpr float CHARGE_MARGIN_X = 180.0f;
	static constexpr float CHARGE_MARGIN_Z = 180.0f;


	// 移動終了後のクールタイム (秒)
	static constexpr float MOVE_END_COOL_TIME_SEC = 0.5f;

	//カメラのシェイクカウント
	static constexpr float SHAKE_CNT = 10;

	//カメラの制限
	static constexpr float SHAKE_LIMIT = 10;

	//描画
	 // スタミナゲージの描画に関する定数
	static constexpr int STAMINA_GAUGE_X = 15;
	static constexpr int STAMINA_GAUGE_Y = 50;
	static constexpr int STAMINA_GAUGE_WIDTH = 260; // 275 - 15
	static constexpr int STAMINA_GAUGE_HEIGHT = 25;  // 75 - 50
	static constexpr int STAMINA_GAUGE_INNER_OFFSET = 1; // 背景との隙間
	static constexpr int STAMINA_GAUGE_BG_COLOR = 0x000000;
	static constexpr int STAMINA_GAUGE_CURRENT_COLOR = 0x9d370e;
	static constexpr int STAMINA_GAUGE_CONSUMPTION_COLOR = 0xED784A;


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
	void ChangeEnemyState(SlimeBase::ENEMYSTATE state)override;

	//広範囲攻撃用の状態変化用
	//void ChangeWaidAtkState(const WAID_ATK waidAtk);

	//スタミナとフレームの減算
	void FrameComsumption(void);

	//スタミナ回復処理
	void StaminaRecovery(void);

	//敵の状態ゲッタ
	SlimeBase::ENEMYSTATE GetState(void);


	//広範囲攻撃状態ヘッダ
	//Enemy::WAID_ATK GetWaidAtkState(void) const;

	//敵状態のセッター
	void SetEnemyState(const SlimeBase::ENEMYSTATE enemyState);
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
	SlimeBase::ENEMYSTATE state_;	//状態変数
	//WAID_ATK waidAtk_;
	ACT act_;			//行動パターン

	float jumpCnt_;		//広範囲攻撃のジャンプカウント

	
	
	SunUtility::DIR_3D moveDir_;	//動く方向

	VECTOR moveRoute_;	//行先の座標
	
	//パラメタの初期化
	void SetParam(VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir)override;

	//ノックバック処理
	void KnockBack(void);




};
