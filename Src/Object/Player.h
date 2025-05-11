#pragma once
#include<DxLib.h>
#include"../Utility/SunUtility.h"
#include"../Common/CommonData.h"
#include"./SlimeBase.h"
class SceneGame;
class Player2;

class Player:public SlimeBase
{
public:
	//値の上下を繰り返す
	enum class UP_AND_DOWN
	{
		UP
		, DOWN
	};

	//定数
	//***********************************************
	//初期座標
	static constexpr VECTOR INIT_POS = { -Stage::STAGE_ONE_SQUARE * 3, RADIUS, 0.0f };
	//スライムの色 
	static constexpr int SLIME_COLOR = 0x5195E1;

	//クールタイム
	static constexpr int COOL_TIME = 30;

	//プレイヤーの状態番号
	static constexpr int STATE_ATTACK = 6;

	//ステップ受付時間
	static constexpr int STEP_FRAME_MAX = 10;

	//HP最大値
	static constexpr int MAX_HP = 200;


	//----------------------------------------------
	//ガード関連
	//-----------------------------------------------
	//ガードカウントマックス
	static constexpr int GUARD_CNT_MAX = SunUtility::DEFAULT_FPS * 0.5;

	//ガードクールタイム
	static constexpr int GUARD_COOLTIME = SunUtility::DEFAULT_FPS * 5;

	//ガードクールタイムゲージデフォルトサイズ
	static constexpr int GUARD_GAUGE_SIZE_DEFAULT = 60;

	//ガードクールタイムゲージの最大、最小サイズとデフォルトサイズの差
	static constexpr int GUARD_GAUGE_SIZE_MARGIN = 10;

	//ガード成功時のクールタイム
	static constexpr int GUARD_COOLTIME_SUCCESS = SunUtility::DEFAULT_FPS * 2.5;
	//---------------------------------------------------

	//溜め攻撃状態のときの消費量の倍率
	static constexpr int CHARGE_ATK_STAMINA = 2;

	//溜めてる間の1フレームに消費するスタミナ（消費量用）
	static constexpr float CHARGE_STAMINA_PER_FRAME = CHARGE_SPEED * CHARGE_ATK_STAMINA;

	//パリィの重み付け
	static constexpr int PARRY_ATK_POW = 5;

	//溜め攻撃の重み付け
	static constexpr int CHARGE_ATK_POW = 2;

	//ステップで消費するスタミナ
	static constexpr float STEP_STEMINA = FRAME_DEFAULT;

	//チャージで消費するスタミナ(固定値)
	static constexpr float CHARGE_STAMINA_VAL = FRAME_DEFAULT * CHARGE_ATK_STAMINA;

	//ノックバック後のクールタイム
	static constexpr int KNOCKBACK_AFTER_CNT = SunUtility::DEFAULT_FPS * 1;

	//クリティカルカウント最大
	static constexpr int CRITICAL_CNT_MAX = 1;

	//落ちている時間
	static constexpr int FALL_CNT = SunUtility::DEFAULT_FPS * 2;

	//復活カウント
	static constexpr int REVIVAL_CNT_MAX = SunUtility::DEFAULT_FPS * 2;

	//復活後(復活して、地上に降りた後の無敵時間)
	static constexpr int AFTER_REVIVAL_CNT = SunUtility::DEFAULT_FPS * 3;

	//疲れた表情をするスタミナ残量率の基準
	static constexpr float STAMINA_TIRED = 0.4f;

	//描画関係
	//*********************************************************
	//スライム状態画像の座標
	static constexpr int FACE_POS_X = 130;
	static constexpr int FACE_POS_Y = 144;
	
	//チャージゲージ
	//----------------------------------------------
	//相対座標
	static constexpr VECTOR LOCAL_GAUGE_POS = { 0.0f,0.0f,50.0f };
	//サイズ
	static constexpr int GAUGE_SIZE = 46;
	//----------------------------------------------
	
	//パリィクールタイムゲージ
	static constexpr VECTOR PARRY_POS = { -400.0f,50.0f,40.0f };

	//シールドエフェクト
	static constexpr float SHIELD_SCALE = 10.0f;



	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	//bool Init(SceneGame* parent) override;		

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void) override;	

	//描画処理
	virtual void Draw(void)override;

	/// <summary>
	/// 解放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void) override;		

	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name=""></param>
	virtual void ProcessMove(void);

	/// <summary>
	/// 状態変化関数
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	void ChangeState(SlimeBase::PLAYERSTATE state)override;

	/// <summary>
	/// チャージ開始
	/// </summary>
	/// <param name=""></param>
	virtual void ChargeStart(void);




	//プレイヤー座標のゲッター
	const VECTOR GetPos(void)const;

	//プレイヤーの状態ゲッタ
	SlimeBase::PLAYERSTATE GetState(void);

	/// <summary>
	/// プレイヤー状態のセッター
	/// </summary>
	/// <param name="playerState"></param>
	void SetPlayerState(const SlimeBase::PLAYERSTATE playerState);

	//ガードクールタイムのセッタ
	void SetGuardCoolTime(const int guardCooltime);

	//座標セッタ
	void SetPos(const VECTOR pos) { pos_ = pos; }

	//プレイヤーと敵が何もしていないときに当たっているときに、当たらないようにする
	void SetMarginPos(SunUtility::DIR_3D marginDir);
	
	//アイテムとった時の広範囲攻撃状態遷移
	void ChangeWaidAtkState(const WAID_ATK waidAtk)override;
	
	


protected:

/// <summary>
/// 座標の初期化
/// </summary>
	void SetParam(VECTOR _initPos,int _padNum,int _enemyNum) override;

	//ステップフレームカウント
	int stepFrame_;

	//ステップ中入力かの判定
	bool isStep_;

	//ガードカウント
	int guardCnt_;

	//ガードクールタイム
	int guardCoolTime_;

	//ガードクールタイム割合
	float guardCoolTimePercent_;	

	//ガードクールタイムゲージのサイズ
	int guardCoolTimeGaugeSize_;

	//スタミナ消費量
	float staminaConsum_;

	//消費量割合
	float staminaConsumPercent_;

	//スタミナ割合
	float staminaPercent_;

	//クリティカルカウント
	int criticalCnt_;


	//何もしてないときの座標を決める用のDir
	SunUtility::DIR_3D dirMargin_;

	int padNum_;		//ゲームパッドの番号

	VECTOR shieldPos_;	//ガードエフェクト座標
	VECTOR shieldRot_;	//ガードエフェクト角度
	VECTOR shieldScl_;	//ガードエフェクト大きさ

	Parameta shieldPar_;	//シールドエフェクトパラメタ
	
	/// <summary>
	/// デバッグ用関数
	/// </summary>
	/// <param name=""></param>
	virtual void DrawDebug(void);

	/// <summary>
	/// フレーム更新処理
	/// </summary>
	/// <param name=""></param>
	void FrameUpdate(void);


	/// <summary>
	/// スタミナ回復処理
	/// </summary>
	void StaminaRecovery(void);

	/// <summary>
	/// チャージかステップを決める処理
	/// </summary>
	/// <param name=""></param>
	void MoveDecide(void);
	/// <summary>
	/// ノックバックされる側の処理
	/// </summary>
	/// <param name="attackDir"></param>
	virtual void KnockBack(void);

	/// <summary>
	/// スタミナの下限
	/// </summary>
	/// <param name="staminaConsumPerFrame">1フレームのスタミナ減少量</param>
	void StaminaLowLimit(float staminaConsumPerFrame);

	//状態ごとの更新
	void StateUpdate(void)override;


#pragma region 列挙型の更新処理
	//クールタイム時の処理
	void CoolUpdate(void);

	//ステップ受付状態
	void ActionableUpdate(void);

	/// ステップ入力の猶予
	void StepKeepUpdate(void);

	/// <summary>
	/// ノックバック処理
	/// </summary>
	/// <param name=""></param>
	void KnockBuckUpdate(void);

	//ガード処理
	void GuardUpdate(void);

	//アイテム（広範囲攻撃）
	void WaidAtkUpdate(void);

	//ステップ処理
	void StepUpdate(void);

	//溜め状態
	void ChargeUpdate(void);

	//攻撃
	void NormalAttackUpdate(void);

	//クリティカル
	void CriticalUpdate(void);

	//ガードクールタイム
	void GuardCoolTimeConsum(void);

	//アイテムの毎フレーム処理
	void ItemUpdate(void);

	//アイテム入手してからの更新
	void GetItemUpdate(void);

	/// <summary>
	/// 値の振れ幅を決めて上下させる
	/// </summary>
	/// <param name="cnt">上下させるカウント</param>
	/// <param name="moveNum">上下させたい値</param>
	/// <param name="defaultNum">中央値</param>
	/// <param name="rangeNum">振れ幅</param>
	/// <param name="speedNum">上下させるスピード</param>
	void ShakeNum(int moveNum, int defaultNum, int rangeNum, int speedNum);

	UP_AND_DOWN updown_;


	//落ちている状態
	void FallUpdate(void);

	//復活処理
	void RevivalUpdate(void);


	SlimeBase::PLAYERSTATE state_;		//プレイヤーの状態
	SlimeBase::PLAYERSTATE colState_;	//プレイヤーが当たった時の保管用変数

#pragma endregion

private:
	////ポインタ格納領域
	Player2* player2_;
};

