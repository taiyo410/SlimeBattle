#pragma once
#include<vector>
#include"../Utility/SunUtility.h"
#include"../Manager/SoundManager.h"
#include"../Common/Vector2.h"
#include"./SceneBase.h"
#include"../Common/CommonData.h"
#include"../Common/Parameta.h"
#include"../Object/SlimeBase.h"
class SlimeBase;
class CommonData;
class RuleBase;
class Stage;
class ItemBase;
class Player;
class Player2;
class Enemy;
class SceneManager;
class SlimeManager;
class Grid;
class SceneGame :public SceneBase
{
public:
	//定数
	//------------------------
	// スライムのプレイヤー番号
	static constexpr int PLAYER = 0;
	// 敵番号
	static constexpr int ENEMY = 1;

	//２P番号
	static constexpr int PLAYER2 = 1;

	//スライムの数
	static constexpr int SLIME_NUM_MAX = 2;

	//アイテム出現カウント
	static constexpr int ITEM_SPORN_CNT = SunUtility::DEFAULT_FPS * 10;

	//アイテム個数の最大
	static constexpr int ITEM_CNT_MAX = 2;


	//ノックバックフレーム関係
	//-----------------------------------------------
	//相殺ダメージ
	static constexpr int OFFSET_DMG = 10;
	//相殺で吹っ飛んだ時のノックバックフレーム
	static constexpr int OFFSET_KNOCKBACK_FRAME = 5;
	//弱体状態じゃないとき敵がチャージしていた時のプレイヤーのノックバック
	static constexpr int PLAYER_KNOCKBACK_FRAME = 5;
	//プレイヤーがクリティカル出した時のノックバック
	static constexpr int ENEMY_CRITICALED_KNOCKBACK = SlimeBase::KNOCKBUCK_FRAME + 5;

	//ヒットエフェクトの大きさ
	static constexpr float HIT_EFFECT_SCL = 10.0f;

	//BGMを変えるHP割合の基準
	static constexpr float CHANGE_BGM_PER = 0.5f;

	//広範囲攻撃のダメージ割合
	static constexpr float WAID_ATK_DMG_SCALE = 1.5f;

	//ダメージ関連
	//----------------------------------------
	//敵がチャージしてる時のダメージ
	static constexpr int CHARGE_ENEMY_DMG = 5;
	//弱ってる時のダメージ
	static constexpr int WEAK_ENEMY_DMG = 5;

	//スコア
	//----------------------------------
	//倍率
	static constexpr float WAID_ATK_ADD_SCORE_SCALE = 5;
	//プレイヤーに追加するスコア
	static constexpr int PLAYER_ADD_SCORE = 50;

	//プレイヤーがクリティカル出した時のスコア
	static constexpr int PLAYER_ADD_SCORE_CRITICAL = 1000;
	
	//プレイヤーがクリティカル出した時の敵のダメージ
	static constexpr int PLAYER_CRITICAL_DMG = 50;

	//ガード成功したときのスコア
	static constexpr int GUARD_SCORE = 100;

	//攻撃成功したときのスコア
	static constexpr int PLAYER_ATK_SCORE = 300;

	//敵の攻撃スコア
	static constexpr int ENEMY_ATK_SCORE = 400;

	//ダメージ受けた後の何もできない時間
	static constexpr int ENEMY_COOL_TIME = SunUtility::DEFAULT_FPS * 3;
	static constexpr int ENEMY_KNOCKBACK_TIME = SunUtility::DEFAULT_FPS * 3;

	//列挙型
	enum class BGM_TYPE
	{
		BGM
		,BGM2
	};

	enum class BG_CLOWD
	{
		ROBOKASS
		,RIHUJIN
		,MAX
	};

	

#pragma region ステージ関係
	
#pragma endregion

	

	//デフォルトコンストラクタ
	SceneGame(void);

	//デストラクタ
	~SceneGame(void);
	//列挙型
	//-------------------------------
	//敵味方種別
	enum class TYPE
	{
		PLAYER
		, ENEMY
	};

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Init(void)override;		

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name=""></param>
	void Update(void)override;		

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	void Draw(void)override;		

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool Release(void)override;		
	
	/// <summary>
	/// タイプを設定する
	/// </summary>
	/// <param name=""></param>
	void SetType(void);

	//ルールを設定する
	void SetRule(void);

	//ルールによって処理を変える
	void DoChangeRule(void);

	bool GetIsHitItem(void);
	


	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="centerPos1">オブ1の中心座標</param>
	/// <param name="size1">オブ1のサイズ</param>
	/// <param name="centerPos2">オブ2の中心座標</param>
	/// <param name="size2">オブ2のサイズ</param>
	/// <returns></returns>
	//球体と球体の当たり判定
	bool IsHitSpheres(const VECTOR& pos1, float radius1, const VECTOR& pos2, float radius2);

	//アイテムの取得
	bool IsHitItem(void);


	//アイテム出現
	void ProcessItem(void);

	//攻撃力を比べる
	void PlAtkPowCompare(int pl1Atknum, int pl2Atknum);


#pragma region ゲッター
#pragma region プレイヤー１
	/// <summary>
	/// プレイヤー方向
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SunUtility::DIR_3D GetPlayerDir(void);

	/// <summary>
	/// プレイヤー座標をゲームシーンからゲットするとき
	/// </summary>
	/// <param name="_num">プレイヤー番号</param>
	/// <returns></returns>
	VECTOR GetPlayerPos(int _num);

	/// <summary>
	/// プレイヤーの状態ゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SlimeBase::PLAYERSTATE GetPlayerState(void);

	//プレイヤーのHPゲッタ
	float GetPlayerHpPercent(int _num);

	//プレイヤーのスコアゲッタ
	int GetPlayerScore(void);

	//無敵時間
	int GetPlayerInvincible(void);

	bool isHitItem_;	//アイテムに当たったかどうか

#pragma endregion
#pragma region プレイヤー２
	/// <summary>
	/// プレイヤー方向
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SunUtility::DIR_3D GetPlayer2Dir(void);


	/// <summary>
	/// プレイヤー座標をゲームシーンからゲットするとき
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetPlayer2Pos(void);

	//プレイヤー2のHPゲッタ
	float GetPlayer2HpPercent(void);

	//プレイヤー2のスコアゲッタ
	int GetPlayer2Score(void);

	//無敵時間
	int GetPlayer2Invincible(void);

	Parameta hitEffectPar_;	//エフェクトのパラメタ

#pragma endregion


#pragma region 敵
	/// <summary>
	/// 敵座標をゲームシーンからゲットするとき
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	VECTOR GetEnemyPos(void);

	// 敵方向
	SunUtility::DIR_3D GetEnemyDir(void);

	//当たっているかどうかのゲッター
	bool GetIsCollision(void);


	// 敵の状態ゲッタ
	SlimeBase::ENEMYSTATE GetEnemyState(void);

	//敵のHPゲッタ
	float GetEnemyHpPercent(void);

	//敵のスコアゲッタ
	int GetEnemyScore(void);

	//敵の無敵時間
	int GetEnemyInvincible(void);

	int itemCnt_;		//アイテムの個数

	ItemBase* GetValidItem(void);
#pragma endregion

	
	

#pragma endregion







private:
	//ポインター宣言
	RuleBase* ruleBase_;
	SlimeBase* slime_[SLIME_NUM_MAX];
	SlimeBase* slimes_;
	//SlimeManager& slimeMng_;
	Stage* stage_;
	Player* player_;
	Enemy* enemy_;
	std::vector<ItemBase*> items_;
	Grid* grid_;
	SoundManager* sound_;
	//メンバー変数
	//-------------------------
	//背景
	int bgImage_;		//背景画像格納

	int roboKass_;		//ロボカス画像

	int cloudImage_;		//雲画像
	Vector2 cloudPos_;	//雲画像用

	BG_CLOWD bgClowd_;	//雲に乗ったやつの画像の種類

	Vector2 bgClowdPos_;	//座標

	//エフェクト
	int hitEffectId_;	//ヒットエフェクトのId

	int itemSpornCnt_;		//アイテム出現カウント

	int hitSE_;			//当たった時のSE

	int gamebgm_;		//BGM格納
	int gamebgm2_;		//どちらかの体力が半分以下になった時

	//プレイヤー勝ち番号
	int slimeWinNum_;

	//負け番号
	int slimeLoseNum_;	



	VECTOR hitEffectPos_;	//ヒットエフェクトの座標
	VECTOR hitEffectscl_;	//ヒットエフェクトの大きさ
	VECTOR hitEffectRot_;	//ヒットエフェクトの角度
	//敵味方種別
	CommonData::TYPE type_[SLIME_NUM_MAX];

	//ルール
	CommonData::RULE rule_;

	//BGM切り替え用
	BGM_TYPE bgm_;

	//BGM切り替えフラグ
	bool bgmFlg_;
	

	//当たっているか
	bool isCollision_;
	/// <summary>
	/// デバッグ用関数
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);

	/// <summary>
	/// PVE用のノックバック判定
	/// </summary>
	/// <param name="playerDir">プレイヤーの方向</param>
	/// <param name="playerState">プレイヤーの状態</param>
	/// <param name="enemyDir">敵の方向</param>
	/// <param name="enemyState">敵の状態</param>
	void PVEKnockBack(SunUtility::DIR_3D playerDir, SlimeBase::PLAYERSTATE playerState
		, SunUtility::DIR_3D enemyDir, SlimeBase::ENEMYSTATE enemyState);

	/// <summary>
	/// PVP用のノックバック
	/// </summary>
	/// <param name="plLoseNum">比べるプレイヤー番号</param>
	void PVPKnockBack(int knockBackNum);

	//お互いに吹っ飛ぶ用のノックバック
	void KnockBackMutual(void);

	//BGM切り替え
	void ChangeBgm(BGM_TYPE bgm);
};
