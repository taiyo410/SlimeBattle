#include<DxLib.h>
#include<string>
#include<EffekseerForDXLib.h>
#include"../Application.h"
#include"../Utility/SunUtility.h"
#include"../Common/Parameta.h"
#include"../Manager/InputManager.h"
#include"../Manager/EffectManager.h"
#include"../Manager/ModelManager.h"
#include"../Manager/SoundManager.h"
#include"SlimeBase.h"
#include"../Scene/SceneGame.h"
#include"Stage.h"
#include"ItemBase.h"
#include"GaugeCircle.h"
#include"Speaker.h"
#include"Player.h"
////�X���C���̏�ԉ摜
//const std::string BLUE_NORMAL_FACE = "NormalK.png";
//const std::string BLUE_TIRED_FACE = "Tukare.png";
//const std::string BLUE_DAMAGE_FACE = "DamageK.png";
//const std::string BLUE_CHARGE_FACE = "ChargeK.png";
//const std::string BLUE_ATTACK_FACE = "AttackK.png";
//
////�I�����W�X���C����ԉ摜
//const std::string ORANGE_NORMAL_FACE = "NormalY.png";
//const std::string ORANGE_TIRED_FACE = "TukareY.png";
//const std::string ORANGE_DAMAGE_FACE = "DamageY.png";
//const std::string ORANGE_CHARGE_FACE = "ChargeY.png";
//const std::string ORANGE_ATTACK_FACE = "AttackY.png";


//�p�����^�̏�����
void Player::SetParam(VECTOR _initPos, int _padNum,int _enemyNum, ModelManager::MODEL_TYPE _modelType,SunUtility::DIR_3D _initDir)
{
#pragma region �p�����^�̏�����
	modelType_ = _modelType;
	dir_ = _initDir;

	//�X���C����ԉ摜�̃��[�h
	if (modelType_ == ModelManager::MODEL_TYPE::BLUE_SLIME)
	{
		facePos_ = { BLUE_SLIME_FACE_POS_X,BLUE_SLIME_FACE_POS_Y };
		backSlimefacePos_ = facePos_;
		slimeFaceImgs_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE +BLUE_NORMAL_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + BLUE_TIRED_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + BLUE_DAMAGE_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + BLUE_CHARGE_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + BLUE_ATTACK_FACE).c_str());
	}
	else if (modelType_ == ModelManager::MODEL_TYPE::ORANGE_SLIME)
	{
		facePos_ = { ORANGE_SLIME_FACE_POS_X,ORANGE_SLIME_FACE_POS_Y };
		backSlimefacePos_ = facePos_;
		slimeFaceImgs_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + ORANGE_NORMAL_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + ORANGE_TIRED_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + ORANGE_DAMAGE_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + ORANGE_CHARGE_FACE).c_str());
		slimeFaceImgs_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + ORANGE_ATTACK_FACE).c_str());
	}

	face_ = SLIME_FACE::NORMAL;

	pos_ = _initPos;
	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };
	padNum_ = _padNum;
	enemyNum_ = _enemyNum;

	revivalPos_ = { _initPos.x,REVIVAL_HEIGHT_POS_Y,_initPos.z };

	auto& ins = EffectManager::GetEffect();
	//�G�t�F�N�g�̃��[�h
	shieldPos_={ 0.0f,0.0f,0.0f };
	shieldRot_={ 0.0f,0.0f,0.0f };
	shieldScl_ = { SHIELD_SCALE,SHIELD_SCALE,SHIELD_SCALE };
	shieldPar_ = { shieldPos_,shieldRot_,shieldScl_ };

	waidAtkPar_.pos= { 0.0f,0.0f,0.0f };
	waidAtkPar_.rot= { 0.0f,0.0f,0.0f };
	waidAtkPar_.scl= { 0.0f,0.0f,0.0f };

	waidChargePar_.pos = SunUtility::VECTOR_ZERO;
	waidChargePar_.rot = SunUtility::VECTOR_ZERO;
	waidChargePar_.scl = { WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL };

	//�K�[�h�N�[���^�C���Q�[�W�T�C�Y������
	guardCoolTimeGaugeSize_ = GUARD_GAUGE_SIZE_DEFAULT;

	hp_ = MAX_HP;

	hpPercent_ = static_cast<float>(hp_ / MAX_HP);

	isUseItem_ = false;


	//�W�����v��
	jumpPower_ = 0.0f;

	//�W�����v����
	isJump_ = false;

	//�X�^�~�i
	stamina_ = STAMINA_MAX;

	staminaConsum_ = STAMINA_MAX;
	staminaConsumPercent_ = 1.0f;

	staminaPercent_ = 1.0f;

	//�X�^�~�i�������Ă邩
	isStaminaRecov_ = false;

	//�v���C���[���
	pState_ = SlimeBase::PLAYERSTATE::ACTIONABLE;

	//�t���[���J�E���g
	frame_ = FRAME_DEFAULT;

	////�X�e�b�v�J�E���g
	stepFrame_ = STEP_FRAME_MAX;

	//�X�e�b�v���f
	isStep_ = false;

	guardCoolTime_ = 0;

	updown_ = UP_AND_DOWN::UP;

	invincibleCnt_ = 0;

	coolTime_ = 0;

	itemReGetCnt_ = 0;

	gravityPow_ = DEFAULT_GRAVITY;

	fallDmg_ = FALL_DMG_DEFAULT;

	fallScore_ = FALL_SCORE_DEFAULT;

#pragma endregion
}
//�v���C���[��ԃZ�b�^
void Player::SetPlayerState(const SlimeBase::PLAYERSTATE playerState)
{
	pState_ = playerState;
}


//�X�V����
void Player::Update(void)
{
	SlimeBase::Update();

	//�d�͂�������
	if (pState_ != SlimeBase::PLAYERSTATE::REVIVAL)
	{
		AddGravity(gravityPow_);
	}

	hpPercent_ = static_cast<float>(hp_) / static_cast<float>(MAX_HP);
	if (hp_ < 0)
	{
		hp_ = 0;
	}
	//�X�^�~�i�����X�V
	staminaPercent_ = stamina_ / STAMINA_MAX;

	staminaConsumPercent_ = staminaConsum_ / STAMINA_MAX;
	//�t���[������
	FrameUpdate();

	//�A�C�e������
	ItemUpdate();

	//�J�E���^�[�N�[���^�C�����Z
	GuardCoolTimeConsum();


	if (staminaConsum_ <= CHARGE_STAMINA_VAL && staminaConsum_ <= CHARGE_STAMINA_PER_FRAME)
	{
		staminaConsum_ = 0;
	}
	//�X�^�~�i����@
	if (stamina_ >= STAMINA_MAX)
	{
		stamina_ = STAMINA_MAX;
	}

}
//�`�揈��
void Player::Draw(void)
{
	SlimeBase::Draw();

	if (pState_ == SlimeBase::PLAYERSTATE::CHARGE)
	{
		VECTOR pos = VECTOR();
		VECTOR framePos = VECTOR();

		//�v���C���[�̓���̃��[���h���W
		pos = VAdd(pos_, LOCAL_GAUGE_POS);
		framePos = VAdd(pos_, LOCAL_GAUGE_POS);

		//���[���h���W���X�N���[�����W�ɕϊ�
		pos = ConvWorldPosToScreenPos(pos);
		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::CHARGE, pos, GAUGE_SIZE, GAUGE_SIZE, chargePer_, true);
	}

	if (modelType_ == ModelManager::MODEL_TYPE::BLUE_SLIME)
	{
		facePos_ = { BLUE_SLIME_FACE_POS_X,BLUE_SLIME_FACE_POS_Y };
		backSlimefacePos_ = facePos_;

		//�p���B�N�[���^�C���Q�[�W�̕`��
		VECTOR parryPos;
		parryPos = ConvWorldPosToScreenPos(PARRY_POS_BLUE);

		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::PARRY_K, parryPos, guardCoolTimeGaugeSize_, guardCoolTimeGaugeSize_, guardCoolTimePercent_, false);

		//�����O�p�`
		DrawDirTriangle(pos_, dir_, BLUE_SLIME_COLOR);

		//�X�^�~�i�Q�[�W
		//�O�g
		DrawBox(STAMINA_GAUGE_X, STAMINA_GAUGE_Y, STAMINA_GAUGE_WIDTH_POS_X, STAMINA_GAUGE_WIDTH_POS_Y
			, SunUtility::BLACK, true);

		//����
		DrawBox(STAMINA_GAUGE_WIDTH_POS_X- STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_Y+ STAMINA_GAUGE_INNER_OFFSET
			, STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET - staminaPercent_ * STAMINA_GAUGE_WIDTH, 
			STAMINA_GAUGE_WIDTH_POS_Y- STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_CURRENT_COLOR, true);
		DrawBox(STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_Y + STAMINA_GAUGE_INNER_OFFSET
			, STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET - staminaConsumPercent_ * STAMINA_GAUGE_WIDTH, STAMINA_GAUGE_WIDTH_POS_Y- STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_CONSUMPTION_COLOR, true);
	}
	else
	{
		facePos_ = { ORANGE_SLIME_FACE_POS_X,ORANGE_SLIME_FACE_POS_Y };
		backSlimefacePos_ = facePos_;
		//�p���B�N�[���^�C���Q�[�W�̕`��
		VECTOR parryPos;
		parryPos = ConvWorldPosToScreenPos(PARRY_POS_ORANGE);

		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::PARRY_Y, parryPos, guardCoolTimeGaugeSize_, guardCoolTimeGaugeSize_, guardCoolTimePercent_, false);

		//�����O�p�`
		DrawDirTriangle(pos_, dir_, ORANGE_SLIME_COLOR);

		//�O�g
		DrawBox(Application::SCREEN_SIZE_X - STAMINA_GAUGE_WIDTH_POS_X, STAMINA_GAUGE_Y
			, Application::SCREEN_SIZE_X - STAMINA_GAUGE_X, STAMINA_GAUGE_WIDTH_POS_Y, SunUtility::BLACK, true);

		//����
		DrawBox(Application::SCREEN_SIZE_X - STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_Y + STAMINA_GAUGE_INNER_OFFSET
			, Application::SCREEN_SIZE_X - STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET + staminaPercent_ * STAMINA_GAUGE_WIDTH
			, STAMINA_GAUGE_WIDTH_POS_Y - STAMINA_GAUGE_INNER_OFFSET
			, STAMINA_GAUGE_CURRENT_COLOR, true);
		DrawBox(Application::SCREEN_SIZE_X - STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET
			, STAMINA_GAUGE_Y + STAMINA_GAUGE_INNER_OFFSET
			, Application::SCREEN_SIZE_X - STAMINA_GAUGE_WIDTH_POS_X - STAMINA_GAUGE_INNER_OFFSET + staminaConsumPercent_ * STAMINA_GAUGE_WIDTH
			, STAMINA_GAUGE_WIDTH_POS_Y - STAMINA_GAUGE_INNER_OFFSET, STAMINA_GAUGE_CONSUMPTION_COLOR, true);
	}

}
//�������
bool Player::Release(void)
{
	EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET, this);
	return true;
}

const VECTOR Player::GetPos(void)const 
{
	return pos_;
}

/// <summary>
	/// �f�o�b�O�p�֐�
	/// </summary>
	/// <param name=""></param>
void Player::DrawDebug(void)
{
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
	{
		VECTOR player2Pos = sceneGame_->GetEnemyPos();
		VECTOR posP2P = { pos_.x - player2Pos.x,RADIUS,pos_.z - player2Pos.z };
	}
	
	DrawFormatString(0, 16, 0x000000
		, "PlayerPos(%.1f,%.1f,%.1f)\nFrame(%.1f)\nStamina(%.8f)\nState(%d)\nStep(%d)\nstaminaConsum(%.1f)\nHpPercent(%d)\ndir(%d)\nCnt(%d)"
		, pos_.x, pos_.y, pos_.z
		, frame_
		, stamina_
		, pState_
		, stepFrame_
		, staminaConsum_
		, hp_
		, dir_
		,waidChargeCnt_);

	if (item_ != nullptr)
	{
		DrawFormatString(0, 250-16, 0x000000, "P1Item(%.2f)", item_->GetWaidAtk());
	}

}

//�X�^�~�i������
void Player::FrameUpdate(void)
{
	if (stamina_ > 0.0f)return;
	frame_ = FRAME_DEFAULT;
	stamina_ = 0.0f;
	pState_ = SlimeBase::PLAYERSTATE::ACTIONABLE;
	isStaminaRecov_ = true;

}

//�X�^�~�i�񕜏���
void Player::StaminaRecovery(void)
{
	if (stamina_ < STAMINA_MAX)
	{
		staminaRecov_ += STAMINA_RECOVE_SPEED;
		if (staminaRecov_ == STAMINA_RECOV_MAX)
		{
			stamina_ += staminaRecov_;
			staminaConsum_ = stamina_;
			staminaRecov_ = 0;
		}
	}
}

//���߈ړ�
void Player::ChargeStart(void)
{
	//�W�����v���͗��߂��Ȃ�
	if (isJump_)return;

	if (InputManager::GetInput().IsPadDown(padNum_, PAD_INPUT_UP))
	{
		dir_ = SunUtility::DIR_3D::FLONT;
	}

	else if (InputManager::GetInput().IsPadDown(padNum_, PAD_INPUT_RIGHT))
	{
		dir_ = SunUtility::DIR_3D::RIGHT;
	}

	else if (InputManager::GetInput().IsPadDown(padNum_, PAD_INPUT_DOWN))
	{
		dir_ = SunUtility::DIR_3D::BACK;
	}

	else if (InputManager::GetInput().IsPadDown(padNum_, PAD_INPUT_LEFT))
	{
		dir_ = SunUtility::DIR_3D::LEFT;
	}

	if (InputManager::GetInput().IsPadKeep(padNum_, PAD_INPUT_A))
	{
		MoveDecide();
	}



}

//�ړ�����
void Player::ProcessMove(void)
{
	//�W�����v�ȊO�̏���
	if (isJump_)return;

	SunUtility::DIR_3D dir = SunUtility::DIR_3D::MAX;

	dir = dir_;

	//�ړ�
	if (InputManager::GetInput().IsPadRelease(padNum_, PAD_INPUT_A))
	{
		frameNum_ = frame_;
		if (pState_ == SlimeBase::PLAYERSTATE::CHARGE)
		{
			StopJoypadVibration(padNum_, -1);
			ChangePlayerState(SlimeBase::PLAYERSTATE::NORMALATTACK);
		}
		else
		{
			ChangePlayerState(SlimeBase::PLAYERSTATE::STEP);
		}
	}
}

//�m�b�N�o�b�N����
void Player::KnockBuckUpdate(void)
{
	auto& ins = CommonData::GetData();
	knockBackCnt_--;
	SunUtility::DIR_3D dir;
	if (ins.GetMode() == CommonData::MODE::PVE)
	{
		dir = sceneGame_->GetEnemyDir();
	}
	else if(ins.GetMode()==CommonData::MODE::PVP)
	{
		dir = sceneGame_->GetPlayer2Dir();
	}
	KnockBack();
	if (!MoveLimit())
	{
		StopJoypadVibration(padNum_, -1);
		ChangePlayerState(SlimeBase::PLAYERSTATE::FALL);
	}
	if (knockBackCnt_ < 0)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::COOL);
	}
}

//�x�[�X�Ɉ����idiff�̒l�j��ǉ����č��
void Player::KnockBack(void)
{
	auto& ins = CommonData::GetData();
	VECTOR diff = {};
	if (ins.GetMode() == CommonData::MODE::PVE)
	{

		//���W�Ńm�b�N�o�b�N�𔻒肷��
		diff = VSub(pos_, sceneGame_->GetEnemyPos());	//���肩�玩���������Ƒ���ւ̕����������B
	}
	else if(ins.GetMode() == CommonData::MODE::PVP)
	{
		//���W�Ńm�b�N�o�b�N�𔻒肷��
		diff = VSub(pos_, sceneGame_->GetPlayerPos(enemyNum_));	//���肩�玩���������Ƒ���ւ̕����������B
	}
	
	//�m�b�N�o�b�N�͎����Ƃ͋t������i�����[����j
	auto dir = VNorm(diff);
	auto dir4 = SunUtility::ToDirection(dir);


	DirUpdate(dir4);

}



//�`���[�W�ƃX�e�b�v�����߂鏈��
void Player::MoveDecide(void)
{
	ChangePlayerState(SlimeBase::PLAYERSTATE::STEPKEEP);
	if (stepFrame_ < 0)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::CHARGE);
	}
}

void Player::StaminaLowLimit(float staminaConsumPerFrame)
{
	if (staminaConsum_ <= staminaConsumPerFrame)
	{
		staminaConsum_ = 0;
	}
}

void Player::SetGuardCoolTime(const int guardCooltime)
{
	guardCoolTime_ = guardCooltime;
}

void Player::SetMarginPos(SunUtility::DIR_3D marginDir)
{
	switch (dirMargin_)
	{
	case SunUtility::DIR_3D::FLONT:
		pos_.z = sceneGame_->GetEnemyPos().z+RADIUS + POS_MARGIN;
		break;
	case SunUtility::DIR_3D::BACK:
		pos_.z -= sceneGame_->GetEnemyPos().z-RADIUS - POS_MARGIN;
		break;
	case SunUtility::DIR_3D::RIGHT:
		pos_.x = sceneGame_->GetEnemyPos().x + RADIUS + POS_MARGIN;
		break;
	case SunUtility::DIR_3D::LEFT:
		pos_.x = sceneGame_->GetEnemyPos().x - RADIUS - POS_MARGIN;
		break;
	}
}

#pragma region	��Ԃ̍X�V����

void Player::CoolUpdate(void)
{
	coolTime_--;
	if (coolTime_ <= 0)
	{
		coolTime_ = 0;
		ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
	}

	if (!MoveLimit())
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::FALL);
	}
}

//�s���\��Ԃ̎��̏���
void Player::ActionableUpdate(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::IDLE);

	//�񕜏���
	StaminaRecovery();

	face_ = SLIME_FACE::NORMAL;
	if (staminaPercent_ <= STAMINA_TIRED)
	{
		face_ = SLIME_FACE::TIRED;
	}
	ChargeStart();
	auto& ins = InputManager::GetInput();
	//E�L�[�������ƃK�[�h���
	if (ins.IsPadKeep(padNum_, PAD_INPUT_6) && guardCoolTime_ == 0)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::GUARD);
	}

	if (!MoveLimit())
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::FALL);
	}

	GetItemUpdate();

}

//�X�e�b�v��t���
void Player::StepKeepUpdate(void)
{
	stepFrame_--;
	ProcessMove();
	if (stepFrame_ < 0)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::CHARGE);
	}
}


//�������
void Player::StepUpdate(void)
{
	//�X�e�b�v��t���ԓ��ɃL�[�𗣂�����
	if (stepFrame_ >= 0)
	{
		model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::STEP);
		DirUpdate(dir_);
		
		//�t���[�������炷
		frame_--;
		if (frame_ <= 0)
		{
			ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
		}
		//�X�e�b�v���X�^�~�i�����炷
		stamina_--;
	}
	else
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::CHARGE);
	}
}

//����
void Player::ChargeUpdate(void)
{
	
	auto& ins = InputManager::GetInput();
	if (stamina_ >= 0.0f)
	{
		frame_ += CHARGE_SPEED;
	}
	
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::CHARGE);
	StartJoypadVibration(padNum_, static_cast<int>(frame_ * 10), -1, -1);
	if (staminaConsum_ > 0)
	{
		chargePer_ = frame_ / FRAME_MAX;
	}
	
	if (staminaConsum_>=0&&frame_<=FRAME_MAX)
	{
		staminaConsum_ -= CHARGE_STAMINA_PER_FRAME;
	}
	else if(frame_>=FRAME_MAX)
	{
		staminaConsum_ -= 0;
	}
	StaminaLowLimit(CHARGE_STAMINA_PER_FRAME);

	ProcessMove();

	//���߃L�����Z��
	if (ins.IsPadKeep(padNum_,PAD_INPUT_5))
	{
		StopJoypadVibration(padNum_, -1);
		ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
	}

}

//�U��
void Player::NormalAttackUpdate(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::ATTACK);
	DirUpdate(dir_);

	//�t���[�������炷
	frame_--;
	stamina_ -= CHARGE_ATK_STAMINA;
	if (frame_ <= 0.0f||stamina_<=0.0f)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::CRITICALATTACK);
	}
}

void Player::CriticalUpdate(void)
{
	criticalCnt_--;
	if (criticalCnt_ <= 0&&pos_.y<=RADIUS)
	{
		ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
	}
}

void Player::GuardCoolTimeConsum(void)
{
	guardCoolTime_--;
	guardCoolTimePercent_ =SunUtility::PERCENT_MAX_F - static_cast<float>(guardCoolTime_) / static_cast<float>(GUARD_COOLTIME);
	if (guardCoolTime_ < 0)
	{
		guardCoolTime_ = 0;
		ShakeNum(guardCoolTimeGaugeSize_, GUARD_GAUGE_SIZE_DEFAULT, GUARD_GAUGE_SIZE_MARGIN, 1);
	}
	else
	{
		guardCoolTimeGaugeSize_ = GUARD_GAUGE_SIZE_DEFAULT;
	}
}

void Player::ItemUpdate(void)
{
	//�A�C�e�����Ƃ������̏���(�v���C���[�̍U����Ԃ��I����Ă��L�͈͍U���𓮂�������悤�ɂ��邽��)
	if (item_ == nullptr)
	{
		itemReGetCnt_--;
		EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::WAIDATK, this);
		return;
	}

	if (isUseItem_)
	{
		itemGetPar_.pos = pos_;
		itemGetPar_.pos.y -= RADIUS;
		itemGetPar_.rot = SunUtility::VECTOR_ZERO;
		itemGetPar_.scl = { ITEM_SCL,ITEM_SCL,ITEM_SCL };
		itemGetPar_.isLoop = true;
		if (itemGetEffPlay_)
		{
			EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::ITEMGET, this, itemGetPar_);
			itemGetEffPlay_ = false;
		}

		EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::ITEMGET, this, itemGetPar_);

	}
	if (item_->GetIsAtkAlive() && item_->GetWaidAtk() < ItemBase::WAID_ATK_COL)
	{
		item_->UpdateWaidAttack();
		waidAtk_ = WAID_ATK::ATK;
		waidAtkPar_.scl = { item_->GetWaidAtk() * WAID_ATK_COLMARGIN,item_->GetWaidAtk() * WAID_ATK_COLMARGIN,item_->GetWaidAtk() * WAID_ATK_COLMARGIN };
		EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::WAIDATK, this, waidAtkPar_);
	}

	else if (item_->GetWaidAtk() >= ItemBase::WAID_ATK_COL)
	{
		waidAtk_ = WAID_ATK::END;
		item_->SetWaidAtk(0);
		item_->SetWaidAtk(false);
		itemReGetCnt_ = ITEM_REGET_CNT;
		item_ = nullptr;
	}

}

void Player::GetItemUpdate(void)
{
	if (!isUseItem_)return;
	auto& ins = InputManager::GetInput();
	if (ins.IsPadKeep(padNum_, PAD_INPUT_X))
	{
		ItemBase::ITEM_TYPE itemType = item_->GetItemType();
		switch (itemType)
		{
		case ItemBase::ITEM_TYPE::SPEEKER:
			ChangePlayerState(SlimeBase::PLAYERSTATE::WAIDATTACK);
			break;
		case ItemBase::ITEM_TYPE::MAX:
			break;
		default:
			break;
		}

	}
}

void Player::FallUpdate(void)
{
	fallCnt_--;
	if (fallCnt_ <= 0)
	{
		Damage(fallDmg_,0);
		AddScore(-fallScore_);
		ChangePlayerState(SlimeBase::PLAYERSTATE::REVIVAL);
	}
}

void Player::RevivalUpdate(void)
{
	revivalCnt_--;
	SetPos(revivalPos_);
	if (revivalCnt_ <= 0)
	{
		SetInvincible(AFTER_REVIVAL_CNT);
		ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
	}
}


void Player::GuardUpdate(void)
{
	guardCnt_--;
	shieldPar_.pos = pos_;

	EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::SHIELD,this,shieldPar_);
	if (!sceneGame_->GetIsCollision())
	{
		guardCoolTime_ = GUARD_COOLTIME;
	}
	if (guardCnt_ < 0 || InputManager::GetInput().IsPadRelease(padNum_,PAD_INPUT_6) || sceneGame_->GetIsCollision())
	{
		EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::SHIELD, this);
		ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
	}
}

void Player::WaidAtkUpdate(void)
{
	waidChargeCnt_++;
	switch (waidAtk_)
	{
	case WAID_ATK::CHARGE:
		waidChargePar_.pos = pos_;
		waidChargePar_.pos.y -= RADIUS;
		EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::WAIDCHARGE, this, waidChargePar_);
		if (waidChargeCnt_ > WAID_CHARGE_MAX)
		{
			waidChargeCnt_ = WAID_CHARGE_MAX;
			ChangeWaidAtkState(WAID_ATK::JUMP);
		}
		break;
	case WAID_ATK::JUMP:
		//�ǂ̂��炢�̎��ԏ�ɏオ�邩
		jumpCnt_++;
		SetJumpPower(WIDE_JUMP_POWER);
		Jump();
		if (jumpCnt_ > WAID_JUMPCNT_MAX)
		{
			jumpCnt_ = WAID_JUMPCNT_MAX;
			SetGravityPow(5.0f);
			ChangeWaidAtkState(WAID_ATK::JUMPEND);
		}
		break;
	case WAID_ATK::JUMPEND:
		if (pos_.y <= RADIUS)
		{
			SetIsUse(false);
			EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET,this);
			ChangeWaidAtkState(WAID_ATK::ATK);
		}
		break;
	case WAID_ATK::ATK:
		item_->IsAtkAlive();
		ChangeWaidAtkState(WAID_ATK::END);
		
		
	break;
	case WAID_ATK::END:
		if (pos_.y <= RADIUS)
		{
			ChangePlayerState(SlimeBase::PLAYERSTATE::ACTIONABLE);
		}
		break;
	}
}

void Player::ChangeWaidAtkState(const WAID_ATK waidAtk)
{
	waidAtk_ = waidAtk;
	switch (waidAtk_)
	{
	case WAID_ATK::CHARGE:
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATKCHARGE, DX_PLAYTYPE_BACK, SE_VOL);
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDCHARGE, this, waidChargePar_);
		break;
	case WAID_ATK::JUMP:
		break;
	case WAID_ATK::JUMPEND:
		gravityPow_ = WAID_ATK_FALL_GRAVITY;
		break;
	case WAID_ATK::ATK:
		waidAtkPar_.pos = pos_;
		waidAtkPar_.scl = { 0.0f,0.0f,0.0f };
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATK, DX_PLAYTYPE_BACK, SE_VOL);
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDATK, this, waidAtkPar_);
		break;
	case WAID_ATK::END:
		gravityPow_ = DEFAULT_GRAVITY;

		break;
	default:
		break;
	}
}



#pragma endregion

void Player::StateUpdate(void)
{
	if (stamina_ < 0.0f)return;
	switch (pState_)
	{
	case SlimeBase::PLAYERSTATE::COOL:
		CoolUpdate();
		break;
	case SlimeBase::PLAYERSTATE::DEBUFF:
		break;
	case SlimeBase::PLAYERSTATE::ACTIONABLE:
		ActionableUpdate();
		break;
	case SlimeBase::PLAYERSTATE::STEPKEEP:
		StepKeepUpdate();
		break;
	case SlimeBase::PLAYERSTATE::STEP:
		StepUpdate();
		break;
	case SlimeBase::PLAYERSTATE::CHARGE:
		ChargeUpdate();
		break;
	case SlimeBase::PLAYERSTATE::NORMALATTACK:
		NormalAttackUpdate();
		break;
	case SlimeBase::PLAYERSTATE::KNOCKBACK:
		KnockBuckUpdate();
		break;
	case SlimeBase::PLAYERSTATE::GUARD:
		GuardUpdate();
		break;
	case SlimeBase::PLAYERSTATE::WAIDATTACK:
		WaidAtkUpdate();
		break;
	case SlimeBase::PLAYERSTATE::CRITICALATTACK:
		CriticalUpdate();
		break;
	case SlimeBase::PLAYERSTATE::FALL:
		FallUpdate();
		break;
	case SlimeBase::PLAYERSTATE::REVIVAL:
		RevivalUpdate();
		break;

	}
}

//��ԕω��֐�
void Player::ChangePlayerState(SlimeBase::PLAYERSTATE state)
{
	pState_=state;
	atkPow_ = 0;
	switch (pState_)
	{
	case SlimeBase::PLAYERSTATE::ACTIONABLE:
		frame_ = FRAME_DEFAULT;
		atkPow_ = 0;
		break;
	case SlimeBase::PLAYERSTATE::STEPKEEP:
		stepFrame_ = STEP_FRAME_MAX;   
		break;
	case SlimeBase::PLAYERSTATE::STEP:
		model_->SetStepAnim(modelType_, 0.0f);
		staminaConsum_ -= STEP_STEMINA;
		sound_->PlaySe(SoundManager::SE_TYPE::SLIMEMOVE, DX_PLAYTYPE_BACK, SE_VOL);
		StaminaLowLimit(STEP_STEMINA);
		break;
	case SlimeBase::PLAYERSTATE::CHARGE:
		model_->SetStepAnim(modelType_, 0.0f);
		staminaConsum_ -= CHARGE_STAMINA_VAL;
		face_ = SLIME_FACE::CHARGE;
		break;
	case SlimeBase::PLAYERSTATE::NORMALATTACK:
		sound_->PlaySe(SoundManager::SE_TYPE::ATTACK, DX_PLAYTYPE_BACK, SE_VOL);
		atkPow_ = CHARGE_ATK_POW;
		model_->SetStepAnim(modelType_, 0.0f);
		face_ = SLIME_FACE::ATTACK;
		break;
	case SlimeBase::PLAYERSTATE::KNOCKBACK:
		face_ = SLIME_FACE::DAMAGE;
		StopJoypadVibration(padNum_);
		break;
	case SlimeBase::PLAYERSTATE::GUARD:
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::SHIELD, this, shieldPar_);
		atkPow_ = PARRY_ATK_POW;
		 guardCnt_ = GUARD_CNT_MAX;
		 face_ = SLIME_FACE::DAMAGE;
		break;
	case SlimeBase::PLAYERSTATE::WAIDATTACK:
		waidChargeCnt_ = 0;
		ChangeWaidAtkState(WAID_ATK::CHARGE);
		jumpCnt_ = 0;
		face_ = SLIME_FACE::ATTACK;
		break;
	case SlimeBase::PLAYERSTATE::CRITICALATTACK:
		criticalCnt_ = CRITICAL_CNT_MAX;
		atkPow_ = PARRY_ATK_POW;
		break;
	case SlimeBase::PLAYERSTATE::FALL:
		fallCnt_ = FALL_CNT;
		
		EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET,this);
		if (item_ != nullptr)
		{
			isItemUse_ = false;
			isUseItem_ = false;
			item_ = nullptr;
		}
		break;
	case SlimeBase::PLAYERSTATE::REVIVAL:
		revivalCnt_ = REVIVAL_CNT_MAX;
		SetInvincible(REVIVAL_CNT_MAX);
		fallDmg_ += FALL_DMG_INCREASE;
		fallScore_ += FALL_SCORE_INCREASE;
		stamina_ = STAMINA_MAX;
		staminaConsum_ = STAMINA_MAX;
		
		atkPow_ = 0;
		break;

	}
}

void Player::ShakeNum(int moveNum, int defaultNum, int rangeNum, int speedNum)
{
	switch (updown_)
	{
	case UP_AND_DOWN::UP:
		if (guardCoolTimeGaugeSize_ < defaultNum+rangeNum)
		{
			guardCoolTimeGaugeSize_ += speedNum;
		}
		else
		{
			updown_ = UP_AND_DOWN::DOWN;
		}
		break;
	case UP_AND_DOWN::DOWN:
		if (guardCoolTimeGaugeSize_ >= defaultNum -rangeNum)
		{
			guardCoolTimeGaugeSize_ -= speedNum;
		}
		else
		{
			updown_ = UP_AND_DOWN::UP;
		}
		break;
	}
}


