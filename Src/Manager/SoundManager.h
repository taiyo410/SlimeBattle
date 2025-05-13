#pragma once
#include "../Common/Parameta.h"
#include<string>
#include<vector>
#include<map>
class SoundManager
{
public:
	//定数
	static constexpr int VOLUME_MAX = 100;
	//SEの音量
	static constexpr int SE_VOL = 70;

	static constexpr int MAX_VOLUME_VALUE = 255;

	//パス関係
	//BGM
	//---------------------------------
	const std::string TITLE_BGM = "Title.mp3";
	//ゲームシーン
	const std::string GAME_BGM = "GameScene.mp3";
	//ゲームシーン２つ目
	const std::string GAME2_BGM = "GameScene2.mp3";
	//リザルト
	const std::string RESULT_BGM = "Result.mp3";
	//---------------------------------
	//SE
	//---------------------------------
	//ステップ
	const std::string STEP_SE = "MoveSlime.mp3";
	//攻撃
	const std::string ATTACK_SE = "Attack.mp3";
	//広範囲攻撃
	const std::string WAID_ATK_SE = "WaidAtk.mp3";
	//広範囲溜め
	const std::string CHARGE_WAID_ATK_SE = "WaidCharge.mp3";
	//ボタン
	const std::string BUTTON_SE = "button.mp3";
	//キャンセル
	const std::string CANCEL_SE = "Cancel.mp3";
	//カーソル動かすとき
	const std::string MOVE_CURSOR = "Cursor.mp3";
	//ゲームスタート音
	const std::string GAME_START_SE = "GameStart.mp3";
	//リザルトからタイトルへ移るときのSE
	const std::string RESULT_2_TITLE = "ResultButton.mp3";
	
	//列挙型
	enum class BGM_TYPE
	{
		TITLE
		,GAME
		,GAME2
		,RESULT
	};
	enum class SE_TYPE
	{
		SLIMEMOVE
		,ATTACK
		,WAIDATKCHARGE
		,WAIDATK
		,BUTTON
		,CANCEL
		,CURSOR
		,GAMESTART
		,RESULT_TITLE
	};
	//BGMのパスの指定
	void BGMInit(void);

	//SEのパスの指定
	void SEInit(void);

	/// <summary>
	/// BGMのロード
	/// </summary>
	/// <param name="bgm">BGMの種類</param>
	void LoadBgm(const BGM_TYPE bgm);

	/// <summary>
	/// SEのロード
	/// </summary>
	/// <param name="se">SEの種類</param>
	void LoadSe(const SE_TYPE se);
	/// <summary>
	/// BGM再生
	/// </summary>
	/// <param name="bgm">BGMの種類</param>
	/// <param name="type">プレイタイプ</param>
	/// <param name="vol">音量</param>
	void PlayBgm(BGM_TYPE bgm,int type,int volPer = VOLUME_MAX,bool isTopPosition = true);

	/// <summary>
	/// SE再生
	/// </summary>
	/// <param name="se">SEの種類</param>
	/// <param name="type">再生タイプ</param>
	/// <param name="volPer">音量</param>
	/// <param name="isTopPosition">曲の初めに戻るか戻らないか</param>
	void PlaySe(SE_TYPE se, int type,int volPer = 100 , bool isTopPosition=true);
	void StopBgm(BGM_TYPE bgm);
	void StopSe(SE_TYPE se);

	void Release(void);

private:
	//パスを指定する
	std::map<BGM_TYPE, std::string>bgmPass_;
	std::map<SE_TYPE, std::string>sePass_;

	//BGMのタイプ指定
	std::map<BGM_TYPE, int>bgm_;

	//SEのタイプ指定
	std::map<SE_TYPE, int>se_;
};

