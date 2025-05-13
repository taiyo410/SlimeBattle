#pragma once
#include "../Common/Parameta.h"
#include<string>
#include<vector>
#include<map>
class SoundManager
{
public:
	//�萔
	static constexpr int VOLUME_MAX = 100;
	//SE�̉���
	static constexpr int SE_VOL = 70;

	static constexpr int MAX_VOLUME_VALUE = 255;
	
	//�񋓌^
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
	//BGM�̃p�X�̎w��
	void BGMInit(void);

	//SE�̃p�X�̎w��
	void SEInit(void);

	/// <summary>
	/// BGM�̃��[�h
	/// </summary>
	/// <param name="bgm">BGM�̎��</param>
	void LoadBgm(const BGM_TYPE bgm);

	/// <summary>
	/// SE�̃��[�h
	/// </summary>
	/// <param name="se">SE�̎��</param>
	void LoadSe(const SE_TYPE se);
	/// <summary>
	/// BGM�Đ�
	/// </summary>
	/// <param name="bgm">BGM�̎��</param>
	/// <param name="type">�v���C�^�C�v</param>
	/// <param name="vol">����</param>
	void PlayBgm(BGM_TYPE bgm,int type,int volPer = VOLUME_MAX,bool isTopPosition = true);

	/// <summary>
	/// SE�Đ�
	/// </summary>
	/// <param name="se">SE�̎��</param>
	/// <param name="type">�Đ��^�C�v</param>
	/// <param name="volPer">����</param>
	/// <param name="isTopPosition">�Ȃ̏��߂ɖ߂邩�߂�Ȃ���</param>
	void PlaySe(SE_TYPE se, int type,int volPer = 100 , bool isTopPosition=true);
	void StopBgm(BGM_TYPE bgm);
	void StopSe(SE_TYPE se);

	void Release(void);

private:
	//�p�X���w�肷��
	std::map<BGM_TYPE, std::string>bgmPass_;
	std::map<SE_TYPE, std::string>sePass_;

	//BGM�̃^�C�v�w��
	std::map<BGM_TYPE, int>bgm_;

	//SE�̃^�C�v�w��
	std::map<SE_TYPE, int>se_;
};

