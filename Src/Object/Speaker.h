#pragma once
#include"../Utility/SunUtility.h"
#include "ItemBase.h"
#include "SlimeBase.h"
class Speaker: public ItemBase
{
public:
	//�L�͈͍U���W�����v�p���[
	static constexpr float WIDE_JUMP_POWER = 50.0f;

	//�L�͈͍U���N�[���^�C��
	static constexpr int WAID_ATK_COOLTIME_MAX = SunUtility::DEFAULT_FPS * 10;

	//�L�͈͍U���`���[�W�ő�l
	static constexpr float WAID_CHARGE_MAX = SunUtility::DEFAULT_FPS * 1.3;
	static constexpr float WAID_JUMPCNT_MAX = SunUtility::DEFAULT_FPS * 0.3;
	static constexpr float WAID_COL_EXPAND_SPEED = 3.0f;

	//�J�����V�F�C�N�֘A
	//����
	static constexpr int SHALE_CNT = 10;
	//�U�ꕝ
	static constexpr int SHAKE_LIMIT = 10;

	////�͈͍U���̓����蔻��p
	//static constexpr float WAID_ATK_COL = SlimeBase::RADIUS * 3;

	//�L�͈͍U���̗������p�̏d��
	static constexpr float WAID_ATK_FALL_GRAVITY = 2.0f;
	//�L�͈͍U��
	enum class WAID_ATK
	{
		CHARGE
		, JUMP
		, JUMPEND
		, ATK
		, END
	};

	void Update(void)override;
	void Draw(void)override;
	void SetParam(void)override;
	//�L�͈͍U��
	void UpdateWaidAttack(void)override;

	


	
private:
	
};

