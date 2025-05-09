#include<DxLib.h>
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
#include"Player2.h"
#include"Player.h"

//パラメタの初期化
void Player::SetParam(void)
{
#pragma region パラメタの初期化
	//modelFileName_ = "SilmeAnimKokage.mv1";
	modelType_ = ModelManager::MODEL_TYPE::KOKAGE;
	dir_ = SunUtility::DIR_3D::RIGHT;

	//スライム状態画像のロード
	slimeFaceImg_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + "NormalK.png").c_str());
	slimeFaceImg_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + "Tukare.png").c_str());
	slimeFaceImg_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + "DamageK.png").c_str());
	slimeFaceImg_[SLIME_FACE::CHARGE]=LoadGraph((Application::PATH_IMAGE + "ChargeK.png").c_str());
	slimeFaceImg_[SLIME_FACE::ATTACK]=LoadGraph((Application::PATH_IMAGE + "AttackK.png").c_str());

	facePos_ = { FACE_POS_X,FACE_POS_Y };
	backSlimefacePos_ = facePos_;
	face_ = SLIME_FACE::NORMAL;

	pos_ = INIT_POS;
	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };
	padNum_ = DX_INPUT_KEY_PAD1;

	revivalPos_ = { -Stage::STAGE_ONE_SQUARE * 3,RADIUS * 5,0.0f };

	auto& ins = EffectManager::GetEffect();
	//エフェクトのロード
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

	slimeNum_ = 0;

	//ガードクールタイムゲージサイズ初期化
	guardCoolTimeGaugeSize_ = GUARD_GAUGE_SIZE_DEFAULT;
	
	speedAnim_ = ANIM_SPEED_DEFAULT;

	hp_ = MAX_HP;

	hpPercent_ = static_cast<float>(hp_ / MAX_HP);

	isUseItem_ = false;


	//ジャンプ力
	jumpPower_ = 0.0f;

	//ジャンプ判定
	isJump_ = false;

	//スタミナ
	stamina_ = STAMINA_MAX;

	staminaConsum_ = STAMINA_MAX;
	staminaConsumPercent_ = 1.0f;

	staminaPercent_ = 1.0f;

	//スタミナが減ってるか
	isStaminaRecov_ = false;

	//プレイヤー状態
	state_ = CommonData::PLAYERSTATE::ACTIONABLE;

	//フレームカウント
	frame_ = FRAME_DEFAULT;

	////ステップカウント
	stepFrame_ = STEP_FRAME_MAX;

	//ステップ判断
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
//プレイヤー状態セッタ
void Player::SetPlayerState(const CommonData::PLAYERSTATE playerState)
{
	state_ = playerState;
}


//bool Player::Init(SceneGame* parent)
//{
//	return true;
//}

//更新処理
void Player::Update(void)
{
	SlimeBase::Update();

	//重力をかける
	if (state_ != CommonData::PLAYERSTATE::REVIVAL)
	{
		AddGravity(gravityPow_);
	}

	hpPercent_ = static_cast<float>(hp_) / static_cast<float>(MAX_HP);
	if (hp_ < 0)
	{
		hp_ = 0;
	}
	//スタミナ割合更新
	staminaPercent_ = stamina_ / STAMINA_MAX;

	staminaConsumPercent_ = staminaConsum_ / STAMINA_MAX;
	//フレーム処理
	FrameUpdate();

	//アイテム処理
	ItemUpdate();

	//カウンタークールタイム減算
	GuardCoolTimeConsum();


	if (staminaConsum_ <= CHARGE_STAMINA_VAL && staminaConsum_ <= CHARGE_STAMINA_PER_FRAME)
	{
		staminaConsum_ = 0;
	}
	//スタミナ上限　
	if (stamina_ >= STAMINA_MAX)
	{
		stamina_ = STAMINA_MAX;
	}

}
//描画処理
void Player::Draw(void)
{
	SlimeBase::Draw();
	//DrawDebug();
	//デバッグ用の色変更

	//方向三角形
	DrawDirTriangle(pos_, dir_, SLIME_COLOR);

	if (state_ == CommonData::PLAYERSTATE::CHARGE)
	{
		VECTOR pos = VECTOR();
		VECTOR framePos = VECTOR();

		//プレイヤーの頭上のワールド座標
		pos = VAdd(pos_, LOCAL_GAUGE_POS);
		framePos = VAdd(pos_, LOCAL_GAUGE_POS);

		//ワールド座標をスクリーン座標に変換
		pos = ConvWorldPosToScreenPos(pos);
		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::CHARGE, pos, GAUGE_SIZE, GAUGE_SIZE, chargePer_, true);
	}

	//パリィクールタイムゲージの描画
	VECTOR parryPos;
	parryPos = ConvWorldPosToScreenPos(PARRY_POS);
	
	gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::PARRY_K, parryPos, guardCoolTimeGaugeSize_, guardCoolTimeGaugeSize_, guardCoolTimePercent_,false);
	
	//スタミナゲージ
	DrawBox(15, 50, 275, 75, 0x000000, true);
	DrawBox(274, 51, 274  - staminaPercent_ * 260, 74, 0x9d370e, true);
	DrawBox(274, 51, 274  - staminaConsumPercent_ * 260, 74, 0xED784A, true);
}
//解放処理
bool Player::Release(void)
{
	EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET, this);
	return true;
}

//プレイヤーの状態ゲッタ
CommonData::PLAYERSTATE Player::GetState(void)
{
	return state_;
}

/// <summary>
	/// デバッグ用関数
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
		, state_
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


//スタミナ初期化
void Player::FrameUpdate(void)
{
	if (stamina_ <= 0.0f)
	{
		frame_ = FRAME_DEFAULT;
		stamina_ = 0.0f;
		state_ = CommonData::PLAYERSTATE::ACTIONABLE;
		isStaminaRecov_ = true;
	}
}

//スタミナ回復処理
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

//溜め移動
void Player::ChargeStart(void)
{
	//ジャンプ中は溜められない
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

//移動処理
void Player::ProcessMove(void)
{
	//ジャンプ以外の処理
	if (isJump_)return;

	SunUtility::DIR_3D dir = SunUtility::DIR_3D::MAX;

	dir = dir_;

	//移動
	if (InputManager::GetInput().IsPadRelease(padNum_, PAD_INPUT_A))
	{
		frameNum_ = frame_;
		if (state_ == CommonData::PLAYERSTATE::CHARGE)
		{
			StopJoypadVibration(padNum_, -1);
			ChangeState(CommonData::PLAYERSTATE::NORMALATTACK);
		}
		else
		{
			ChangeState(CommonData::PLAYERSTATE::STEP);
		}

	}

}

//ノックバック処理
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
		ChangeState(CommonData::PLAYERSTATE::FALL);
	}
	if (knockBackCnt_ < 0)
	{
		ChangeState(CommonData::PLAYERSTATE::COOL);
	}
}

//ベースに引数（diffの値）を追加して作る
void Player::KnockBack(void)
{
	auto& ins = CommonData::GetData();
	VECTOR diff = {};
	if (ins.GetMode() == CommonData::MODE::PVE)
	{

		//座標でノックバックを判定する
		diff = VSub(pos_, sceneGame_->GetEnemyPos());	//相手から自分を引くと相手への方向を向く。
	}
	else if(ins.GetMode() == CommonData::MODE::PVP)
	{
		//座標でノックバックを判定する
		diff = VSub(pos_, sceneGame_->GetPlayer2Pos());	//相手から自分を引くと相手への方向を向く。
	}
	
	//ノックバックは自分とは逆だから（自分ー相手）
	auto dir = VNorm(diff);
	auto dir4 = SunUtility::ToDirection(dir);


	DirUpdate(dir4);

}



//チャージとステップを決める処理
void Player::MoveDecide(void)
{
	ChangeState(CommonData::PLAYERSTATE::STEPKEEP);
	if (stepFrame_ < 0)
	{
		ChangeState(CommonData::PLAYERSTATE::CHARGE);
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

#pragma region	状態の更新処理

void Player::CoolUpdate(void)
{
	coolTime_--;
	if (coolTime_ <= 0)
	{
		coolTime_ = 0;
		ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
	}

	if (!MoveLimit())
	{
		ChangeState(CommonData::PLAYERSTATE::FALL);
	}
}

//行動可能状態の時の処理
void Player::ActionableUpdate(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::IDLE);

	//回復処理
	StaminaRecovery();

	face_ = SLIME_FACE::NORMAL;
	if (staminaPercent_ <= STAMINA_TIRED)
	{
		face_ = SLIME_FACE::TIRED;
	}
	ChargeStart();
	auto& ins = InputManager::GetInput();
	//Eキーを押すとガード状態
	if (ins.IsPadKeep(padNum_, PAD_INPUT_6) && guardCoolTime_ == 0)
	{
		ChangeState(CommonData::PLAYERSTATE::GUARD);
	}

	if (!MoveLimit())
	{
		ChangeState(CommonData::PLAYERSTATE::FALL);
	}

	GetItemUpdate();

}

//ステップ受付状態
void Player::StepKeepUpdate(void)
{
	stepFrame_--;
	ProcessMove();
	if (stepFrame_ < 0)
	{
		ChangeState(CommonData::PLAYERSTATE::CHARGE);
	}
}


//回避処理
void Player::StepUpdate(void)
{
	//ステップ受付時間内にキーを離した時
	if (stepFrame_ >= 0)
	{
		model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::STEP);
		DirUpdate(dir_);
		
		//フレームを減らす
		frame_--;
		if (frame_ <= 0)
		{
			ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
		}
		//ステップ中スタミナを減らす
		stamina_--;
		
	}
	else
	{
		ChangeState(CommonData::PLAYERSTATE::CHARGE);
	}
}

//溜め
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

	//溜めキャンセル
	if (ins.IsPadKeep(padNum_,PAD_INPUT_5))
	{
		StopJoypadVibration(padNum_, -1);
		ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
	}

}

//攻撃
void Player::NormalAttackUpdate(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::ATTACK);
	DirUpdate(dir_);

	//フレームを減らす
	frame_--;
	stamina_ -= CHARGE_ATK_STAMINA;
	if (frame_ <= 0.0f||stamina_<=0.0f)
	{
		ChangeState(CommonData::PLAYERSTATE::CRITICALATTACK);
	}
}

void Player::CriticalUpdate(void)
{
	criticalCnt_--;
	if (criticalCnt_ <= 0&&pos_.y<=RADIUS)
	{
		ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
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
	//アイテムをとった時の処理(プレイヤーの攻撃状態が終わっても広範囲攻撃を動き続けるようにするため)
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
			ChangeState(CommonData::PLAYERSTATE::WAIDATTACK);
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
		Score(-fallScore_);
		ChangeState(CommonData::PLAYERSTATE::REVIVAL);
	}
}

void Player::RevivalUpdate(void)
{
	revivalCnt_--;
	SetPos(revivalPos_);
	if (revivalCnt_ <= 0)
	{
		SetInvincible(AFTER_REVIVAL_CNT);
		ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
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

		ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);

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
		//どのくらいの時間上に上がるか
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
			ChangeState(CommonData::PLAYERSTATE::ACTIONABLE);
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
	switch (state_)
	{
	case CommonData::PLAYERSTATE::COOL:
		CoolUpdate();
		break;
	case CommonData::PLAYERSTATE::DEBUFF:
		break;
	case CommonData::PLAYERSTATE::ACTIONABLE:
		ActionableUpdate();
		break;
	case CommonData::PLAYERSTATE::STEPKEEP:
		StepKeepUpdate();
		break;
	case CommonData::PLAYERSTATE::STEP:
		StepUpdate();
		break;
	case CommonData::PLAYERSTATE::CHARGE:
		ChargeUpdate();
		break;
	case CommonData::PLAYERSTATE::NORMALATTACK:
		NormalAttackUpdate();
		break;
	case CommonData::PLAYERSTATE::KNOCKBACK:
		KnockBuckUpdate();
		break;
	case CommonData::PLAYERSTATE::GUARD:
		GuardUpdate();
		break;
	case CommonData::PLAYERSTATE::WAIDATTACK:
		WaidAtkUpdate();
		break;
	case CommonData::PLAYERSTATE::CRITICALATTACK:
		CriticalUpdate();
		break;
	case CommonData::PLAYERSTATE::FALL:
		FallUpdate();
		break;
	case CommonData::PLAYERSTATE::REVIVAL:
		RevivalUpdate();
		break;

	}
}

//状態変化関数
void Player::ChangeState(CommonData::PLAYERSTATE state)
{
	state_=state;
	atkPow_ = 0;
	switch (state_)
	{
	case CommonData::PLAYERSTATE::ACTIONABLE:
		frame_ = FRAME_DEFAULT;
		atkPow_ = 0;
		break;
	case CommonData::PLAYERSTATE::STEPKEEP:
		stepFrame_ = STEP_FRAME_MAX;   
		break;
	case CommonData::PLAYERSTATE::STEP:
		model_->SetStepAnim(modelType_, 0.0f);
		stepAnim_ = 0.0f;
		staminaConsum_ -= STEP_STEMINA;
		sound_->PlaySe(SoundManager::SE_TYPE::SLIMEMOVE, DX_PLAYTYPE_BACK, SE_VOL);
		StaminaLowLimit(STEP_STEMINA);
		break;
	case CommonData::PLAYERSTATE::CHARGE:
		model_->SetStepAnim(modelType_, 0.0f);
		stepAnim_ = 0.0f;
		staminaConsum_ -= CHARGE_STAMINA_VAL;
		face_ = SLIME_FACE::CHARGE;
		break;
	case CommonData::PLAYERSTATE::NORMALATTACK:
		sound_->PlaySe(SoundManager::SE_TYPE::ATTACK, DX_PLAYTYPE_BACK, SE_VOL);
		atkPow_ = CHARGE_ATK_POW;
		model_->SetStepAnim(modelType_, 0.0f);
		stepAnim_ = 0.0f;
		face_ = SLIME_FACE::ATTACK;
		break;
	case CommonData::PLAYERSTATE::KNOCKBACK:
		face_ = SLIME_FACE::DAMAGE;
		StopJoypadVibration(padNum_);
		break;
	case CommonData::PLAYERSTATE::GUARD:
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::SHIELD, this, shieldPar_);
		atkPow_ = PARRY_ATK_POW;
		 guardCnt_ = GUARD_CNT_MAX;
		 face_ = SLIME_FACE::DAMAGE;
		break;
	case CommonData::PLAYERSTATE::WAIDATTACK:
		waidChargeCnt_ = 0;
		ChangeWaidAtkState(WAID_ATK::CHARGE);
		jumpCnt_ = 0;
		face_ = SLIME_FACE::ATTACK;
		break;
	case CommonData::PLAYERSTATE::CRITICALATTACK:
		criticalCnt_ = CRITICAL_CNT_MAX;
		break;
	case CommonData::PLAYERSTATE::FALL:
		fallCnt_ = FALL_CNT;
		
		EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::ITEMGET,this);
		if (item_ != nullptr)
		{
			isItemUse_ = false;
			isUseItem_ = false;
			item_ = nullptr;
		}
		break;
	case CommonData::PLAYERSTATE::REVIVAL:
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


