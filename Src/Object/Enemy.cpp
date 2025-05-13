#include<DxLib.h>
#include"../Utility/SunUtility.h"
#include"../Application.h"
#include"../Manager/InputManager.h"
#include"../Manager/EffectManager.h"
#include"../Manager/ModelManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"../Common/CommonData.h"
#include"../Scene/SceneGame.h"
#include"../Object/GaugeCircle.h"
#include"../Object/Stage.h"
#include"../Object/Speaker.h"
#include"../Object/SlimeBase.h"
#include"../Object/Player.h"
#include"../Object/Enemy.h"

void Enemy::SetParam(VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir)
{
#pragma region パラメタの初期化
	pos_ = _initPos;

	//modelFileName_ = "SilmeAnimYuuhi.mv1";
	modelType_ = _modelType;

	facePos_ = { ORANGE_SLIME_FACE_POS_X,ORANGE_SLIME_FACE_POS_Y };
	backSlimefacePos_ = facePos_;
	slimeFaceImgs_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + ORANGE_NORMAL_FACE).c_str());
	slimeFaceImgs_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + ORANGE_TIRED_FACE).c_str());
	slimeFaceImgs_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + ORANGE_DAMAGE_FACE).c_str());
	slimeFaceImgs_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + ORANGE_CHARGE_FACE).c_str());
	slimeFaceImgs_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + ORANGE_ATTACK_FACE).c_str());

	facePos_ = { Application::SCREEN_SIZE_X - 60 - 70,40 + 74 + 30 };
	backSlimefacePos_ = facePos_;

	revivalPos_ = _initPos;

	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };

	waidAtkPar_.pos = { 0.0f,0.0f,0.0f };
	waidAtkPar_.rot = { 0.0f,0.0f,0.0f };
	waidAtkPar_.scl = { 0.0f,0.0f,0.0f };


	waidChargePar_.pos = SunUtility::VECTOR_ZERO;
	waidChargePar_.rot = SunUtility::VECTOR_ZERO;
	waidChargePar_.scl = { WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL };;

	//speedAnim_ = ANIM_SPEED_DEFAULT;

	//ジャンプ力
	jumpPower_ = 0.0f;

	//ジャンプ判定
	isJump_ = false;

	//スタミナ
	stamina_ = STAMINA_MAX;

	//スタミナ回復状態
	isStaminaRecov_ = false;

	//状態
	state_ = SlimeBase::ENEMYSTATE::NONE;

	//フレームカウント
	frame_ = FRAME_DEFAULT;

	//Move状態判定
	isMove_ = false;

	//クールタイム
	coolTime_ = 80;

	//動く方向初期化
	moveDir_ = SunUtility::DIR_3D::MAX;

	//方向
	dir_ = _dir;

	//HP
	hp_ = MAX_HP;

	//広範囲攻撃クールタイム
	waidAtkCoolTime_ = WAID_ATK_COOLTIME_MAX;

	hpPercent_ = SunUtility::PERCENT_MAX_F;

	gravityPow_ = DEFAULT_GRAVITY;

	moveRoute_ = VSub(pos_, SunUtility::VECTOR_ZERO);
	fallDmg_ = FALL_DMG_DEFAULT;

	fallScore_ = FALL_SCORE_DEFAULT;
#pragma endregion


}

//更新処理
void Enemy::Update(void)
{
	SlimeBase::Update();

	stamina_ = STAMINA_MAX;
	waidAtkCoolTime_--;

	hpPercent_ = static_cast<float>(hp_ ) / static_cast<float>(MAX_HP);

	
	//重力をかける
	if (state_ != SlimeBase::ENEMYSTATE::REVIVAL)
	{
		AddGravity(gravityPow_);
	}
	

	//スタミナ回復処理
	StaminaRecovery();

	
	switch (dir_)
	{
	case SunUtility::DIR_3D::FLONT:
		moveRoute_.z = pos_.z + frame_ * SPEED;
		break;
	case SunUtility::DIR_3D::BACK:
		moveRoute_.z = pos_.z - (frame_ * SPEED);
		break;
	case SunUtility::DIR_3D::RIGHT:
		moveRoute_.x = pos_.x + (frame_ * SPEED);
		break;
	case SunUtility::DIR_3D::LEFT:
		moveRoute_.x = pos_.x - (frame_ * SPEED);
		break;
	}


	
}

//描画処理
void Enemy::Draw(void)
{
	SlimeBase::Draw();
	DrawDirTriangle(pos_, dir_, ORANGE_SLIME_COLOR);


	if (state_ == SlimeBase::ENEMYSTATE::CHARGE)
	{
		VECTOR pos = VECTOR();

		//プレイヤーの頭上のワールド座標
		pos = VAdd(pos_, LOCAL_GAUGE_POS);

		//ワールド座標をスクリーン座標に変換
		pos = ConvWorldPosToScreenPos(pos);
		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::CHARGE, pos, GAUGE_SIZE, GAUGE_SIZE, chargePer_,true);
	}

	//DrawDebug();
	//if (pState_ == SlimeBase::ENEMYSTATE::CHARGE)
	//{
	//	DrawLine3D(pos_, { pos_.x + frame_,pos_.y,pos_.z },0x000000);
	//}
}

//解放処理
bool Enemy::Release(void)
{
	return true;
}

//デバッグ関数
void Enemy::DrawDebug(void)
{
	//VECTOR playerPos = slimeMng_->GetPlayerPos();
	//VECTOR enemyPos = pos_;
	//VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

	//
	//



	//if (waidAtk_ == SlimeBase::WAID_ATK::ATK)
	//{

	//	VECTOR colPos = { pos_.x,pos_.y - RADIUS,pos_.z };
	//	DrawSphere3D(colPos, waidAtkRadius_, 16, 0x00ff00, 0xffffff, false);
	//}
	//

	//DrawFormatString(0, 130, 0x000000
	//	, "EnemyPos(%.1f,%.1f,%.1f)\nFrame(%.1f)\nStamina(%.8f)\nState(%d)\nposE2P(%.2f,%.2f,%.2f)\nACT(%d)\nMoveRoute(%.2f,%.2f,%.2f)"
	//	, pos_.x, pos_.y, pos_.z
	//	, frame_
	//	, stamina_
	//	, pState_
	//	, posE2P.x, posE2P.y, posE2P.z
	//	,act_
	//	,moveRoute_.x,moveRoute_.y,moveRoute_.z
	//);
	////DrawFormatString(0, 216, 0x000000, "KnockBack(%d)\nHP(%d)"
	////	, knockBackCnt_
	////	,hp_);
	//

	//


	//if (pState_ == SlimeBase::ENEMYSTATE::CHARGE)
	//{
	//	DrawString(pos_.x, pos_.y - RADIUS, "Charge!!!!", 0xff0000);
	//}
}

//フレームとスタミナ減算処理
void Enemy::FrameComsumption(void)
{
	frame_--;
	stamina_--;
	isStaminaRecov_ = false;
	if (frame_ >= 0.0f)return;

	frame_ = FRAME_DEFAULT;
	isStaminaRecov_ = true;
	if (!isJump_)
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NONE);
	}


}

//DIRを考える処理
void Enemy::MoveDir(void)
{
	VECTOR playerPos = sceneGame_->GetPlayerPos(SceneGame::PLAYER);
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };


	if (posE2P.x >= MOVE_POS_E2P)
	{
		moveDir_ = SunUtility::DIR_3D::RIGHT;
		
	}
	else if (posE2P.z >= MOVE_POS_E2P)
	{
		moveDir_ = SunUtility::DIR_3D::FLONT;
	}
	else if (posE2P.x <= -MOVE_POS_E2P)
	{
		moveDir_ = SunUtility::DIR_3D::LEFT;
		
	}
	else if (posE2P.z <= -MOVE_POS_E2P)
	{
		moveDir_ = SunUtility::DIR_3D::BACK;
	}
	
	
	switch (moveDir_)
	{
	case SunUtility::DIR_3D::FLONT:
		pos_.z += MOVE_SPEED;
		break;
	case SunUtility::DIR_3D::BACK:
		pos_.z -= MOVE_SPEED;
		break;
	case SunUtility::DIR_3D::LEFT:
		pos_.x -= MOVE_SPEED;
		break;
	case SunUtility::DIR_3D::RIGHT:
		pos_.x += MOVE_SPEED;
		break;
	}
	dir_ = moveDir_;

}

void Enemy::StateUpdate(void)
{
	if (stamina_ <= 0.0f)return;

	switch (state_)
	{
	case SlimeBase::ENEMYSTATE::NONE:
		UpdateNone();
		break;
	case SlimeBase::ENEMYSTATE::DEBUFF:
		DebuffUpdate();
		break;
	case SlimeBase::ENEMYSTATE::THINK:
		UpdateThink();
		break;
	case SlimeBase::ENEMYSTATE::MOVE:
		UpdateMove();
		break;
	case SlimeBase::ENEMYSTATE::STEP:
		UpdateStep();
		break;
	case SlimeBase::ENEMYSTATE::CHARGE:
		UpdateCharge();
		break;
	case SlimeBase::ENEMYSTATE::KNOCKBACK:
		UpdateKnockBuck();
		break;
	case SlimeBase::ENEMYSTATE::NORMALATTACK:
		UpdateNormalAttack();
		break;
	case SlimeBase::ENEMYSTATE::WAIDATTACK:
		UpdateWaidAttack();
		break;
	case SlimeBase::ENEMYSTATE::CRITICALATTACK:
		break;
	case SlimeBase::ENEMYSTATE::FALL:
		FallUpdate();
		break;
	case SlimeBase::ENEMYSTATE::REVIVAL:
		RevivalUpdate();
		break;
	}

}

//スタミナ回復処理
void Enemy::StaminaRecovery(void)
{
	if (state_ == SlimeBase::ENEMYSTATE::THINK||state_==SlimeBase::ENEMYSTATE::NONE)
	{
		if (isStaminaRecov_ && stamina_ < STAMINA_MAX)
		{
			//スタミナを0.25のスピードで回復
			staminaRecov_ += STAMINA_RECOVE_SPEED;

			//回復量が1になったら回復
			if (staminaRecov_ == STAMINA_RECOV_MAX)
			{
				stamina_ += staminaRecov_;
				staminaRecov_ = 0;
			}
		}
	}
}
//状態ゲッタ
SlimeBase::ENEMYSTATE Enemy::GetState(void)
{
	return state_;
}

void Enemy::SetEnemyState(const SlimeBase::ENEMYSTATE enemyState)
{
	state_ = enemyState;
}

float Enemy::GetWaidCol(void) const
{
	return waidAtkRadius_;
}

void Enemy::ChangeEnemyState(SlimeBase::ENEMYSTATE state)
{
	state_ = state;

	// 状態変化時の初期処理
	switch (state_)
	{
	case SlimeBase::ENEMYSTATE::NONE:
		gravityPow_ = DEFAULT_GRAVITY;
		break;
	case SlimeBase::ENEMYSTATE::THINK:
		isWeak_ = false;
		frame_ = FRAME_DEFAULT;
		face_ = SLIME_FACE::NORMAL;
		break;
	case SlimeBase::ENEMYSTATE::MOVE:
		break;
	case SlimeBase::ENEMYSTATE::STEP:
		model_->SetStepAnim(modelType_, 0.0f);
		sound_->PlaySe(SoundManager::SE_TYPE::SLIMEMOVE, DX_PLAYTYPE_BACK,SE_VOL);
		break;
	case SlimeBase::ENEMYSTATE::CHARGE:
		face_ = SLIME_FACE::CHARGE;
		break;
	case SlimeBase::ENEMYSTATE::KNOCKBACK:
		face_ = SLIME_FACE::DAMAGE;
		break;
	case SlimeBase::ENEMYSTATE::NORMALATTACK:
		sound_->PlaySe(SoundManager::SE_TYPE::ATTACK, DX_PLAYTYPE_BACK, SE_VOL);
		model_->SetStepAnim(modelType_, 0.0f);
		face_ = SLIME_FACE::ATTACK;
		break;
	case SlimeBase::ENEMYSTATE::WAIDATTACK:
		waidAtk_ = SlimeBase::WAID_ATK::CHARGE;
		waidChargeCnt_ = 0;
		jumpCnt_ = 0;
		face_ = SLIME_FACE::ATTACK;
		ChangeWaidAtkState(SlimeBase::WAID_ATK::CHARGE);
		break;
	case SlimeBase::ENEMYSTATE::CRITICALATTACK:
		break;
	case SlimeBase::ENEMYSTATE::FALL:
		fallCnt_ = FALL_CNT;
		break;
	case SlimeBase::ENEMYSTATE::REVIVAL:
		SetInvincible(REVIVAL_CNT_MAX);
		fallDmg_ += FALL_DMG_INCREASE;
		fallScore_ += FALL_SCORE_INCREASE;
		revivalCnt_ = REVIVAL_CNT_MAX;
		isWeak_ = false;
		break;
	}

}

#pragma region 状態ごとの処理
void Enemy::UpdateNone(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::IDLE);

	coolTime_--;
	isStaminaRecov_ = true;
	if (coolTime_ < 0)
	{
		isWeak_ = false;
		ChangeEnemyState(SlimeBase::ENEMYSTATE::THINK);
	}

	if (!MoveLimit())
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::FALL);
	}
}
void Enemy::DebuffUpdate(void)
{
	coolTime_--;
	isStaminaRecov_ = true;
	if (coolTime_ < 0)
	{
		isWeak_ = false;
		ChangeEnemyState(SlimeBase::ENEMYSTATE::THINK);
	}
}

void Enemy::UpdateThink(void)
{
	if (isJump_)return;
	VECTOR playerPos = sceneGame_->GetPlayerPos(SceneGame::PLAYER);
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

	if (waidAtkCoolTime_ < 0)
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::WAIDATTACK);
	}

	else if (posE2P.x >= -CHARGE_MARGIN_X && posE2P.x <= CHARGE_MARGIN_X 
		&& posE2P.z >= -CHARGE_MARGIN_Z && posE2P.z <= CHARGE_MARGIN_Z
		&& act_ == ACT::Attack && MoveLimit())
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::CHARGE);
	}

	else if ((pos_.x <= -CHARGE_MARGIN_X) || (pos_.x >= CHARGE_MARGIN_X)
		|| (pos_.z <= -CHARGE_MARGIN_Z) || (pos_.z >= CHARGE_MARGIN_Z))
	{
		act_ = ACT::ESCAPE;
		ChangeEnemyState(SlimeBase::ENEMYSTATE::STEP);
	}
	else if ((pos_.x > -CHARGE_MARGIN_X) || (pos_.x > CHARGE_MARGIN_X)
		|| (pos_.z > -CHARGE_MARGIN_Z) || (pos_.z > CHARGE_MARGIN_Z))
	{
		act_ = ACT::Attack;
		ChangeEnemyState(SlimeBase::ENEMYSTATE::STEP);
	}
	if (!MoveLimit())
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::FALL);
	}

}

void Enemy::UpdateMove(void)
{
	MoveDir();
	ChangeEnemyState(SlimeBase::ENEMYSTATE::THINK);
}

void Enemy::UpdateStep(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::STEP);


	VECTOR playerPos = sceneGame_->GetPlayerPos(SceneGame::PLAYER);
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

	VECTOR marginPos;
	marginPos.x = ESCAPE_MARGIN_X;
	marginPos.y = 0;
	marginPos.z = ESCAPE_MARGIN_Z;

	VECTOR diff;
	VECTOR dir;
	SunUtility::DIR_3D dir4;

	SunUtility::DIR_3D playerDir = sceneGame_->GetPlayerDir();
	if (isJump_)return;
	switch (act_)
	{
	case Enemy::ACT::Attack:
	{
		//座標でノックバックを判定する
		diff = VSub(sceneGame_->GetPlayerPos(SceneGame::PLAYER), pos_);	//相手から自分を引くと相手への方向を向く。
		//敵に向かって進む（相手-自分）
		dir = VNorm(diff);
		//無限にある方向を４方向に限定する
		dir4 = SunUtility::ToDirection(dir);
		dir_ = dir4;
	}
	break;
	case Enemy::ACT::ESCAPE:
	{
		//座標で方向を指定する
		diff = VSub(SunUtility::VECTOR_ZERO, pos_);	//相手から自分を引くと相手への方向を向く。
		//敵に向かって進む（相手-自分）
		dir = VNorm(diff);
		//無限にある方向を４方向に限定する
		dir4 = SunUtility::ToDirection(dir);
		dir_ = dir4;
	}
	break;
	}


	//スタミナが0以上だったら移動させる
	if (stamina_ >= 0)
	{
		DirUpdate(dir_);
		FrameComsumption();
	}

	//移動フレームが０以下人あったら移動クールタイムへ
	if (frame_ <= 0)
	{
		SetCoolTime(static_cast<int>(SunUtility::DEFAULT_FPS * MOVE_END_COOL_TIME_SEC));
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NONE);
	}

}

void Enemy::UpdateCharge(void)
{
	if (isJump_)return;
	VECTOR playerPos = sceneGame_->GetPlayerPos(SceneGame::PLAYER);
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };
	
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::CHARGE);
	moveDir_ = SunUtility::DIR_3D::MAX;


	//大きさをとる
	float size = sqrtf(posE2P.x * posE2P.x + posE2P.z * posE2P.z);
	VECTOR direction({ posE2P.x / size, RADIUS, posE2P.z / size });
	if (abs(direction.x) < abs(direction.z))
	{

		if (direction.z > 0.0f)
		{
			dir_ = SunUtility::DIR_3D::FLONT;
		}
		else
		{
			dir_ = SunUtility::DIR_3D::BACK;
		}
	}
	else
	{
		if (direction.x < 0.0f)
		{
			dir_ = SunUtility::DIR_3D::LEFT;
		}
		else
		{
			dir_ = SunUtility::DIR_3D::RIGHT;
		}
	}

	frame_ += SlimeBase::CHARGE_SPEED;
	chargePer_ = frame_ / FRAME_MAX;


	//プレイヤーのサイズ内にルート座標が入ったら攻撃する
	if (((moveRoute_.x <= playerPos.x + RADIUS) && (moveRoute_.x >= playerPos.x - RADIUS)
		|| (moveRoute_.z <= playerPos.z + RADIUS) && (moveRoute_.z >= playerPos.z - RADIUS)) || (frame_ >= FRAME_MAX))
	{
		if (isJump_)return;
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NORMALATTACK);

	}
}

void Enemy::UpdateKnockBuck(void)
{
	knockBackCnt_--;
	KnockBack();
	if (knockBackCnt_ < 0&&!isWeak_)
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NONE);
	}
	else if (knockBackCnt_ < 0 && isWeak_)
	{
		ChangeEnemyState(SlimeBase::ENEMYSTATE::DEBUFF);
	}
}



void Enemy::KnockBack(void)
{

	//座標でノックバックを判定する
	auto diff = VSub(pos_, sceneGame_->GetPlayerPos(SceneGame::PLAYER));	//相手から自分を引くと相手への方向を向く。
	//ノックバックは自分とは逆だから（自分ー相手）
	auto dir = VNorm(diff);
	//無限にある方向を４方向に限定する
	auto dir4 = SunUtility::ToDirection(dir);
	DirUpdate(dir4);
}

void Enemy::UpdateNormalAttack(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::ATTACK);

	if (stamina_ >= 0)
	{
		DirUpdate(dir_);
		FrameComsumption();
	}


	if (frame_ <= 0)
	{
		SetCoolTime(SunUtility::DEFAULT_FPS * 2);
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NONE);

	}
	else
	{
		if (stamina_ > 0.0f)return;

		isStaminaRecov_ = true;
		SetCoolTime(STAMINA_RECOV_TIME);
		ChangeEnemyState(SlimeBase::ENEMYSTATE::NONE);
	}
}

void Enemy::UpdateWaidAttack(void)
{
	waidChargeCnt_++;
	switch (waidAtk_)
	{
	case SlimeBase::WAID_ATK::CHARGE:
		waidChargePar_.pos = pos_;
		waidChargePar_.pos.y -= RADIUS;
		EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::WAIDCHARGE, this, waidChargePar_);
		if (waidChargeCnt_ > WAID_CHARGE_MAX)
		{
			waidChargeCnt_ = WAID_CHARGE_MAX;
			ChangeWaidAtkState(SlimeBase::WAID_ATK::JUMP);
		}
		break;
	case SlimeBase::WAID_ATK::JUMP:
		jumpCnt_++;
		SetJumpPower(WIDE_JUMP_POWER);
		Jump();
		if (jumpCnt_ > WAID_JUMPCNT_MAX)
		{
			jumpCnt_ = WAID_JUMPCNT_MAX;
			ChangeWaidAtkState(SlimeBase::WAID_ATK::JUMPEND);
		}
		break;
	case SlimeBase::WAID_ATK::JUMPEND:
		if (pos_.y <= RADIUS)
		{
			ChangeWaidAtkState(SlimeBase::WAID_ATK::ATK);
		}
		break;
	case SlimeBase::WAID_ATK::ATK:
	{
		auto camera = SceneManager::GetInstance().GetCamera();
		camera = SceneManager::GetInstance().GetCamera();
		camera->CameraShake(static_cast<int>(SHAKE_CNT), static_cast<int>(SHAKE_LIMIT));
	}
	waidAtkRadius_ += WAID_COL_EXPAND_SPEED;
	waidAtkPar_.pos = pos_;
	waidAtkPar_.scl = { waidAtkRadius_ * WAID_ATK_COLMARGIN,waidAtkRadius_ * WAID_ATK_COLMARGIN,waidAtkRadius_ * WAID_ATK_COLMARGIN };
	EffectManager::GetEffect().SyncEffect(EffectManager::EFF_TYPE::WAIDATK, this, waidAtkPar_);
		if (waidAtkRadius_ > Speaker::WAID_ATK_COL)
		{
			EffectManager::GetEffect().StopEffect(EffectManager::EFF_TYPE::WAIDATK, this);
			ChangeWaidAtkState(SlimeBase::WAID_ATK::END);
		}
	break;
	case SlimeBase::WAID_ATK::END:
		if (pos_.y <= RADIUS)
		{
			ChangeEnemyState(SlimeBase::ENEMYSTATE::THINK);
		}
		break;
	}
}
void Enemy::FallUpdate(void)
{
	fallCnt_--;

	if (fallCnt_ > 0)return;
	Damage(fallDmg_, 0);
	AddScore(-fallScore_);
	ChangeEnemyState(SlimeBase::ENEMYSTATE::REVIVAL);

}
void Enemy::RevivalUpdate(void)
{
	revivalCnt_--;
	SetPos(revivalPos_);
	if (revivalCnt_ > 0)return;
	ChangeEnemyState(SlimeBase::ENEMYSTATE::THINK);
	

}
void Enemy::ChangeWaidAtkState(const SlimeBase::WAID_ATK waidAtk)
{
	waidAtk_ = waidAtk;
	const int VOL = 60;
	switch (waidAtk_)
	{
	case SlimeBase::WAID_ATK::CHARGE:
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATKCHARGE, DX_PLAYTYPE_BACK, VOL);
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDCHARGE, this, waidChargePar_);
		break;
	case SlimeBase::WAID_ATK::JUMP:
		break;
	case SlimeBase::WAID_ATK::JUMPEND:
		gravityPow_ = WAID_ATK_FALL_GRAVITY;
		break;
	case SlimeBase::WAID_ATK::ATK:
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDATK, this, waidAtkPar_);
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATK, DX_PLAYTYPE_BACK, VOL);
		waidAtkRadius_ = 0;
		waidAtkPar_.scl = { 0.0f,0.0f,0.0f };
		break;
	case SlimeBase::WAID_ATK::END:
		waidAtkCoolTime_ = WAID_ATK_COOLTIME_MAX;
		break;
	default:
		break;
	}
}
#pragma endregion