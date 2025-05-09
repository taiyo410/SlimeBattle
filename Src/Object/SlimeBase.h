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
	//アニメーションの終わり
	static constexpr float ANIM_END = 59.0f;

	//移動上限
	static constexpr float MOVE_LIMIT = Stage::STAGE_ONE_SQUARE * 5.8 - Stage::STAGE_ONE_SQUARE / 2;
	enum class SLIME_FACE
	{
		NORMAL
		, DAMAGE
		, TIRED
		, CHARGE
		, ATTACK
	};
	//定数
	//--------------------------------------
	
	// 
	//半径
	static constexpr float RADIUS = 25.0f;
	//重力
	static constexpr float DEFAULT_GRAVITY = 0.25f;

	//最大ジャンプパワー
	static constexpr float MAX_JUMP_POWER =10.0f;

	//移動ジャンプパワー
	static constexpr float STEP_JUMP_POWER = 0.4;

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

	//アニメーション最大時間
	static constexpr float ANIM_CNT_MAX = 60;

	//アニメーションデフォルトの速度
	static constexpr float ANIM_SPEED_DEFAULT = SunUtility::DEFAULT_FPS;



	//広範囲攻撃ジャンプパワー
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//広範囲攻撃クールタイム
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//広範囲攻撃チャージ最大値
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 0.5;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3;
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

	//列挙型
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

	//列挙型
	enum class ANIM
	{
		IDLE
		,STEP
		,CHARGE
		,ATTACK
		,MAX
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
	virtual bool Init(SceneGame* _sceneGame);

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

	//プレイヤーの座標の座標ゲッター

	/// <summary>
	/// 敵とプレイヤーの座標ゲッタ
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetPos(void);

	/// <summary>
	/// プレイヤーの方向ゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns>プレイヤーの方向</returns>
	SunUtility::DIR_3D GetDir(void);

	//ノックバックカウントのセッタ
	void SetKnockBack(const int knockBackCnt);

	/// <summary>
	/// ダメージ判定
	/// </summary>
	/// <param name="dmg">ダメージ</param>
	/// <param name="invincibleCnt">無敵時間</param>
	void Damage(const int dmg, const int invincibleCnt);

	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump(void);

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

	//スライム番号の取得
	int GetSlimeNum(void);

	//重力のセッタ(広範囲攻撃用)
	void SetGravityPow(const float gravityPow);

	//弱体状態のセッタ
	void SetIsWeak(bool isWeak);

	/// <summary>
	/// ジャンプ力の設定
	/// </summary>
	/// <param name="power"></param>
	void SetJumpPower(float power);

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

	bool GetIsUse(void);

	//広範囲攻撃の半径ゲッタ
	float GetWaidCol(void);

	//プレイヤーがアイテムのポインターを持っているか
	bool IsGetItemPtr(void);	

	//プレイヤーのアイテムが爆発しているかどうかのゲッタ
	bool IsItemAtk(void);

	//攻撃状態重み付けゲッタ
	int GetAtkPow(void);

	/// <summary>
	/// 状態変化関数
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual void ChangeState(PLAYERSTATE state);

	//スコア加算処理
	void Score(const int score);

	//エフェクトを再生セッタ
	void SetIsItemGetEffect(const bool isItemGetEff);

	ModelManager::MODEL_TYPE GetModelType(void);




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
	std::map<SLIME_FACE, int>slimeFaceImg_;
	SLIME_FACE face_;	//スライム状態
	Vector2 facePos_;	//状態画像の座標

	//状態画像の背景
	int backSlimefaceImg_;	//画像
	Vector2 backSlimefacePos_;	//座標

	//アニメーションのアタッチ番号
	int animAttachNo_;

	//アニメ番号
	int animNo_;

	//アニメ遷移用
	ANIM anim_;

	//アニメーションの総再生時間
	float animTotalTime_;

	//再生中のアニメーション時間
	float stepAnim_;

	//アニメーション速度
	float speedAnim_;

	//アニメ終わった判定
	bool endAnim_;


	//ステップSEの格納
	int stepSE_;

	//攻撃SE
	int attackSE_;

	//チャージSE
	int chargeSE_;
	//広範囲攻撃のパラメタ



	//溜め割合
	float chargePer_;
	float gaugeRate_;	//デバッグ用のゲージ変化

	int atkPow_;	//状態ごとの重ねつけ

	int textureFrame_;	 //フレーム枠画像

	//ジャンプ力
	float jumpPower_;

	float gravityPow_;	//重力変数

	//ジャンプ中判定
	bool isJump_;

	bool isWeak_;	//弱体状態フラグ

	bool isItemUse_;	//アイテム使用フラグ

	//体力
	int hp_;

	//スコア
	int score_;
	//Hpの割合
	float hpPercent_;	

	//プレイヤーのスタミナ
	float stamina_;

	//クールタイム
	int coolTime_;

	//落ちている時間のカウント
	int fallCnt_;

	//落ちた時のダメージ
	int fallDmg_;

	//落ちたときのスコア減算
	int fallScore_;

	//復活中カウント
	int revivalCnt_;

	P_OR_E judge_;		//プレイヤーかエネミーか


	//プレイヤーの方向
	SunUtility::DIR_3D dir_;

	//ノックバック方向
	SunUtility::DIR_3D knockBackDir_;


	

	//スタミナ減少中判定
	bool isStaminaRecov_;

	//スタミナ回復量
	float staminaRecov_;

	//無敵時間
	int invincibleCnt_;


	int waidChargeCnt_;	//広範囲攻撃の溜めカウント
	

	WAID_ATK waidAtk_;
	//広範囲攻撃
	


	int waidAtkCoolTime_;	//広範囲攻撃のクールタイム
	int slimeNum_;		//スライム番号
	
	float jumpCnt_;		//広範囲攻撃のジャンプカウント




	//フレームカウント
	//----------------------------------------
	//フレーム
	float frame_;

	//ノックバックカウント
	int knockBackCnt_;	

	//溜めが終わった後のフレーム保管用
	float frameNum_;

	bool isUseItem_;	//アイテム使用状態

	//初期化処理
	virtual void SetParam(void);

	/// <summary>
	/// ジャンプ操作
	/// </summary>
	void ProcessJump(void);

	

	//状態ごとの更新
	virtual void StateUpdate(void);

	//広範囲攻撃用の状態変化用
	virtual void ChangeWaidAtkState(const WAID_ATK waidAtk);

	


	

	/// <summary>
	/// クリティカルしたときの関数
	/// </summary>
	void CriticalAttack(void);

	/// <summary>
	/// 通常ダメージ
	/// </summary>
	/// <param name=""></param>
	void NormalAttack(void);

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

	//アニメーション処理
	void Animation(void);
	
	//アニメーションが終わった時の処理
	void EndAnimation(void);
	
	//方向を表す三角形描画
	void DrawDirTriangle(VECTOR _pos,SunUtility::DIR_3D _dir,int _color);

	//共通の状態処理
	//アイテム再取得までのカウント
	int itemReGetCnt_;
	
	Parameta itemGetPar_;	//アイテムゲットしたとき
	bool itemGetEffPlay_;

	

private:
	


};