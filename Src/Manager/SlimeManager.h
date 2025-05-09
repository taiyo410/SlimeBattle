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

	//�萔
	//**********************************************
	static constexpr int SLIME_NUM = 2;
	//**********************************************

	/// <summary>
	/// �ÓI�ɃC���X�^���X����
	/// </summary>
	/// <param name="_mode"></param>
	static void CreateInstance(CommonData::MODE _mode);

	//�ÓI�ɃC���X�^���X���擾
	static SlimeManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
private:
	//�^�w��
	using MODE = CommonData::MODE;

	static SlimeManager* instance_;
	CommonData::MODE mode_;
	std::unique_ptr<SlimeBase>slime_[SLIME_NUM];
};

