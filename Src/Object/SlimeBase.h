#pragma once
#include<DxLib.h>
#include<map>
#include"./Stage.h"
#include"../Common/Vector2.h"
#include"../Common/CommonData.h"
#include"../Common/Parameta.h"
#include"../Manager/SoundManager.h"
#include"../Manager/ModelManager.h"
#include"../Utility/SunUtility.h"
class SceneGame;
class SoundManager;
class ModelManager;
class ItemBase;
class Player;
class GaugeCircle;
class SlimeBase
{
public:

	//定数
	//--------------------------------------
	//移動上限
	static constexpr float MOVE_LIMIT = Stage::STAGE_ONE_SQUARE * 5.8 - Stage::STAGE_ONE_SQUARE / 2;

	//スライムの色 
	static constexpr int BLUE_SLIME_COLOR = 0x5195E1;
	static constexpr int ORANGE_SLIME_COLOR = 0xED784A;

	//半径
	static constexpr float RADIUS = 25.0f;

	//復活したときの高さ
	static constexpr float REVIVAL_HEIGHT_POS_Y = RADIUS * 5.0f;

	//初期座標
	//左側
	static constexpr VECTOR INIT_LEFT_POS = { -Stage::STAGE_ONE_SQUARE * 3, RADIUS, 0.0f };

	static constexpr VECTOR INIT_RIGHT_POS = { Stage::STAGE_ONE_SQUARE * 3,RADIUS,0.0f };
	//重力
	//重力
	static constexpr float DEFAULT_GRAVITY = 0.25f;

	//最大ジャンプパワー
	static constexpr float MAX_JUMP_POWER =10.0f;

	//移動ジャンプパワー
	static constexpr float STEP_JUMP_POWER = 0.4f;

	//フレーム時間
	static constexpr float FLAME_TIME = 1 / 60;

	//スピード
	static constexpr float SPEED = 15.0f;

	//クリティカルダメージ
	static constexpr int CRITICAL_DAMAGE = 5;

	//通常ダメージ
	static constexpr int NORMAL_DAMAGE = 2;

	//フレーム基準値
	static constexpr float FRAME_DEFAULT = 4.0f;

	//フレーム最大値
	static constexpr float FRAME_MAX = 12.0f;

	//スタミナ最大値
	static constexpr float STAMINA_MAX = 60.0f;

	//スタミナ回復スピード(１フレームに回復する量)
	static constexpr float STAMINA_RECOVE_SPEED = 0.25f;

	//スタミナ回復量最大値
	static constexpr float STAMINA_RECOV_MAX = 1.0f;

	//チャージスピード
	static constexpr float CHARGE_SPEED = 0.2f;

	////吹っ飛ぶフレーム数
	static constexpr int KNOCKBUCK_FRAME = 12;

	//プレイヤーがパリィしたときに吹っ飛ぶフレーム数
	static constexpr int KNOCKBACK_PARRY = 5;

	//ステップのSEの音量
	static constexpr int STEP_VOL = SoundManager::VOLUME_MAX * 50 / 100;

	//無敵時間
	static constexpr int INVINCIBLE_TIME = SunUtility::DEFAULT_FPS * 1;
	
	//敵とプレイヤーの座標マージン
	static constexpr float POS_MARGIN = 5.0f;


	//広範囲攻撃ジャンプパワー
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//広範囲攻撃クールタイム
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//広範囲攻撃チャージ最大値
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 0.5f;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3f;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//広範囲攻撃の落下時用の重力
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;

	//広範囲攻撃当たり判定調整用
	static constexpr float WAID_ATK_COLMARGIN = 1.3f;

	//広範囲攻撃溜めのエフェクトの大きさ
	static constexpr float WAID_CHARGE_EFFECT_SCL = 30;

	//アイテム再取得までの時間
	static constexpr int ITEM_REGET_CNT = 2;

	//落ちた時のダメージの増加量
	static constexpr int FALL_DMG_INCREASE = 10;

	//落ちた時のダメージデフォルト
	static constexpr int FALL_DMG_DEFAULT = 20;

	//落ちた時のスコア減算デフォルト
	static constexpr int FALL_SCORE_DEFAULT = 100;

	//落ちた時のスコア減算増加量
	static constexpr int FALL_SCORE_INCREASE = 50;

	//SEの音量
	static constexpr int SE_VOL = 50;

	//三角形のYの高さ
	static constexpr float HIGH = 12.5f;

	//頂点座標
	static constexpr float VERTEX = 60.0f;

	//描画関係
	//*********************************************************

	//チャージゲージ
	//----------------------------------------------
	//相対座標
	static constexpr VECTOR LOCAL_GAUGE_POS = { 0.0f,0.0f,50.0f };
	//サイズ
	static constexpr int GAUGE_SIZE = 46;
	//----------------------------------------------

	//パリィクールタイムゲージ
	static constexpr VECTOR PARRY_POS_BLUE = { -400.0f,50.0f,40.0f };
	static constexpr VECTOR PARRY_POS_ORANGE = { 400.0f,50.0f,40.0f };

	//シールドエフェクト
	static constexpr float SHIELD_SCALE = 10.0f;

	//スライムモデルの点滅カウント
	static constexpr int BLINK_INTERVAL = 3;
	static constexpr int BLINK_PATTERN = 2;

	//青スライムの状態画像
	const std::string BLUE_NORMAL_FACE = "NormalK.png";
	const std::string BLUE_TIRED_FACE = "Tukare.png";
	const std::string BLUE_DAMAGE_FACE = "DamageK.png";
	const std::string BLUE_CHARGE_FACE = "ChargeK.png";
	const std::string BLUE_ATTACK_FACE = "AttackK.png";

	//オレンジスライム状態画像
	const std::string ORANGE_NORMAL_FACE = "NormalY.png";
	const std::string ORANGE_TIRED_FACE = "TukareY.png";
	const std::string ORANGE_DAMAGE_FACE = "DamageY.png";
	const std::string ORANGE_CHARGE_FACE = "ChargeY.png";
	const std::string ORANGE_ATTACK_FACE = "AttackY.png";

	//スライム背景の雲画像
	const std::string CLOWD_IMG = "Clowd.png";
	static constexpr double CLOWD_SCL = 1.5;

	//青スライム状態画像の座標
	static constexpr int BLUE_SLIME_FACE_POS_X = 130;
	static constexpr int BLUE_SLIME_FACE_POS_Y = 144;

	//オレンジスライム状態画像
	static constexpr int ORANGE_SLIME_FACE_POS_X = 1070;
	static constexpr int ORANGE_SLIME_FACE_POS_Y = 144;



	//列挙型
	enum class SLIME_FACE
	{
		NORMAL
		, DAMAGE
		, TIRED
		, CHARGE
		, ATTACK
		, MAX
	};


	enum class PLAYERSTATE
	{
		COOL
		, DEBUFF
		, ACTIONABLE
		, STEPKEEP
		, STEP
		, CHARGE
		, NORMALATTACK
		, CRITICALATTACK
		, KNOCKBACK
		, GUARD
		, WAIDATTACK
		, FALL
		, REVIVAL

	};

	//列挙型
	enum class ENEMYSTATE
	{
		NONE
		, THINK
		, DEBUFF
		, MOVE
		, STEP
		, CHARGE
		, KNOCKBACK
		, KNOCKBACkSMALL
		, NORMALATTACK
		, WAIDATTACK
		, CRITICALATTACK
		, FALL
		, REVIVAL
	};




	//広範囲攻撃
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};
	enum class P_OR_E
	{
		PLAYER
		,ENEMY
	};
	
	//デフォルトコンストラクタ
	SlimeBase(void);

	//デストラクタ
	~SlimeBase(void);

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	virtual bool Init(SceneGame* _sceneGame,VECTOR _initPos,int _padNum,int _enemyNum,ModelManager::MODEL_TYPE _modelType,SunUtility::DIR_3D _dir);

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
	/// <returns></returns>
	virtual bool Release(void);

	
	//ゲッタ
	//********************************************************
	// 敵とプレイヤーの座標ゲッタ
	VECTOR GetPos(void);


	// プレイヤーの方向ゲッター
	SunUtility::DIR_3D GetDir(void);

	//ノックバックカウントのセッタ
	void SetKnockBack(const int knockBackCnt);

	/// <summary>
	/// ダメージ判定
	/// </summary>
	/// <param name="dmg">ダメージ</param>
	/// <param name="invincibleCnt">無敵時間</param>
	void Damage(const int dmg, const int invincibleCnt);

	//表示用スコアゲッタ
	int GetScore(void);

	//無敵時間セッタ
	void SetInvincible(const int invincibleCnt);
	//無敵時間ゲッター
	int GetInvincibleCnt(void);

	//クールタイムのセッタ
	void SetCoolTime(const int coolTime);

	//座標セッタ
	void SetPos(const VECTOR pos);

	//HPゲッタ
	float GetHpPercent(void);

	//弱体状態のゲッタ
	bool GetIsWeak(void);

	//重力のセッタ(広範囲攻撃用)
	void SetGravityPow(const float gravityPow);

	//弱体状態のセッタ
	void SetIsWeak(bool isWeak);


	/// <summary>
	/// 重力をかける
	/// </summary>
	void AddGravity(float gravityPow);

	//アイテムのポインタのセット
	void SetItem(ItemBase* item);

	//アイテム使用状態セッタ
	void SetIsUse(const bool isUseItem);

	//アイテム再取得カウントゲッタ
	int GetItemReGetCnt(void);

	//広範囲攻撃チャージカウントゲッタ
	int GetChargeCnt(void);

	//広範囲攻撃チャージカウントセッタ
	void SetChargeCnt(int cnt);

	WAID_ATK GetWaidAtkState(void);

	//プレイヤーがアイテムのポインターを持っているか
	bool IsGetItemPtr(void);	

	//プレイヤーのアイテムが爆発しているかどうかのゲッタ
	bool IsItemAtk(void);

	//攻撃状態重み付けゲッタ
	int GetAtkPow(void);

	//スコア加算処理
	void AddScore(const int score);

	//プレイヤーの状態ゲッタ
	PLAYERSTATE GetPlayerState(void) { return pState_; }

	//------------------------------------------------
	//エフェクトを再生セッタ
	void SetIsItemGetEffect(const bool isItemGetEff);

	// ジャンプ力の設定
	void SetJumpPower(float power);

	void SetGuardCoolTime(const int guardCooltime);

	//プレイヤーの状態変更(ゲームシーンで継承スライム配列で変更できるように)
	virtual void ChangePlayerState(PLAYERSTATE _pState);

	//CPUの状態変更
	virtual void ChangeEnemyState(ENEMYSTATE _state);

protected:
	//ポインタ
	//SlimeManager& slimeMng_;
	SceneGame* sceneGame_;
	ItemBase* item_;
	GaugeCircle* gaugeCircle_;
	SoundManager* sound_;
	ModelManager* model_;
	ModelManager::MODEL_TYPE modelType_;


	VECTOR pos_;			//座標

	VECTOR rot_;			//角度

	VECTOR scale_;			//大きさ設定

	VECTOR revivalPos_;		//復活する座標
	//モデルファイル名
	std::string modelFileName_;

	int modelHandle_;	//モデルハンドル

	//スライムの状態画像
	std::map<SLIME_FACE, int>slimeFaceImgs_;	//画像格納
	SLIME_FACE face_;	//スライム状態
	Vector2 facePos_;	//状態画像の座標

	//状態画像の背景
	int backSlimefaceImg_;	//画像
	Vector2 backSlimefacePos_;	//座標

	//チャージSE
	int hp_;			//体力
	int score_;			//スコア
	float chargePer_;	//割合
	float jumpPower_;	//ジャンプ力
	bool isJump_;	//ジャンプ中判定
	float gravityPow_;	//重力変数
	int atkPow_;	//状態ごとの重ねつけ
	SunUtility::DIR_3D dir_;//プレイヤーの方向

	int textureFrame_;	 //フレーム枠画像

	bool isWeak_;	//弱体状態フラグ

	bool isItemUse_;	//アイテム使用フラグ

	float hpPercent_;	//Hpの割合

	float stamina_;		//プレイヤーのスタミナ

	int coolTime_;		//クールタイム

	//落ちる関係
	int fallCnt_;		//落ちている時間のカウント
	int fallDmg_;		//落ちた時のダメージ
	int fallScore_;		//落ちたときのスコア減算
	int revivalCnt_;	//復活中カウント


	SunUtility::DIR_3D knockBackDir_;//ノックバック方向


	//スタミナ減少中判定
	bool isStaminaRecov_;

	//スタミナ回復量
	float staminaRecov_;

	//無敵時間
	int invincibleCnt_;

	//広範囲攻撃
	int waidChargeCnt_;	//広範囲攻撃の溜めカウント
	WAID_ATK waidAtk_;	//広範囲攻撃状態
	int waidAtkCoolTime_;	//広範囲攻撃のクールタイム
	float jumpCnt_;		//広範囲攻撃のジャンプカウント

	//フレームカウント
	//----------------------------------------
	float frame_;
	int knockBackCnt_;	//ノックバックカウント
	float frameNum_;	//溜めが終わった後のフレーム保管用
	bool isUseItem_;	//アイテム使用状態

	//プレイヤー関連
	int enemyNum_;		//各スライムにとって敵であるスライムの番号



	SlimeBase::PLAYERSTATE pState_;		//プレイヤーの状態
	int guardCoolTime_;					//ガードクールタイム

	//初期化処理
	virtual void SetParam(VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir);

	/// <summary>
	/// ジャンプ操作
	/// </summary>
	void ProcessJump(void);

	

	//状態ごとの更新
	virtual void StateUpdate(void);

	//広範囲攻撃用の状態変化用
	virtual void ChangeWaidAtkState(const WAID_ATK waidAtk);

	//ジャンプ
	void Jump(void);

	/// <summary>
	/// クリティカルしたときの関数
	/// </summary>
	//void CriticalAttack(void);

	/// <summary>
	/// 通常ダメージ
	/// </summary>
	/// <param name=""></param>
	//void NormalAttack(void);

	/// <summary>
	/// 方向ごとの処理
	/// </summary>
	/// <param name=""></param>
	void DirUpdate(SunUtility::DIR_3D dir);


	//フレーム上限
	void FrameLimit(void);

	//広範囲攻撃パラメタ
	Parameta waidAtkPar_;

	//広範囲攻撃チャージ用エフェクト
	Parameta waidChargePar_;

	//移動制限　
	bool MoveLimit(void);

	//無敵時間減算処理
	void InvincibleConsum(void);

	//無敵時間ゲッタ
	int GetInvincible(void);

	//地面
	void Ground(void);
	//ステージ上にいるかどうか
	bool isInStage_;

	//方向を表す三角形描画
	void DrawDirTriangle(VECTOR _pos,SunUtility::DIR_3D _dir,int _color);

	//共通の状態処理
	//アイテム再取得までのカウント
	int itemReGetCnt_;
	
	Parameta itemGetPar_;	//アイテムゲットしたとき
	bool itemGetEffPlay_;
private:
};