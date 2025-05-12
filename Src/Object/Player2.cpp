#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"../Application.h"
#include"../Manager/InputManager.h"
#include"../Manager/EffectManager.h"
#include"../Object/GaugeCircle.h"
#include"../Object/Stage.h"
#include"../Object/ItemBase.h"
#include"../Object/Speaker.h"
#include"../Scene/SceneGame.h"
#include "Player2.h"


void Player2::SetParam(VECTOR _initPos, int _padNum, int _enemyNum)
{

	modelType_ = ModelManager::MODEL_TYPE::YUUHI;
	pos_ = INIT_POS;
	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };
	padNum_ = DX_INPUT_PAD2;
	
	
	dir_= SunUtility::DIR_3D::LEFT;

	revivalPos_ = { Stage::STAGE_ONE_SQUARE * 3,RADIUS * 5,0.0f };
	
	auto& ins = EffectManager::GetEffect();
	//�G�t�F�N�g�̃��[�h
	shieldPos_ = { 0.0f,0.0f,0.0f };
	shieldRot_ = { 0.0f,0.0f,0.0f };
	shieldScl_ = { 10.0f,10.0f,10.0f };
	shieldPar_ = { shieldPos_,shieldRot_,shieldScl_ };

	waidChargePar_.pos = SunUtility::VECTOR_ZERO;
	waidChargePar_.rot = SunUtility::VECTOR_ZERO;
	waidChargePar_.scl = { WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL };

	//�X���C����ԉ摜�̃��[�h
	slimeFaceImg_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + "NormalY.png").c_str());
	slimeFaceImg_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + "TukareY.png").c_str());
	slimeFaceImg_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + "DamageY.png").c_str());
	slimeFaceImg_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + "ChargeY.png").c_str());
	slimeFaceImg_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + "AttackY.png").c_str());

	facePos_ = { Application::SCREEN_SIZE_X - 60 - 70,40 + 74 + 30 };
	backSlimefacePos_ = facePos_;

	textureFrame_ = LoadGraph((Application::PATH_IMAGE + "CircleFrame.png").c_str());

	hp_ = MAX_HP;

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

	invincibleCnt_ = 0;

	coolTime_ = 0;

	slimeNum_ = 1;

	gravityPow_ = DEFAULT_GRAVITY;

	//�K�[�h�N�[���^�C���Q�[�W�T�C�Y������
	guardCoolTimeGaugeSize_ = GUARD_GAUGE_SIZE_DEFAULT;

	fallDmg_ = FALL_DMG_DEFAULT;

	fallScore_ = FALL_SCORE_DEFAULT;
}

void Player2::DrawDebug(void)
{
	DrawFormatString(0, 300, 0x000000
		, "PlayerPos(%.1f,%.1f,%.1f)\nFrame(%.1f)\nStamina(%.8f)\nState(%d)\nStep(%d)\nstaminaConsum(%.1f)\nHpPercent(%d)\ndir(%d)\nCnt(%d)"
		, pos_.x, pos_.y, pos_.z
		, frame_
		, stamina_
		, pState_
		, stepFrame_
		, staminaConsum_
		, hp_
		, dir_
		, waidChargeCnt_);

	if (waidAtk_ == WAID_ATK::ATK)
	{

		VECTOR colPos = { pos_.x,pos_.y - RADIUS,pos_.z };
		DrawSphere3D(colPos, item_->GetWaidAtk(), 16, 0x00ff00, 0xffffff, false);
	}
	if (item_ != nullptr)
	{
		DrawFormatString(0, 250, 0x000000, "P2Item(%.2f)", item_->GetWaidAtk());
	}

	DrawBox(532, 630 - 32, 532 + GUARD_COOLTIME * 0.4, 630, 0x000000, true);
	DrawBox(533, 631 - 32, 531 + guardCoolTime_ * 0.4, 629, 0x990000, true);
}


void Player2::Update(void)
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
		itemGetPar_.scl = { 60,60,60 };
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

	//if (item_->GetWaidAtk() >= Speaker::WAID_ATK_COL)
	else if (item_->GetWaidAtk() >= ItemBase::WAID_ATK_COL/*&&!item_->GetIsAtkAlive()*/)
	{
		waidAtk_ = WAID_ATK::END;
		item_->SetWaidAtk(0);
		item_->SetWaidAtk(false);
		itemReGetCnt_ = ITEM_REGET_CNT;
		item_ = nullptr;
	}



	//�X�^�~�i�����X�V
	staminaPercent_ = stamina_ / STAMINA_MAX;

	staminaConsumPercent_ = staminaConsum_ / STAMINA_MAX;

	//�t���[������
	FrameUpdate();

	//�񕜏���
	StaminaRecovery();

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

void Player2::Draw(void)
{
	SlimeBase::Draw();
	//DrawDebug();

	DrawDirTriangle(pos_, dir_, SLIME_COLOR);



	if (pState_ == SlimeBase::PLAYERSTATE::CHARGE)
	{
		VECTOR pos = VECTOR();
		VECTOR framePos = VECTOR();

		//�v���C���[�̓���̃��[���h���W
		pos = VAdd(pos_, { 0.0f,0.0f,50.0f });
		framePos = VAdd(pos_, { 0.0f,0.0f,50.0f });

		//���[���h���W���X�N���[�����W�ɕϊ�
		pos = ConvWorldPosToScreenPos(pos);
		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::CHARGE, pos, 46, 46, chargePer_,true);
	}
	VECTOR parryPos = { 400.0f,50.0f,40.0f };
	parryPos = ConvWorldPosToScreenPos(parryPos);
	gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::PARRY_Y, parryPos, guardCoolTimeGaugeSize_, guardCoolTimeGaugeSize_, guardCoolTimePercent_,false);
}

bool Player2::Release(void)
{
	EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET, this);
	return false;
}


//�m�b�N�o�b�N����
void Player2::KnockBuckUpdate(void)
{
	auto& ins = CommonData::GetData();
	knockBackCnt_--;
	SunUtility::DIR_3D dir;
	
	//dir = sceneGame_->GetPlayerDir();
	
	KnockBack();
	if (!MoveLimit())
	{
		ChangeState(SlimeBase::PLAYERSTATE::FALL);
	}
	if (knockBackCnt_ < 0)
	{
		SetCoolTime(KNOCKBACK_AFTER_CNT);
		ChangeState(SlimeBase::PLAYERSTATE::COOL);
	}


}

//�x�[�X�Ɉ����idiff�̒l�j��ǉ����č��
void Player2::KnockBack(void)
{
	auto& ins = CommonData::GetData();
	VECTOR diff;

	//���W�Ńm�b�N�o�b�N�𔻒肷��
	diff = VSub(pos_, sceneGame_->GetPlayerPos(SceneGame::PLAYER));	//���肩�玩���������Ƒ���ւ̕����������B

	//�m�b�N�o�b�N�͎����Ƃ͋t������i�����[����j
	auto dir = VNorm(diff);
	auto dir4 = SunUtility::ToDirection(dir);

	DirUpdate(dir4);

}
