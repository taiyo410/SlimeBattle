#pragma once
#include<memory>
#include"../Common/CommonData.h"
#include"../Object/SlimeBase.h"

class SlimeBase;
class SlimeManager
{
public:
	SlimeManager(CommonData::MODE _mode);
	~SlimeManager(void);

	//定数
	//**********************************************
	static constexpr int SLIME_NUM = 2;
	//**********************************************

	/// <summary>
	/// 静的にインスタンス生成
	/// </summary>
	/// <param name="_mode"></param>
	static void CreateInstance(CommonData::MODE _mode);

	//静的にインスタンスを取得
	static SlimeManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
private:
	//型指定
	using MODE = CommonData::MODE;

	static SlimeManager* instance_;
	CommonData::MODE mode_;
	std::unique_ptr<SlimeBase>slime_[SLIME_NUM];
};

