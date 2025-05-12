#include<DxLib.h>
#include"../Application.h"
#include"../Manager/Camera.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/ModelManager.h"
#include"../Scene/SceneGame.h"
#include"../Object/ItemBase.h"
#include"../Object/GaugeCircle.h"
#include"./Stage.h"
#include"./SlimeBase.h"
#include"./Enemy.h"
#include"./Player.h"

//�f�t�H���g�R���X�g���N�^
SlimeBase::SlimeBase(void)
{
	//modelFileName_ = "SilmeAnimKokage.mv1";
	modelType_ = ModelManager::MODEL_TYPE::KOKAGE;
	dir_ = {};

	//�X���C����ԉ摜�̃��[�h
	slimeFaceImg_[SLIME_FACE::NORMAL] = LoadGraph((Application::PATH_IMAGE + "NormalK.png").c_str());
	slimeFaceImg_[SLIME_FACE::TIRED] = LoadGraph((Application::PATH_IMAGE + "Tukare.png").c_str());
	slimeFaceImg_[SLIME_FACE::DAMAGE] = LoadGraph((Application::PATH_IMAGE + "DamageK.png").c_str());
	slimeFaceImg_[SLIME_FACE::CHARGE] = LoadGraph((Application::PATH_IMAGE + "ChargeK.png").c_str());
	slimeFaceImg_[SLIME_FACE::ATTACK] = LoadGraph((Application::PATH_IMAGE + "AttackK.png").c_str());

	facePos_ = {};
	backSlimefacePos_ = facePos_;
	face_ = SLIME_FACE::NORMAL;

	pos_ = {};
	scale_ = { 1.0f,1.0f,1.0f };
	rot_ = { 0.0f,0.0f,0.0f };

	enemyNum_ = 0;

	revivalPos_ = { -Stage::STAGE_ONE_SQUARE * 3,RADIUS * 5,0.0f };

	waidChargeCnt_ = 0;

	waidAtkPar_.pos = { 0.0f,0.0f,0.0f };
	waidAtkPar_.rot = { 0.0f,0.0f,0.0f };
	waidAtkPar_.scl = { 0.0f,0.0f,0.0f };

	waidChargePar_.pos = SunUtility::VECTOR_ZERO;
	waidChargePar_.rot = SunUtility::VECTOR_ZERO;
	waidChargePar_.scl = { WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL,WAID_CHARGE_EFFECT_SCL };

	slimeNum_ = 0;

	score_ = 0;

	isUseItem_ = false;

	//�W�����v��
	jumpPower_ = 0.0f;

	//�W�����v����
	isJump_ = false;

	//�X�^�~�i
	stamina_ = STAMINA_MAX;

	//�X�^�~�i�������Ă邩
	isStaminaRecov_ = false;

	//�v���C���[���
	pState_ = SlimeBase::PLAYERSTATE::ACTIONABLE;

	//�t���[���J�E���g
	frame_ = FRAME_DEFAULT;

	guardCoolTime_ = 0;

	invincibleCnt_ = 0;

	coolTime_ = 0;

	itemReGetCnt_ = 0;

	gravityPow_ = DEFAULT_GRAVITY;

	fallDmg_ = FALL_DMG_DEFAULT;

	fallScore_ = FALL_SCORE_DEFAULT;

}

//�f�X�g���N�^
SlimeBase::~SlimeBase(void)
{

}

//����������
bool SlimeBase::Init(SceneGame* _sceneGame, VECTOR _initPos, int _padNum, int _enemyNum, ModelManager::MODEL_TYPE _modelType,SunUtility::DIR_3D _dir)
{
	sceneGame_ = _sceneGame;
	//�p�����[�^�ݒ�
	SetParam(_initPos,_padNum,_enemyNum,_modelType,_dir);

	//���f������
	model_ = new ModelManager();
	model_->ModelInit();
	modelHandle_=model_->LoadModel(modelType_);
	model_->SetModelParam(modelType_,pos_, dir_);

	//���y�t�@�C���̃��[�h
	stepSE_ = LoadSoundMem((Application::PATH_SOUND + "MoveSlime.mp3").c_str());
	attackSE_ = LoadSoundMem((Application::PATH_SOUND + "Attack.mp3").c_str());

	//�X���C����ԉ摜�̌��̉_�摜
	backSlimefaceImg_ = LoadGraph((Application::PATH_IMAGE + "Clowd.png").c_str());


	gaugeCircle_ = new GaugeCircle();
	gaugeCircle_->Init();

	sound_ = new SoundManager();
	sound_->SEInit();
	sound_->LoadSe(SoundManager::SE_TYPE::SLIMEMOVE);
	sound_->LoadSe(SoundManager::SE_TYPE::ATTACK);
	sound_->LoadSe(SoundManager::SE_TYPE::WAIDATKCHARGE);
	sound_->LoadSe(SoundManager::SE_TYPE::WAIDATK);

	return true;
}

//�X�V����
void  SlimeBase::Update(void)
{
	//��ԍX�V
	StateUpdate();

	//�A�j���[�V�����X�V
	model_->AnimUpdate(modelType_, frameNum_);
	model_->Animation(modelType_, pos_, scale_, dir_);

	//�ړ�����
	Jump();

	//�ړ�����
	MoveLimit();

	//���G���Ԍ��Z����
	InvincibleConsum();

	//�t���[���̏��
	FrameLimit();

	//�n�ʁ@
	Ground();
}

//�`�揈��
void SlimeBase::Draw(void)
{
	if (((invincibleCnt_ / 3) % 2) == 0)
	{
		model_->DrawModel(modelType_);
	}
	DrawRotaGraph(backSlimefacePos_.x, backSlimefacePos_.y, 1.5f, 0.0f, backSlimefaceImg_, true);
	DrawRotaGraph(facePos_.x, facePos_.y,0.1f,0.0f, slimeFaceImg_[face_], true);
}
//�������
bool SlimeBase::Release(void)
{
	model_->DeleteModel(modelType_);
	gaugeCircle_->Release();
	return true;
}

//public�̏���
//--------------------------------------------------------------------------
//�G���W�̃Q�b�^
VECTOR SlimeBase::GetPos(void)
{
	return pos_;
}

//�m�b�N�o�b�N�J�E���g�Z�b�^
void SlimeBase::SetKnockBack(const int knockBack)
{
	knockBackCnt_ = knockBack;
}

void SlimeBase::Damage(const int dmg, const int invincibleCnt)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::HP && invincibleCnt_ <= 0)
	{
		hp_ -= dmg;
	}

	//���G����
	SetInvincible(invincibleCnt);
}



int SlimeBase::GetScore(void)
{
	return score_;
}

void SlimeBase::SetInvincible(int invincibleCnt)
{
	invincibleCnt_ = invincibleCnt;
}

int SlimeBase::GetInvincibleCnt(void)
{
	return invincibleCnt_;
}

//�����Q�b�^
SunUtility::DIR_3D SlimeBase::GetDir(void)
{
	return dir_;
}

float SlimeBase::GetHpPercent(void)
{
	return hpPercent_;
}

void SlimeBase::SetParam(VECTOR _initPos, int _padNum, int _enemyNum,ModelManager::MODEL_TYPE _modelType, SunUtility::DIR_3D _dir)
{
	waidAtkPar_.pos = { 0.0f,0.0f,0.0f };
	waidAtkPar_.rot = { 0.0f,0.0f,0.0f };
	waidAtkPar_.scl = { 0.0f,0.0f,0.0f };

}


//protected�̏���
//---------------------------------------------------------------------------
//�v���C���[�̃W�����v����
void SlimeBase::ProcessJump(void)
{
	if (isJump_)return;
	SetJumpPower(MAX_JUMP_POWER);
	isJump_ = true;
}

//�W�����v
void SlimeBase::Jump(void)
{
	pos_.y += jumpPower_;
}

//��Ԃ��Ƃ̏���
void SlimeBase::StateUpdate(void)
{

}

void SlimeBase::ChangeWaidAtkState(const WAID_ATK waidAtk)
{

}

// �W�����v�͂̐ݒ�
void SlimeBase::SetJumpPower(float power)
{
	jumpPower_ = power;
	//�����x���傫���Ȃ肷����̂�h��
	if (jumpPower_ > MAX_JUMP_POWER)
	{
		jumpPower_ = MAX_JUMP_POWER;
	}
}

void SlimeBase::SetGuardCoolTime(const int guardCooltime)
{
	guardCoolTime_ = guardCooltime;
}

void SlimeBase::ChangePlayerState(PLAYERSTATE _pState)
{
	//�X�^�u
}

void SlimeBase::ChangeEnemyState(ENEMYSTATE _state)
{
	//�X�^�u
}

//��������i�W�����v�F�d�͉����x�j
void SlimeBase::AddGravity(float gravityPow)
{
	SetJumpPower(jumpPower_ - gravityPow);
}

void SlimeBase::SetItem(ItemBase* item)
{
	item_ = item;
}

void SlimeBase::SetIsUse(const bool isUseItem)
{
	isUseItem_ = isUseItem;
}


//�������Ƃ̏���
void SlimeBase::DirUpdate(SunUtility::DIR_3D dir)
{
	switch (dir)
	{
	case SunUtility::DIR_3D::FLONT:
		pos_.z += SPEED;
		break;   
	case SunUtility::DIR_3D::BACK:
		pos_.z -= SPEED;
		break;
	case SunUtility::DIR_3D::LEFT:
		pos_.x -= SPEED;
		break;
	case SunUtility::DIR_3D::RIGHT:
		pos_.x += SPEED;
		break;
	}
	if (dir != SunUtility::DIR_3D::MAX)
	{
		SetJumpPower(STEP_JUMP_POWER);
		Jump();
		isJump_ = true;
	}
}

void SlimeBase::FrameLimit(void)
{
	if (frame_ >= FRAME_MAX)
	{
		frame_ = FRAME_MAX;
	}
}

bool SlimeBase::MoveLimit(void)
{
	//����
	if (pos_.x < -MOVE_LIMIT-SlimeBase::RADIUS)
	{
		return false;
	}
	//�E��
	else if (pos_.x > MOVE_LIMIT+SlimeBase::RADIUS)
	{
		return false;
	}
	//����
	else if (pos_.z < -MOVE_LIMIT - SlimeBase::RADIUS)
	{
		return false;
	}
	//�㑤
	else if (pos_.z > MOVE_LIMIT + SlimeBase::RADIUS)
	{
		return false;
	}

	return true;

}

void SlimeBase::InvincibleConsum(void)
{
	if (invincibleCnt_ > 0)
	{
		invincibleCnt_--;
	}
	else
	{
		invincibleCnt_ = 0;
	}
}

int SlimeBase::GetInvincible(void)
{
	return invincibleCnt_;
}

void SlimeBase::Ground(void)
{
	//�n��
	if (pos_.y >= RADIUS && !MoveLimit())return;
	pos_.y = RADIUS;
	isJump_ = false;
}

void SlimeBase::DrawDirTriangle(VECTOR _pos, SunUtility::DIR_3D _dir, int _color)
{
	VECTOR attackPos;
	VECTOR attackPos2;
	VECTOR attackPos3;

	switch (_dir)
	{
	case SunUtility::DIR_3D::FLONT:
		attackPos = { _pos.x - RADIUS,HIGH,_pos.z };
		attackPos2 = { _pos.x + RADIUS,HIGH,_pos.z };
		attackPos3 = { _pos.x,HIGH,pos_.z + VERTEX };
		//3D�̎O�p�`�͗��\�����邩�玞�v���Ɏw�肷��i2�ԖڂɈړ���̍��W���߂�j
		DrawTriangle3D(attackPos, attackPos3, attackPos2, _color, true);
		break;
	case SunUtility::DIR_3D::BACK:
		attackPos = { _pos.x - RADIUS,HIGH,_pos.z };
		attackPos2 = { _pos.x + RADIUS,HIGH,_pos.z };
		attackPos3 = { _pos.x,HIGH,_pos.z - VERTEX };
		DrawTriangle3D(attackPos2, attackPos3, attackPos, _color, true);
		break;
	case SunUtility::DIR_3D::RIGHT:
		attackPos = { _pos.x,HIGH,_pos.z - RADIUS };
		attackPos2 = { _pos.x,HIGH,_pos.z + RADIUS };
		attackPos3 = { _pos.x + VERTEX,HIGH,_pos.z };
		DrawTriangle3D(attackPos2, attackPos3, attackPos, _color, true);
		break;
	case SunUtility::DIR_3D::LEFT:
		attackPos = { _pos.x,HIGH,_pos.z - RADIUS };
		attackPos2 = { _pos.x,HIGH,_pos.z + RADIUS };
		attackPos3 = { _pos.x - VERTEX,HIGH,_pos.z };
		DrawTriangle3D(attackPos, attackPos3, attackPos2, _color, true);
		break;
	}
}

bool SlimeBase::IsGetItemPtr(void)
{
	if (item_ == nullptr)
	{
		return false;
	}
	return true;
}

bool SlimeBase::IsItemAtk(void)
{
	if (item_ != nullptr)
	{
		return item_->GetIsAtkAlive();
	}
	return false;
}

int SlimeBase::GetAtkPow(void)
{
	return atkPow_;
}

bool SlimeBase::GetIsWeak(void)
{
	return isWeak_;
}

int SlimeBase::GetSlimeNum(void)
{
	return slimeNum_;
}

void SlimeBase::SetGravityPow(const float gravityPow)
{
	gravityPow_ = gravityPow;
}


void SlimeBase::SetIsWeak(bool isWeak)
{
	isWeak_ = isWeak;
}

void SlimeBase::SetCoolTime(int coolTime)
{
	coolTime_ = coolTime;
}

void SlimeBase::SetPos(const VECTOR pos)
{
	pos_ = pos;
}

int SlimeBase::GetChargeCnt(void)
{
	return waidChargeCnt_;
}

void SlimeBase::SetChargeCnt(int cnt)
{
	waidChargeCnt_ = cnt;
}

SlimeBase::WAID_ATK SlimeBase::GetWaidAtkState(void)
{
	return waidAtk_;
}

int SlimeBase::GetItemReGetCnt(void)
{
	return itemReGetCnt_;
}

void SlimeBase::AddScore(const int score)
{
	score_ += score;
}

void SlimeBase::SetIsItemGetEffect(const bool isItemGetEff)
{
	itemGetEffPlay_ = isItemGetEff;
}
