#pragma once
class SceneTitle;
class ModelManager;
class CommonData
{
public:
	//定数
	static constexpr int TYPE_MAX = 2;


	//列挙型
		//敵味方種別
	enum class TYPE
	{
		PLAYER1
		,PLAYER2
		,ENEMY
		,MAX
	};

	//セレクト種類
	enum class SELECT
	{
		MODE
		,RULE
	};

	//モード種別
	enum class MODE
	{
		PVE
		,PVP
		,MAX
	};
	//ルール種別
	enum class RULE
	{
		HP
		, SCORE
	};

	//勝利パターン
	enum class WINPATTERN
	{
		P1WIN
		,P2WIN
		,DRAW
	};

	//初期化処理
	bool DataInit(void);

	//モード遷移
	void ModeUpdate(void);

	//勝ちパターンセッタ
	void SetWinPattern(WINPATTERN win);

	//勝ちパターンゲッタ
	WINPATTERN GetWinPattern(void);
	//インスタンスの解放
	void ReleaseData(void);

	//シングルトン化
	//------------------------------
	static void CreateData(void);

	//外部でインスタンスを利用可能にするために
	//インスタンスで返す関数を用意
	static CommonData& GetData(void);

	//インスタンスの削除
	void Destroy(void);

	//敵味方種別のゲッタ
	MODE GetMode(void);

	//ルールセッタ
	RULE GetRule(void);

	//モードのセッター
	void SetMode(MODE value);

	//ルールのセッタ
	void SetRule(RULE value);
#pragma region スコア関係

	//プレイヤーのスコアセッタ
	void SetPlayerScore(const int playerScore);

	//敵のスコアセッタ
	void SetEnemyScore(const int enemyScore);

	//プレイヤー
	int GetPlayerScore(void);

	//敵
	int GetEnemyScore(void);
#pragma endregion


#pragma region HPルール関係

#pragma endregion

private:
	//メンバー変数
	TYPE type_[TYPE_MAX];

	RULE rule_;

	MODE mode_;

	WINPATTERN win_;

	int playerScore_;	//プレイヤーのスコア

	int enemyScore_;	//敵のスコア



	//ポインター宣言
	SceneTitle* sceneTitle_;
	ModelManager* model_;

	//シングルトン化
	//デフォルトコンストラクタ
	CommonData(void);
	//デストラクタ
	~CommonData(void);


	//コピーコンストラクタを利用不可にする
	CommonData(const CommonData& ins);

	//静的なインスタンス初期化
	static CommonData* data_;
};
