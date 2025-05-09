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
	//�V���O���g����
	//------------------------------
	static void CreateEffect(void);

	//�萔
	//�񋓌^
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
	

	//�G�t�F�N�g�̏�����
	bool InitEffect(void);
	//�O���ŃC���X�^���X�𗘗p�\�ɂ��邽�߂�
	//�C���X�^���X�ŕԂ��֐���p��
	static EffectManager& GetEffect(void);

	//�C���X�^���X�̍폜
	void Destroy(void);

	//�G�t�F�N�g�}�l�[�W���̊J��
	void ReleaseEffect(void);

	/// <summary>
	/// �G�t�F�N�g�Đ�����
	/// </summary>
	/// <param name="par">���W�A�傫���A�p�x</param>
	void PlayEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par);


	void SyncEffect(EFF_TYPE effect, SlimeBase* slime, Parameta par);

	

	//�G�t�F�N�g��~����
	void StopEffect(void);
	void StopEffect(EFF_TYPE type);
	void StopEffect(EFF_TYPE type, SlimeBase* slime);

	//�G�t�F�N�g�폜����
	void DeleteEffect(void);

	//�G�t�F�N�g�J��Ԃ�����
	bool IsPlayEffectEnd(EFF_TYPE type, SlimeBase* slime);

	//void ChangeEffect(EFF_TYPE effect,Parameta par);
private:
	EffectManager(void);
	~EffectManager(void);

	//�R�s�[�R���X�g���N�^�𗘗p�s�ɂ���
	EffectManager(const EffectManager& ins);

	//�ÓI�ȃC���X�^���X������
	static EffectManager* effect_;

	//�G�t�F�N�g�f�[�^�i�[
	//std::map<EFF_TYPE, EFF_DATA>effDatas_;
	//std::map<SlimeBase*, std::map<EFF_TYPE, EFF_DATA>>effDatas_;
	std::map<EFF_TYPE, EFF_DATA>effDatas_;

	//int effectPlayId_;	//�G�t�F�N�g�̍Đ��p�ϐ�
	//int effectResId_;	//�G�t�F�N�g�̃��Z�b�g

	EFF_TYPE effectEnum_;	//�G�t�F�N�g�ύX�p

	//�G�t�F�N�g�̃��[�h
	void LoadEffect(void);

	Parameta parameta_;

	//���W
	VECTOR hitEffectPos_;	//�q�b�g�G�t�F�N�g

	//�傫��
	VECTOR hitEffectScale_;	//�q�b�g�G�t�F�N�g

	//�p�x
	VECTOR hitEffectRot_; //�q�b�g�G�t�F�N�g
};

