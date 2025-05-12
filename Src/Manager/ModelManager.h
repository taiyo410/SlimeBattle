#pragma once
#include<vector>
#include<map>
#include<string>
#include"../Utility/SunUtility.h"
class ModelManager
{
public:
	//�萔
	//�A�j���[�V�����f�t�H���g�̑��x
	static constexpr float ANIM_SPEED_DEFAULT = SunUtility::DEFAULT_FPS;

	//�p�x
	//�O
	static constexpr float FLONT_DEG = 180.0f;
	//���
	static constexpr float BACK_DEG = 0.0f;
	//�E
	static constexpr float RIGHT_DEG = 270.0f;
	//��
	static constexpr float LEFT_DEG = 180.0f;

	//�A�j���[�V�����̏I���
	static constexpr float END_ANIM = 59.0F;

	//�ǂݍ��ނ��̂��ǂ��������̂�
	enum class OBJECT
	{
		SLIME
		,ANIMAL
	};

	//�ǂݍ��ރ��f��
	enum class MODEL_TYPE
	{
		KOKAGE
		,YUUHI
	};
	//�A�j���[�V����
	enum class ANIM_TYPE 
	{
		IDLE
		, STEP
		, CHARGE
		, ATTACK
		, WIN
		, DRAW_K
		, DRAW_Y
		, MAX
	};

	//���f���f�[�^
	struct MODEL_DATA
	{

	};
	//���[�h���郂�f����I�ׂ�悤�ɂ���
	void ModelInit(void);

	std::map<OBJECT, MODEL_TYPE>object_;

	//���f���̃��[�h
	int LoadModel (MODEL_TYPE model);

	//���f���̃p�����[�^�ݒ�
	void SetModelParam(MODEL_TYPE model, VECTOR pos, SunUtility::DIR_3D dir);
	//�p�x
	void SetRotation(SunUtility::DIR_3D dir,MODEL_TYPE model);

	//�A�j���[�V��������
	void Animation(MODEL_TYPE model,VECTOR pos,VECTOR scl,SunUtility::DIR_3D dir);

	/// <summary>
	/// �A�j���[�V�����X�V����
	/// </summary>
	/// <param name="accel">�ǂꂾ���x�����邩</param>
	void AnimUpdate(MODEL_TYPE model,float accel);

	//���f���̕`��
	void DrawModel(MODEL_TYPE model);

	//�A�j���[�V�����I�������
	void EndAnimation(MODEL_TYPE model);

	//�A�j���[�V�����ω�
	void ChangeAnim(MODEL_TYPE model,ANIM_TYPE anim);

	//�A�j���[�V���������Ԃ̃Z�b�^
	void SetStepAnim(MODEL_TYPE model,float num);

	//���f���̍폜
	void DeleteModel(MODEL_TYPE model);

	//���f���n���h���̃Q�b�^
	int GetModelHandle(MODEL_TYPE model);

	//���f���n���h���Z�b�^
	void SetModelHandle(MODEL_TYPE model, int handle);
	

private:
	std::map<MODEL_TYPE, int>modelId_;

	//���f���t�@�C����
	std::map<MODEL_TYPE,std::string> modelFilePass_;

	//�p�x
	VECTOR rot_;

	////BGM�̃^�C�v�w��
	//std::map<MODEL_TYPE, int>model_;

	//�A�j���[�V�����̃A�^�b�`�ԍ�
	std::map<MODEL_TYPE,int>animAttachNo_;

	//�A�j���ԍ�
	std::map<MODEL_TYPE, int> animNo_;

	//�A�j���J�ڗp
	ANIM_TYPE anim_;

	//�A�j���[�V�����̑��Đ�����
	std::map<MODEL_TYPE, float> animTotalTime_;

	//�Đ����̃A�j���[�V��������
	std::map<MODEL_TYPE, float> stepAnim_;

	//�A�j���[�V�������x
	std::map<MODEL_TYPE, float> speedAnim_;

	//�A�j���I���������
	std::map<MODEL_TYPE, bool> endAnim_;

};

