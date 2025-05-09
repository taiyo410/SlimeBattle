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

	//�萔
	//**********************************************
	//�X���C���̐�
	static constexpr int SLIME_NUM = 2;

	//�v���C���[�ԍ�
	static constexpr int PLAYER = 0;

	//�G�ԍ�
	static constexpr int ENEMY = 1;
	//**********************************************

	/// <summary>
	/// �ÓI�ɃC���X�^���X����
	/// </summary>
	/// <param name="_mode"></param>
	static void CreateInstance(CommonData::MODE _mode,SceneGame* _sceneGame);

	//�ÓI�ɃC���X�^���X���擾
	static SlimeManager& GetInstance(void);

	void Init(SceneGame* _sceneGame);
	void Update(void);
	void Draw(void);

	//�Q�b�^
	
	/// <summary>
	/// ���W
	/// </summary>
	/// <param name="i">�v���C���[�ԍ�</param>
	/// <returns></returns>
	const VECTOR GetPos(const int i)const { return slime_[i]->GetPos(); }
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="i">�v���C���[�ԍ�</param>
	/// <returns></returns>
	SunUtility::DIR_3D GetDir(int i)const { return slime_[i]->GetDir(); };


	//�Q�b�^
	//Hp�p�[�Z���g
	const float GetPlayerHpPercent(const int _num);

	//���W
	const VECTOR GetPos(const int _num);


private:
	//�^�w��
	using MODE = CommonData::MODE;

	static SlimeManager* instance_;
	CommonData::MODE mode_;
	SlimeBase* slime_[SLIME_NUM];
};

