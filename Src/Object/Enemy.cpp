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

void Enemy::SetParam(void)
{
#pragma region パラメタの初期化
	pos_ = { Stage::STAGE_ONE_SQUARE * 3,RADIUS,0.0f };

	//modelFileName_ = "SilmeAnimYuuhi.mv1";
	modelType_ = ModelManager::MODEL_TYPE::YUUHI;

	//スライム状態画像のロード
	slimeFaceImg_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + "NormalY.png").c_str());
	slimeFaceImg_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + "TukareY.png").c_str());
	slimeFaceImg_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + "DamageY.png").c_str());
	slimeFaceImg_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + "ChargeY.png").c_str());
	slimeFaceImg_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + "AttackY.png").c_str());

	facePos_ = { Application::SCREEN_SIZE_X - 60 - 70,40 + 74 + 30 };
	backSlimefacePos_ = facePos_;

	revivalPos_ = { Stage::STAGE_ONE_SQUARE * 3,RADIUS * 5,0.0f };

	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };

	waidAtkPar_.pos = { 0.0f,0.0f,0.0f };
	waidAtkPar_.rot = { 0.0f,0.0f,0.0f };
	waidAtkPar_.scl = { 0.0f,0.0f,0.0f };


	waidChargePar_.pos = SunUtility::VECTOR_ZERO;
	waidChargePar_.rot = SunUtility::VECTOR_ZERO;
	waidChargePar_.scl = { WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL };;

	speedAnim_ = ANIM_SPEED_DEFAULT;


	//移動速度
	speed_ = 15.0f;

	//距離
	distance_ = 12.0f;

	//ジャンプ力
	jumpPower_ = 0.0f;

	//ジャンプ判定
	isJump_ = false;

	//スタミナ
	stamina_ = STAMINA_MAX;

	//スタミナ回復状態
	isStaminaRecov_ = false;

	//状態
	state_ = CommonData::ENEMYSTATE::NONE;

	//フレームカウント
	frame_ = FRAME_DEFAULT;

	//Move状態判定
	isMove_ = false;

	//クールタイム
	coolTime_ = 80;

	//動く方向初期化
	moveDir_ = SunUtility::DIR_3D::MAX;

	dir_ = SunUtility::DIR_3D::LEFT;

	//HP
	hp_ = MAX_HP;

	//広範囲攻撃クールタイム
	waidAtkCoolTime_ = WAID_ATK_COOLTIME_MAX;

	hpPercent_ = SunUtility::PERCENT_MAX_F;

	gravityPow_ = DEFAULT_GRAVITY;

	slimeNum_ = 1;

	moveRoute_ = VSub(pos_, {0.0f, 0.0f, 0.0f });
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
	if (state_ != CommonData::ENEMYSTATE::REVIVAL)
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

	VECTOR attackPos;
	VECTOR attackPos2;
	VECTOR attackPos3;
	switch (dir_)
	{
	case SunUtility::DIR_3D::FLONT:
		attackPos = { pos_.x - RADIUS,12.5f,pos_.z };
		attackPos2 = { pos_.x + RADIUS,12.5f,pos_.z };
		attackPos3 = { pos_.x,12.5f,moveRoute_.z };
		//3Dの三角形は裏表があるから時計回りに指定する（2番目に移動先の座標を定める）
		DrawTriangle3D(attackPos, attackPos3, attackPos2, 0xED784A, true);
		break;
	case SunUtility::DIR_3D::BACK:
		attackPos = { pos_.x - RADIUS,12.5f,pos_.z };
		attackPos2 = { pos_.x + RADIUS,12.5f,pos_.z };
		attackPos3 = { pos_.x,12.5f,moveRoute_.z };
		DrawTriangle3D(attackPos2, attackPos3, attackPos, 0xED784A, true);
		break;
	case SunUtility::DIR_3D::RIGHT:
		attackPos = { pos_.x,12.5f,pos_.z - RADIUS };
		attackPos2 = { pos_.x,12.5f,pos_.z + RADIUS };
		attackPos3 = { moveRoute_.x,12.5f,pos_.z };
		DrawTriangle3D(attackPos2, attackPos3, attackPos, 0xED784A, true);
		break;
	case SunUtility::DIR_3D::LEFT:
		attackPos = { pos_.x,12.5f,pos_.z - RADIUS };
		attackPos2 = { pos_.x,12.5f,pos_.z + RADIUS };
		attackPos3 = { moveRoute_.x,12.5f,pos_.z };
		DrawTriangle3D(attackPos, attackPos3, attackPos2, 0xED784A, true);
		break;
	}



	if (state_ == CommonData::ENEMYSTATE::CHARGE)
	{
		VECTOR pos = VECTOR();

		//プレイヤーの頭上のワールド座標
		pos = VAdd(pos_, { 0.0f,0.0f,50.0f });

		//ワールド座標をスクリーン座標に変換
		pos = ConvWorldPosToScreenPos(pos);
		gaugeCircle_->Draw(GaugeCircle::GAUGE_TYPE::CHARGE, pos, 46, 46, chargePer_,true);
	}

	//DrawDebug();
	//if (state_ == CommonData::ENEMYSTATE::CHARGE)
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
	VECTOR playerPos = sceneGame_->GetPlayerPos();
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

	
	



	if (waidAtk_ == SlimeBase::WAID_ATK::ATK)
	{

		VECTOR colPos = { pos_.x,pos_.y - RADIUS,pos_.z };
		DrawSphere3D(colPos, waidAtkRadius_, 16, 0x00ff00, 0xffffff, false);
	}
	

	DrawFormatString(0, 130, 0x000000
		, "EnemyPos(%.1f,%.1f,%.1f)\nFrame(%.1f)\nStamina(%.8f)\nState(%d)\nposE2P(%.2f,%.2f,%.2f)\nACT(%d)\nMoveRoute(%.2f,%.2f,%.2f)"
		, pos_.x, pos_.y, pos_.z
		, frame_
		, stamina_
		, state_
		, posE2P.x, posE2P.y, posE2P.z
		,act_
		,moveRoute_.x,moveRoute_.y,moveRoute_.z
	);
	//DrawFormatString(0, 216, 0x000000, "KnockBack(%d)\nHP(%d)"
	//	, knockBackCnt_
	//	,hp_);
	

	


	if (state_ == CommonData::ENEMYSTATE::CHARGE)
	{
		DrawString(pos_.x, pos_.y - RADIUS, "Charge!!!!", 0xff0000);
	}
}

//フレームとスタミナ減算処理
void Enemy::FrameComsumption(void)
{
	frame_--;
	stamina_--;
	isStaminaRecov_ = false;
	if (frame_ < 0.0f)
	{
		frame_ = FRAME_DEFAULT;
		isStaminaRecov_ = true;
		if (!isJump_)
		{
			ChangeState(CommonData::ENEMYSTATE::NONE);
		}
		
	}
}

//DIRを考える処理
void Enemy::MoveDir(void)
{
	VECTOR playerPos = sceneGame_->GetPlayerPos();
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
	if (stamina_ > 0.0f)
	{
		switch (state_)
		{
		case CommonData::ENEMYSTATE::NONE:
			UpdateNone();
			break;
		case CommonData::ENEMYSTATE::DEBUFF:
			DebuffUpdate();
			break;
		case CommonData::ENEMYSTATE::THINK:
			UpdateThink();
			break;
		case CommonData::ENEMYSTATE::MOVE:
			UpdateMove();
			break;
		case CommonData::ENEMYSTATE::STEP:
			UpdateStep();
			break;
		case CommonData::ENEMYSTATE::CHARGE:
			UpdateCharge();
			break;
		case CommonData::ENEMYSTATE::KNOCKBACK:
			UpdateKnockBuck();
			break;
		case CommonData::ENEMYSTATE::NORMALATTACK:
			UpdateNormalAttack();
			break;
		case CommonData::ENEMYSTATE::WAIDATTACK:
			UpdateWaidAttack();
			break;
		case CommonData::ENEMYSTATE::CRITICALATTACK:
			break;
		case CommonData::ENEMYSTATE::FALL:
			FallUpdate();
			break;
		case CommonData::ENEMYSTATE::REVIVAL:
			RevivalUpdate();
			break;
		}
	}
}

//スタミナ回復処理
void Enemy::StaminaRecovery(void)
{
	if (state_ == CommonData::ENEMYSTATE::THINK||state_==CommonData::ENEMYSTATE::NONE)
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
CommonData::ENEMYSTATE Enemy::GetState(void)
{
	return state_;
}

void Enemy::SetEnemyState(const CommonData::ENEMYSTATE enemyState)
{
	state_ = enemyState;
}





float Enemy::GetWaidCol(void) const
{
	return waidAtkRadius_;
}




void Enemy::ChangeState(CommonData::ENEMYSTATE state)
{
	state_ = state;

	// 状態変化時の初期処理
	switch (state_)
	{
	case CommonData::ENEMYSTATE::NONE:
		gravityPow_ = DEFAULT_GRAVITY;
		break;
	case CommonData::ENEMYSTATE::THINK:
		isWeak_ = false;
		frame_ = FRAME_DEFAULT;
		face_ = SLIME_FACE::NORMAL;
		break;
	case CommonData::ENEMYSTATE::MOVE:
		break;
	case CommonData::ENEMYSTATE::STEP:
		model_->SetStepAnim(modelType_, 0.0f);
		sound_->PlaySe(SoundManager::SE_TYPE::SLIMEMOVE, DX_PLAYTYPE_BACK,SE_VOL);
		break;
	case CommonData::ENEMYSTATE::CHARGE:
		face_ = SLIME_FACE::CHARGE;
		break;
	case CommonData::ENEMYSTATE::KNOCKBACK:
		face_ = SLIME_FACE::DAMAGE;
		break;
	case CommonData::ENEMYSTATE::NORMALATTACK:
		sound_->PlaySe(SoundManager::SE_TYPE::ATTACK, DX_PLAYTYPE_BACK, SE_VOL);
		model_->SetStepAnim(modelType_, 0.0f);
		face_ = SLIME_FACE::ATTACK;
		break;
	case CommonData::ENEMYSTATE::WAIDATTACK:
		waidAtk_ = SlimeBase::WAID_ATK::CHARGE;
		waidChargeCnt_ = 0;
		jumpCnt_ = 0;
		face_ = SLIME_FACE::ATTACK;
		ChangeWaidAtkState(SlimeBase::WAID_ATK::CHARGE);
		break;
	case CommonData::ENEMYSTATE::CRITICALATTACK:
		break;
	case CommonData::ENEMYSTATE::FALL:
		fallCnt_ = FALL_CNT;
		break;
	case CommonData::ENEMYSTATE::REVIVAL:
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
		ChangeState(CommonData::ENEMYSTATE::THINK);
	}

	if (!MoveLimit())
	{
		ChangeState(CommonData::ENEMYSTATE::FALL);
	}
}
void Enemy::DebuffUpdate(void)
{
	coolTime_--;
	isStaminaRecov_ = true;
	if (coolTime_ < 0)
	{
		isWeak_ = false;
		ChangeState(CommonData::ENEMYSTATE::THINK);
	}
}

void Enemy::UpdateThink(void)
{
	if (!isJump_)
	{
		VECTOR playerPos = sceneGame_->GetPlayerPos();
		VECTOR enemyPos = pos_;
		VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

		VECTOR marginPos;
		marginPos.x = 180;
		marginPos.y = 0;
		marginPos.z = 180;
		if (waidAtkCoolTime_ < 0)
		{
			ChangeState(CommonData::ENEMYSTATE::WAIDATTACK);
		}

		//マジックナンバーを定数に直す
		else if (posE2P.x >= -180.0f && posE2P.x <= 180.0f && posE2P.z >= -180.0f && posE2P.z <= 180.0f
			&& act_ == ACT::Attack && MoveLimit())
		{
			ChangeState(CommonData::ENEMYSTATE::CHARGE);
		}

		else if ((pos_.x <= -marginPos.x) || (pos_.x >= marginPos.x)
			|| (pos_.z <= -marginPos.z) || (pos_.z >= marginPos.z))
		{
			act_ = ACT::ESCAPE;
			ChangeState(CommonData::ENEMYSTATE::STEP);
		}
		else if ((pos_.x > -marginPos.x) || (pos_.x > marginPos.x)
			|| (pos_.z > -marginPos.z) || (pos_.z > marginPos.z))
		{
			act_ = ACT::Attack;
			ChangeState(CommonData::ENEMYSTATE::STEP);
		}




		
	}
	if (!MoveLimit())
	{
		ChangeState(CommonData::ENEMYSTATE::FALL);
	}
	
}

void Enemy::UpdateMove(void)
{
	MoveDir();
	ChangeState(CommonData::ENEMYSTATE::THINK);
}

void Enemy::UpdateStep(void)
{
	model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::STEP);


	VECTOR playerPos = sceneGame_->GetPlayerPos();
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };

	VECTOR marginPos;
	marginPos.x = 210;
	marginPos.y = 0;
	marginPos.z = 210;

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
		diff = VSub(sceneGame_->GetPlayerPos(), pos_);	//相手から自分を引くと相手への方向を向く。
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



	if (stamina_ >= 0)
	{
		DirUpdate(dir_);
		FrameComsumption();
	}


	if (frame_ <= 0)
	{
		SetCoolTime(SunUtility::DEFAULT_FPS * 0.5);
		ChangeState(CommonData::ENEMYSTATE::NONE);

	}

}

void Enemy::UpdateCharge(void)
{
	VECTOR playerPos = sceneGame_->GetPlayerPos();
	VECTOR enemyPos = pos_;
	VECTOR posE2P = { playerPos.x - enemyPos.x,RADIUS,playerPos.z - enemyPos.z };
	if (!isJump_)
	{
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


		if (chargePer_ >= 0.9999999)
		{
			chargePer_ = 100.0f;
		}
		
	}
	
	//プレイヤーのサイズ内にルート座標が入ったら攻撃する
	if (((moveRoute_.x<= playerPos.x+RADIUS)&&(moveRoute_.x >= playerPos.x - RADIUS)
		||(moveRoute_.z <= playerPos.z+RADIUS)&&(moveRoute_.z >= playerPos.z - RADIUS))||(frame_ >= FRAME_MAX))
	{
		if (!isJump_)
		{
			ChangeState(CommonData::ENEMYSTATE::NORMALATTACK);
		}
	}
}

void Enemy::UpdateKnockBuck(void)
{
	knockBackCnt_--;
	KnockBack();
	if (knockBackCnt_ < 0&&!isWeak_)
	{
		ChangeState(CommonData::ENEMYSTATE::NONE);
	}
	else if (knockBackCnt_ < 0 && isWeak_)
	{
		ChangeState(CommonData::ENEMYSTATE::DEBUFF);
	}
}



void Enemy::KnockBack(void)
{

	//座標でノックバックを判定する
	auto diff = VSub(pos_, sceneGame_->GetPlayerPos());	//相手から自分を引くと相手への方向を向く。
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
		SetCoolTime(SunUtility::DEFAULT_FPS*2);
		ChangeState(CommonData::ENEMYSTATE::NONE);

	}
	else
	{
		if (stamina_ <= 0.0f)
		{
			isStaminaRecov_ = true;
			SetCoolTime(STAMINA_RECOV_TIME);
			ChangeState(CommonData::ENEMYSTATE::NONE);
		}
	}
}

void Enemy::UpdateWaidAttack(void)
{
	waidChargeCnt_++;
	//auto camera = SceneManager::GetInstance().GetCamera();
	//caseの中で変数定義と同時に初期化ができない！！！！！！！！！
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
		camera->CameraShake(10, 10);
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
			ChangeState(CommonData::ENEMYSTATE::THINK);
		}
		break;
	}
}
void Enemy::FallUpdate(void)
{
	fallCnt_--;

	if (fallCnt_ <= 0)
	{
		Damage(fallDmg_,0);
		Score(-fallScore_);
		ChangeState(CommonData::ENEMYSTATE::REVIVAL);
	}

}
void Enemy::RevivalUpdate(void)
{
	revivalCnt_--;
	SetPos(revivalPos_);
	if (revivalCnt_ <= 0)
	{
		ChangeState(CommonData::ENEMYSTATE::THINK);
	}

}
void Enemy::ChangeWaidAtkState(const SlimeBase::WAID_ATK waidAtk)
{
	waidAtk_ = waidAtk;
	switch (waidAtk_)
	{
	case SlimeBase::WAID_ATK::CHARGE:
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATKCHARGE, DX_PLAYTYPE_BACK, 60);
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDCHARGE, this, waidChargePar_);
		break;
	case SlimeBase::WAID_ATK::JUMP:
		break;
	case SlimeBase::WAID_ATK::JUMPEND:
		gravityPow_ = WAID_ATK_FALL_GRAVITY;
		break;
	case SlimeBase::WAID_ATK::ATK:
		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::WAIDATK, this, waidAtkPar_);
		sound_->PlaySe(SoundManager::SE_TYPE::WAIDATK, DX_PLAYTYPE_BACK, 60);
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





