//#pragma once
#include "string"
#include"../Common/Vector2.h"
#include"../Utility/SunUtility.h"
#include"SceneBase.h"
#include"../Common/CommonData.h"
class InputManager;
class CommonData;
class SoundManager;
class Grid;
class RuleBase;
class SceneTitle : public SceneBase
{
public:
	//定数
	static constexpr int MOVE_SPEED_X = 1;
	static constexpr int KINTOUN_MOVE_SPEED_X = 10;

	//モード画像全体サイズ
	static constexpr int MODE_IMG_SIZE_X = 320;
	static constexpr int MODE_IMG_SIZE_Y = 60;
	//モード画像の描画サイズ
	static constexpr int MODE_DRAW_SIZE_X = 180;
	static constexpr int MODE_DRAW_SIZE_Y = 60;

	//ルール画像の描画サイズ
	static constexpr int RULE_DRAW_SIZE_X = 180;
	static constexpr int RULE_DRAW_SIZE_Y = 60;

	//選択画像の全体サイズ
	static constexpr int SELECT_SIZE_X = 240;
	static constexpr int SELECT_SIZE_Y = 60;

	//static constexpr int MODE_GOAL_MAX = 200;
	static constexpr int MODE_GOAL_MAX = 272;
	static constexpr int RULE_GOAL_MAX = 275;

	//モード画像切り替わりスピード
	static constexpr int MODE_MOVE_SPEED = 10;

	//タガメ剣持のアニメーション数
	static constexpr int TAGAME_ANIME_ALL = 3;
	static constexpr int TAGAME_ANIME_DIR = 1;
	static constexpr int TAGAME_SIZE_X = 80;
	static constexpr int TAGAME_SIZE_Y = 100;
	static constexpr float ANIM_SPEED_DEFAULT = 0.25f;
	static constexpr float TAGAME_MOVE_SPEED = 1.0f;
	static constexpr int TAGAME_MOVE_FRAME = SunUtility::DEFAULT_FPS * 1.0;
	//列挙型
	enum class MODE
	{
		PVP
		,PVE
		,MAX
	};
	
	//定数
	static constexpr float ROT_SPEED = 0.005f;

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理が続く　　false:処理が止まる</returns>
	bool Init(void) override;	

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
	/// 開放処理
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:処理が続く	false:処理が止まる</returns>
	bool Release(void) override;	

private:
	//ポインター宣言
	InputManager* inputManager_;
	Grid* grid_;
	SoundManager* sound_;
	//RuleBase* ruleBase_;
	//メンバー変数
	int circleSlimeImage_;		//タイトル画像の格納領域
	int bgImage_;		//タイトル画像の格納領域
	int kintounImage_;		//タイトル画像の格納領域
	int rogoImage_;		//ロゴ画像
	int cloudImage_;		//雲画像
	int modeImage_;		//モード選択用画像
	int ruleImage_;		//モード選択用画像
	int selectImage_;	//選択画像
	int tagameImg_[TAGAME_ANIME_ALL];		//タガメ剣持


	CommonData::MODE mode_;		//モード表示用
	CommonData::RULE rule_;				//ルール表示用

	bool moveFlg_;	//動かすかのフラグ	true:動かす

	float rot_;		//回転用

	int cntAnim_;	//アニメーションカウント
	float speedAnim_;	//アニメーションスピード

	int moveframe_;		//タガメ剣持の移動カウント

	Vector2 cloudPos_;	//雲画像用
	Vector2 kintounPos_;	//雲画像用
	Vector2 modeImgRectPos_;	//ロゴ矩形座標
	Vector2 ruleImgRectPos_;	//ロゴ矩形座標
	Vector2 modeGoalPos_;		//どこまで動かすかの座標
	Vector2 ruleGoalPos_;		//どこまで動かすかの座標
	Vector2 selectPos_;			//選択画像座標
	Vector2 startPos_;			//タガメ剣持が動き始める座標

	Vector2 tagamePos_;			//タガメ座標
	double tagameRot_;			//タガメ

		//セレクト
	CommonData::SELECT select_;
	//モード
	//CommonData::MODE mode_;
	//ルール種別
	//CommonData::RULE rule_;



	//セレクト更新
	void ModeUpdate(void);

	//モード更新　
	void RuleUpdate(void);

	void ChangeSelect(CommonData::SELECT select);
	void ChangeRule(const CommonData::RULE rule);
	void ChangeMode(const CommonData::MODE mode);

	//タガメ剣持の移動
	void MoveTagame(int move);



	/// <summary>
	/// デバッグ用の関数
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);
};
