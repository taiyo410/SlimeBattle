#pragma once
#include "../Common/Parameta.h"
#include<string>
#include<vector>
#include<map>

class SlimeBase;

class EffectManager
{
public:
	
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	//シングルトン化
	//------------------------------
	static void CreateEffect(void);

	//定数
	//列挙型
	enum class EFF_TYPE
	{
		HIT
		,SHIELD
		,WAIDCHARGE
		,WAIDATK
		,ITEMGET
	};

	struct EFF_USER
	{
		SlimeBase* user_;
		int playId_;
		Parameta par;
	};

	struct EFF_DATA
	{
		int resId_;
		std::vector<EFF_USER> playIds_;
	};
	

	//エフェクトの初期化
	bool InitEffect(void);
	//外部でインスタンスを利用可能にするために
	//インスタンスで返す関数を用意
	static EffectManager& GetEffect(void);

	//インスタンスの削除
	void Destroy(void);

	//エフェクトマネージャの開放
	void ReleaseEffect(void);

	/// <summary>
	/// エフェクト再生処理
	/// </summary>
	/// <param name="par">座標、大きさ、角度</param>
	void PlayEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par);


	void SyncEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par);

	

	//エフェクト停止処理
	void StopEffect(void);
	void StopEffect(EFF_TYPE type);
	void StopEffect(EFF_TYPE type, SlimeBase* slime);

	//エフェクト削除処理
	void DeleteEffect(void);

	//エフェクト繰り返し処理
	bool IsPlayEffectEnd(EFF_TYPE type, SlimeBase* slime);

	//void ChangeEffect(EFF_TYPE effect,Parameta par);
private:
	EffectManager(void);
	~EffectManager(void);

	//コピーコンストラクタを利用不可にする
	EffectManager(const EffectManager& ins);

	//静的なインスタンス初期化
	static EffectManager* effect_;

	//エフェクトデータ格納
	//std::map<EFF_TYPE, EFF_DATA>effDatas_;
	//std::map<SlimeBase*, std::map<EFF_TYPE, EFF_DATA>>effDatas_;
	std::map<EFF_TYPE, EFF_DATA>effDatas_;

	//int effectPlayId_;	//エフェクトの再生用変数
	//int effectResId_;	//エフェクトのリセット

	EFF_TYPE effectEnum_;	//エフェクト変更用

	//エフェクトのロード
	void LoadEffect(void);

	Parameta parameta_;

	//座標
	VECTOR hitEffectPos_;	//ヒットエフェクト

	//大きさ
	VECTOR hitEffectScale_;	//ヒットエフェクト

	//角度
	VECTOR hitEffectRot_; //ヒットエフェクト
};

