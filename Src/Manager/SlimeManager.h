#pragma once
#include<memory>
#include"../Common/CommonData.h"
#include"../Object/SlimeBase.h"

class SlimeBase;
class Player;
class Enemy;
class Player2;
class SlimeManager
{
public:
	SlimeManager(CommonData::MODE _mode);
	~SlimeManager(void);

	//定数
	//**********************************************
	//スライムの数
	static constexpr int SLIME_NUM = 2;

	//プレイヤー番号
	static constexpr int PLAYER = 0;

	//敵番号
	static constexpr int ENEMY = 1;
	//**********************************************

	/// <summary>
	/// 静的にインスタンス生成
	/// </summary>
	/// <param name="_mode"></param>
	static void CreateInstance(CommonData::MODE _mode,SceneGame* _sceneGame);

	//静的にインスタンスを取得
	static SlimeManager& GetInstance(void);

	void Init(SceneGame* _sceneGame);
	void Update(void);
	void Draw(void);

	//ゲッタ
	
	/// <summary>
	/// 座標
	/// </summary>
	/// <param name="i">プレイヤー番号</param>
	/// <returns></returns>
	const VECTOR GetPos(const int i)const { return slime_[i]->GetPos(); }
	/// <summary>
	/// 方向
	/// </summary>
	/// <param name="i">プレイヤー番号</param>
	/// <returns></returns>
	SunUtility::DIR_3D GetDir(int i)const { return slime_[i]->GetDir(); };


	//ゲッタ
	//Hpパーセント
	const float GetPlayerHpPercent(const int _num);

	//座標
	const VECTOR GetPos(const int _num);


private:
	//型指定
	using MODE = CommonData::MODE;

	static SlimeManager* instance_;
	CommonData::MODE mode_;
	SlimeBase* slime_[SLIME_NUM];
};

