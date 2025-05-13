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

