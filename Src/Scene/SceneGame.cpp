#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"../Utility/SunUtility.h"
#include"../Application.h"
#include"../Manager/InputManager.h"
#include"../Scene/SceneTitle.h"
#include"../Object/Grid.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SlimeManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/EffectManager.h"
#include"../Common/CommonData.h"
#include"../Rule/RuleHp.h"
#include"../Rule/RuleScore.h"
#include"../Object/Stage.h"
#include"../Object/ItemBase.h"
#include"../Object/Speaker.h"
#include"../Object/Speaker.h"
#include"../Object/SlimeBase.h"
#include"../Object/Player.h"
#include"../Object/Player2.h"
#include"../Object/Enemy.h"

#include"./SceneGame.h"

//�f�t�H���g�R���X�g���N�^
SceneGame::SceneGame(void)
{

}

//�f�X�g���N�^
SceneGame::~SceneGame(void)
{
}
//
void SceneGame::SetType(void)
{
	if (CommonData::GetData().GetMode()== CommonData::MODE::PVE)
	{
		type_[0] = CommonData::TYPE::PLAYER1;
		type_[1] = CommonData::TYPE::ENEMY;

	}

	if (CommonData::GetData().GetMode()== CommonData::MODE::PVP)
	{
		type_[0] = CommonData::TYPE::PLAYER1;
		type_[1] = CommonData::TYPE::PLAYER2;

	}
}

void SceneGame::SetRule(void)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
	{
		rule_ = CommonData::RULE::HP;
	}

	if (CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
	{
		rule_ = CommonData::RULE::SCORE;
	}
}

void SceneGame::DoChangeRule(void)
{
	switch (rule_)
	{
	case CommonData::RULE::HP:
		ruleBase_ = new RuleHp();
		break;
	case CommonData::RULE::SCORE:
		ruleBase_ = new RuleScore();
		break;
	}
	ruleBase_->Init(this);
}

bool SceneGame::GetIsHitItem(void)
{
	return isHitItem_;
}

//���������� 
bool SceneGame::Init(void)
{
	auto& ins = EffectManager::GetEffect();
	SetType();
	hitEffectPos_ = { 0.0f,50.0f,0.0f };
	hitEffectRot_ = { 0.0f,0.0f,0.0f };
	hitEffectscl_ = { 10.0f,10.0f,10.0f };

	hitEffectPar_ = { hitEffectPos_,hitEffectRot_,hitEffectscl_ };
	itemSpornCnt_ = ITEM_SPORN_CNT;

	//slimeMng_ = new SlimeManager(CommonData::GetData().GetMode());
	//slimeMng_->Init();








		//�X���C���̏�����
	for (int s = 0;s < SLIME_NUM_MAX; s++)
	{
		switch (type_[s])
		{
		case CommonData::TYPE::PLAYER1:
			player_ = new Player();
			slime_[s] = player_;
			break;
		case CommonData::TYPE::PLAYER2:
			player2_ = new Player2();
			slime_[s] = player2_;
			break;
		case CommonData::TYPE::ENEMY:
			enemy_ = new Enemy();
			slime_[s] = enemy_;
			break;
		}
		slime_[s]->Init(this);
	}

	SetRule();
	DoChangeRule();	//�G��HP���Q�b�g���Ă��邩��G�̌�ɒu���Ȃ��ƃk���|
	stage_ = new Stage();
	stage_->Init();
	//�������Ă��邩
	isCollision_ = false;
	isHitItem_ = false;

	bgImage_ = LoadGraph((Application::PATH_IMAGE + "BgGameImage.png").c_str());
	roboKass_ = LoadGraph((Application::PATH_IMAGE + "RoboKasu.png").c_str());
	cloudImage_ = LoadGraph((Application::PATH_IMAGE + "BgMoveImage.png").c_str());
	cloudPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };

	sound_ = new SoundManager();
	sound_->BGMInit();
	sound_->SEInit();
	sound_->LoadBgm(SoundManager::BGM_TYPE::GAME);
	sound_->LoadBgm(SoundManager::BGM_TYPE::GAME2);
	
	slimeWinNum_ = 0;
	slimeLoseNum_ = 0;

	

	return true;
}
//�X�V����
void SceneGame::Update(void)
{

	EffectManager::GetEffect().Update();

	//slimeMng_->Update();
	//�w�i����
	cloudPos_.x -= SceneTitle::MOVE_SPEED_X;
	if (cloudPos_.x + Application::SCREEN_SIZE_X / 2 <= 0)
	{
		cloudPos_.x = Application::SCREEN_SIZE_X / 2;
	}

	for (int s = 0; s < SLIME_NUM_MAX; s++)
	{
		slime_[s]->Update();
	}

	stage_->Update();
	ruleBase_->Update();

#pragma region PVE�p�̓����蔻��
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
	{
		if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
		{
			if (GetPlayerHpPercent() <= 0.5f || GetEnemyHpPercent() <= 0.5f)
			{
				ChangeBgm(BGM_TYPE::BGM2);
			}
			else
			{
				ChangeBgm(BGM_TYPE::BGM);
			}
		}
		else
		{
			ChangeBgm(BGM_TYPE::BGM);
		}
		

		//�ʏ펞
		if (IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[ENEMY]->GetPos(), SlimeBase::RADIUS)
			&&slime_[PLAYER]->GetInvincibleCnt()<=0&& slime_[ENEMY]->GetInvincibleCnt() <= 0)
		{
			auto playerDir = slime_[PLAYER]->GetDir();
			auto playerState = player_->GetState();
			auto enemyDir = slime_[ENEMY]->GetDir();
			auto enemyState = enemy_->GetState();
			PlaySoundMem(hitSE_, DX_PLAYTYPE_BACK);
			PVEKnockBack(playerDir, playerState, enemyDir, enemyState);
			//EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::HIT, slime_[PLAYER], hitEffectPar_);
		
			isCollision_ = true;
		}
		else
		{
			isCollision_ = false;
		}


		//�G�͈͍̔U��
		if (enemy_->GetState() == CommonData::ENEMYSTATE::WAIDATTACK && enemy_->GetWaidAtkState() == SlimeBase::WAID_ATK::ATK)
		{
			if (IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[ENEMY]->GetPos(), enemy_->GetWaidCol()))
			{
				if (slime_[PLAYER]->GetInvincibleCnt() <= 0)
				{
					float waidAtkCol = enemy_->GetWaidCol();
					slime_[PLAYER]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
					slime_[PLAYER]->Damage((Speaker::WAID_ATK_COL - waidAtkCol)/2, SlimeBase::INVINCIBLE_TIME);
					slime_[ENEMY]->Score((Speaker::WAID_ATK_COL - waidAtkCol) / 2);
					player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
				}
			}
		}


		
	}
#pragma endregion
#pragma region PVP

	if (CommonData::GetData().GetMode() == CommonData::MODE::PVP)
	{
		if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
		{
			if (GetPlayerHpPercent() <= 0.5f || GetPlayer2HpPercent() <= 0.5f)
			{
				ChangeBgm(BGM_TYPE::BGM2);
			}
			else
			{
				ChangeBgm(BGM_TYPE::BGM);
			}
		}
		else
		{
			ChangeBgm(BGM_TYPE::BGM);
		}
		
		
		ProcessItem();
		for (int s = 0; s < SLIME_NUM_MAX; s++)
		{
			for (auto item : items_)
			{
				if (IsHitSpheres(slime_[s]->GetPos(), SlimeBase::RADIUS, item->GetPos(), ItemBase::ITEM_RADIUS))
				{
					if (!item->GetIsDead() && !item->GetIsGetItem() && !slime_[s]->IsGetItemPtr() && slime_[s]->GetItemReGetCnt() < 0)
					{
						slime_[s]->SetItem(item);
						slime_[s]->SetIsUse(true);
						//�A�C�e���Q�b�g�̃G�t�F�N�g�𗬂�
						Parameta par;
						par.pos = slime_[s]->GetPos();
						par.rot = { 0.0f,0.0f,0.0f };
						par.scl = { SlimeBase::RADIUS,SlimeBase::RADIUS,SlimeBase::RADIUS };
						slime_[s]->SetIsItemGetEffect(true);
						item->SetIsGetItem(true);
						itemCnt_--;
					}
				}
			}

		}
		//�ʏ펞
		if (IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[PLAYER2]->GetPos(), SlimeBase::RADIUS)
			&& slime_[PLAYER]->GetInvincibleCnt() <= 0 && slime_[PLAYER2]->GetInvincibleCnt() <= 0)
		{
			int p1AtkPow = player_->GetAtkPow();
			int p2AtkPow = player2_->GetAtkPow();
			PlaySoundMem(hitSE_, DX_PLAYTYPE_BACK);
			//�v���C���[1�ƃv���C���[2�̍U���͂��ׂ�
			PlAtkPowCompare(p1AtkPow, p2AtkPow);
			PVPKnockBack(slimeLoseNum_);
			
			EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::HIT, slime_[PLAYER], hitEffectPar_);
			


			isCollision_ = true;
		}
		else
		{
			isCollision_ = false;
		}


		////P1�͈͍̔U��
		for (auto item:items_)
		{
			if (item->GetIsAtkAlive())
			{
				if (slime_[PLAYER]->IsItemAtk()&&IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[ENEMY]->GetPos(), item->GetWaidAtk()))
				{
					if (slime_[PLAYER]->GetInvincibleCnt() <= 0)
					{
						float waidAtkCol = item->GetWaidAtk();
						slime_[PLAYER2]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
						slime_[PLAYER2]->Damage((Speaker::WAID_ATK_COL - waidAtkCol) / 1.5, SlimeBase::INVINCIBLE_TIME);
						slime_[PLAYER]->Score((Speaker::WAID_ATK_COL - waidAtkCol)*5);
						player2_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
					}
				}




				if (IsHitSpheres(slime_[PLAYER2]->GetPos(), SlimeBase::RADIUS, slime_[PLAYER]->GetPos(), item->GetWaidAtk()) && slime_[PLAYER2]->IsItemAtk())
				{
					if (slime_[PLAYER]->GetInvincibleCnt() <= 0)
					{
						float waidAtkCol = item->GetWaidAtk();
						slime_[PLAYER]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
						slime_[PLAYER]->Damage((Speaker::WAID_ATK_COL - waidAtkCol)/1.5, SlimeBase::INVINCIBLE_TIME);
						slime_[PLAYER2]->Score((Speaker::WAID_ATK_COL - waidAtkCol)*5);
						player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
					}
				}
			}
		}
		





	}
#pragma endregion

	
	
}
//�`�揈��
void SceneGame::Draw(void)
{
	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y / 2
		, 1.0f
		, 0.0f
		, bgImage_
		, true
		, false
		, false);

	DrawRotaGraph(
		cloudPos_.x
		, cloudPos_.y
		, 1.0f
		, 0.0f
		, cloudImage_
		, true
		, false
		, false);


	DrawRotaGraph(
		cloudPos_.x + Application::SCREEN_SIZE_X
		, cloudPos_.y
		, 1.0f
		, 0.0f
		, cloudImage_
		, true
		, false
		, false);
	stage_->Draw();
	//�X���C���`��
	//slimeMng_->Draw();


	for (int s = 0; s < SLIME_NUM_MAX; s++)
	{
		slime_[s]->Draw();
	}
	
	for (auto item : items_)
	{
		item->Draw();
	}
	
	ruleBase_->Draw();
	DrawDebug();

}
//�������
bool SceneGame::Release(void)
{


	for (auto item : items_)
	{
		item->Release();
		delete item;
		item = nullptr;
	}
	


	stage_->Release();
	delete stage_;
	stage_ = nullptr;

	ruleBase_->Release();
	delete ruleBase_;
	ruleBase_ = nullptr;

	//delete slimeMng_;
	//slimeMng_ = nullptr;

	for (int s = 0; s < 2; s++)
	{
		slime_[s]->Release();
		delete slime_[s];
		slime_[s] = nullptr;
	}
	StopJoypadVibration(DX_INPUT_PAD1);
	StopJoypadVibration(DX_INPUT_PAD2);
	StopSoundMem(gamebgm_);
	StopSoundMem(gamebgm2_);

	EffectManager::GetEffect().StopEffect();

	sound_->Release();
	delete sound_;
	sound_ = nullptr;
	
	return true;
}

void SceneGame::DrawDebug(void)
{

	//DrawString(0, 0, "�Q�[���V�[���`��", 0xffffff);
	//DrawBox(50
	//	, 50
	//	, Application::SCREEN_SIZE_X - 50
	//	, Application::SCREEN_SIZE_Y - 50
	//	, 0xffff00
	//	, true);
	//grid_->Draw();


}

void SceneGame::PVEKnockBack(SunUtility::DIR_3D playerDir, CommonData::PLAYERSTATE playerState, SunUtility::DIR_3D enemyDir, CommonData::ENEMYSTATE enemyState)
{
	//�v���C���[�F�ːi
	if (playerState == CommonData::PLAYERSTATE::NORMALATTACK)
	{
		if (enemyState == CommonData::ENEMYSTATE::NORMALATTACK)
		{
			
			slime_[PLAYER]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
			player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
			slime_[ENEMY]->Score(100);
			slime_[PLAYER]->Damage(10, SlimeBase::INVINCIBLE_TIME);
			hitEffectPar_.pos = GetEnemyPos();
		}

		if (enemyState != CommonData::ENEMYSTATE::NORMALATTACK)
		{
			if (enemyState == CommonData::ENEMYSTATE::NONE
				|| enemy_->GetIsWeak() == true && enemyState == CommonData::ENEMYSTATE::DEBUFF)
			{
				
				slime_[ENEMY]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
				enemy_->ChangeState(CommonData::ENEMYSTATE::KNOCKBACK);
				slime_[PLAYER]->Score(300);
				slime_[ENEMY]->Damage(30, SlimeBase::INVINCIBLE_TIME);
				hitEffectPar_.pos = GetEnemyPos();
			}
			//�G�F�`���[�W��ԈȊO�̎�
			else if (enemyState != CommonData::ENEMYSTATE::CHARGE && enemyState != CommonData::ENEMYSTATE::WAIDATTACK)
			{
				
				slime_[PLAYER]->SetKnockBack(5);
				slime_[ENEMY]->SetKnockBack(5);
				slime_[ENEMY]->SetCoolTime(SunUtility::DEFAULT_FPS);
				player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
				enemy_->ChangeState(CommonData::ENEMYSTATE::KNOCKBACK);
				slime_[PLAYER]->Score(50);
				slime_[ENEMY]->Damage(5, SlimeBase::INVINCIBLE_TIME);
				hitEffectPar_.pos = GetEnemyPos();
			}
			//��̏�Ԃ���Ȃ��Ƃ�
			else if (enemy_->GetIsWeak() == false)
			{
				
				slime_[PLAYER]->SetKnockBack(5);
				player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
				hitEffectPar_.pos = GetEnemyPos();

			}
		}


	}

	//�v���C���[�F�ːi�ƃK�[�h��ԈȊO�@�G�F�ːi��
	else if (playerState != CommonData::PLAYERSTATE::NORMALATTACK && playerState != CommonData::PLAYERSTATE::GUARD && enemyState == CommonData::ENEMYSTATE::NORMALATTACK)
	{
		
		slime_[PLAYER]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
		player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		slime_[ENEMY]->Score(400);
		slime_[PLAYER]->Damage(30, SlimeBase::INVINCIBLE_TIME);
		hitEffectPar_.pos = GetEnemyPos();
	}

	else if (playerState == CommonData::PLAYERSTATE::GUARD && enemyState == CommonData::ENEMYSTATE::NORMALATTACK)
	{
		
		enemy_->ChangeState(CommonData::ENEMYSTATE::KNOCKBACK);
		enemy_->SetIsWeak(true);
		slime_[PLAYER]->Score(50);
		slime_[ENEMY]->SetCoolTime(SunUtility::DEFAULT_FPS * 3);
		slime_[ENEMY]->SetKnockBack(SlimeBase::KNOCKBACK_PARRY);
		player_->SetGuardCoolTime(Player::GUARD_COOLTIME_SUCCESS);
		hitEffectPar_.pos = GetEnemyPos();
	}



	else if (playerState == CommonData::PLAYERSTATE::STEP && enemyState != CommonData::ENEMYSTATE::NORMALATTACK)
	{
		
		slime_[PLAYER]->SetKnockBack(5);
		player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		hitEffectPar_.pos = GetEnemyPos();
	}

	else if (playerState == CommonData::PLAYERSTATE::CRITICALATTACK && slime_[ENEMY]->GetInvincibleCnt() <= 0)
	{
		
		slime_[ENEMY]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME + 5);
		enemy_->ChangeState(CommonData::ENEMYSTATE::KNOCKBACK);
		slime_[ENEMY]->SetCoolTime(SunUtility::DEFAULT_FPS);
		slime_[PLAYER]->Score(1000);
		slime_[ENEMY]->Damage(50, SlimeBase::INVINCIBLE_TIME);
		hitEffectPar_.pos = GetEnemyPos();
		
	}

	else if (slime_[PLAYER]->GetInvincibleCnt()<=0
		&&(slime_[PLAYER]->GetInvincibleCnt() <= 0
		&&playerState == CommonData::PLAYERSTATE::ACTIONABLE
		&& enemyState == CommonData::ENEMYSTATE::NONE
		|| enemyState == CommonData::ENEMYSTATE::THINK
		|| enemyState == CommonData::ENEMYSTATE::STEP
		|| enemyState == CommonData::ENEMYSTATE::DEBUFF))
	{
		
		slime_[PLAYER]->SetKnockBack(5);
		slime_[ENEMY]->SetKnockBack(5);
		slime_[ENEMY]->SetCoolTime(SunUtility::DEFAULT_FPS);
		player_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		enemy_->ChangeState(CommonData::ENEMYSTATE::KNOCKBACK);
		//slime_[ENEMY]->Damage(5, SlimeBase::INVINCIBLE_TIME);
		hitEffectPar_.pos = GetEnemyPos();
	}
	
}

void SceneGame::PVPKnockBack(int knockBackNum)
{
	int p1AtkPow = player_->GetAtkPow();
	int p2AtkPow = player2_->GetAtkPow();
	//�U���͂��ǂ����0���������ǂ�����������
	if (p1AtkPow==0&&p2AtkPow==0)
	{
		slime_[knockBackNum]->SetKnockBack(5);
		//slime_[PLAYER2]->SetKnockBack(5);
		slime_[knockBackNum]->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		//player2_->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		hitEffectPar_.pos = GetPlayerPos();
	}
	else if(p1AtkPow==p2AtkPow)
	{
		slime_[knockBackNum]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
		//slime_[PLAYER2]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
		slime_[knockBackNum]->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		//slime_[PLAYER2]->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
		//slime_[PLAYER]->Score(100);
		//slime_[PLAYER2]->Score(100);
		slime_[knockBackNum]->Damage(10, SlimeBase::INVINCIBLE_TIME);
		//slime_[PLAYER2]->Damage(10, SlimeBase::INVINCIBLE_TIME);
		hitEffectPar_.pos = GetPlayerPos();
	}
	else
	{
		if (player_->GetState() == CommonData::PLAYERSTATE::GUARD || player2_->GetState() == CommonData::PLAYERSTATE::GUARD)
		{
			slime_[knockBackNum]->SetIsWeak(true);
			//player_->Score(50);
			slime_[knockBackNum]->SetCoolTime(SunUtility::DEFAULT_FPS * 3);
			slime_[knockBackNum]->SetKnockBack(SlimeBase::KNOCKBACK_PARRY);
			slime_[knockBackNum]->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
			//player_->SetGuardCoolTime(Player::GUARD_COOLTIME_SUCCESS);
			hitEffectPar_.pos = GetPlayerPos();
		}
		else
		{
			slime_[knockBackNum]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
			slime_[knockBackNum]->ChangeState(CommonData::PLAYERSTATE::KNOCKBACK);
			//slime_[knockBackNum]->Score(300);
			slime_[knockBackNum]->Damage(30, SlimeBase::INVINCIBLE_TIME);
			hitEffectPar_.pos = GetPlayerPos();
		}
		
	}

}

void SceneGame::ChangeBgm(BGM_TYPE bgm)
{
	bgm_=bgm;
	switch (bgm_)
	{
	case SceneGame::BGM_TYPE::BGM:
		sound_->PlayBgm(SoundManager::BGM_TYPE::GAME, DX_PLAYTYPE_LOOP, 30,false);
		break;
	case SceneGame::BGM_TYPE::BGM2:
		sound_->PlayBgm(SoundManager::BGM_TYPE::GAME2, DX_PLAYTYPE_LOOP, 30,false);
		sound_->StopBgm(SoundManager::BGM_TYPE::GAME);
		break;
	default:
		break;
	}
}


#pragma region �v���C���[�Q�b�^�[
//�v���C���[���W
VECTOR SceneGame::GetPlayerPos(void)
{
	VECTOR playerPos;
	playerPos = slime_[PLAYER]->GetPos();
	return playerPos;
}

//�v���C���[�̕���
SunUtility::DIR_3D SceneGame::GetPlayerDir(void)
{
	SunUtility::DIR_3D playerDir;
	playerDir = slime_[PLAYER]->GetDir();
	return playerDir;
}


//�v���C���[�̏��
CommonData::PLAYERSTATE SceneGame::GetPlayerState(void)
{
	return player_->GetState();
}

float SceneGame::GetPlayerHpPercent(void)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
	{
		return slime_[PLAYER]->GetHpPercent();
	}
	
}
//�X�R�A
int SceneGame::GetPlayerScore(void)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
	{
		return slime_[PLAYER]->GetScore();
	}
	
}

int SceneGame::GetPlayerInvincible(void)
{
	return slime_[PLAYER]->GetInvincibleCnt();
}

SunUtility::DIR_3D SceneGame::GetPlayer2Dir(void)
{
	SunUtility::DIR_3D player2Dir;
	player2Dir = slime_[PLAYER2]->GetDir();
	return player2Dir;
}

VECTOR SceneGame::GetPlayer2Pos(void)
{
	VECTOR player2Pos;
	player2Pos = slime_[PLAYER2]->GetPos();
	return player2Pos;
}

CommonData::PLAYERSTATE SceneGame::GetPlayer2State(void)
{
	return player2_->GetState();
}

float SceneGame::GetPlayer2HpPercent(void)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
	{
		return slime_[PLAYER2]->GetHpPercent();
	}
}

int SceneGame::GetPlayer2Score(void)
{
	if (CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
	{
		return slime_[PLAYER2]->GetScore();
	}
}

int SceneGame::GetPlayer2Invincible(void)
{
	return slime_[PLAYER2]->GetInvincibleCnt();;
}



#pragma endregion

#pragma region �G�Q�b�^�[
//�G���W
VECTOR SceneGame::GetEnemyPos(void)
{
	VECTOR enemyPos;
	enemyPos = slime_[ENEMY]->GetPos();
	return enemyPos; 	
}


// �G����
SunUtility::DIR_3D SceneGame::GetEnemyDir(void)
{
	SunUtility::DIR_3D enemyDir;
	enemyDir = slime_[ENEMY]->GetDir();
	return enemyDir;
}

// �G�̏��
CommonData::ENEMYSTATE SceneGame::GetEnemyState(void)
{
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
	{
		return enemy_->GetState();
	}
}
//�G��HP�����Q�b�^
float SceneGame::GetEnemyHpPercent(void)
{
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE 
		&& CommonData::GetData().GetRule() == CommonData::RULE::HP)
	{
		/*return (*slime_[ENEMY]).GetHpPercent();*/
		return slime_[ENEMY]->GetHpPercent();
	}
}
//�G�̃X�R�A
int SceneGame::GetEnemyScore(void)
{
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE
		&& CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
	{
		return slime_[ENEMY]->GetScore();
	}
}
int SceneGame::GetEnemyInvincible(void)
{
	return slime_[ENEMY]->GetInvincibleCnt();
}
ItemBase* SceneGame::GetValidItem(void)
{
	size_t size = items_.size();

	//�A�C�e���̐V�K�쐬
	ItemBase* it = nullptr;

	//�����_���Ɏ�ނ����߂�i����1��ނ����j
	ItemBase::ITEM_TYPE randType = static_cast<ItemBase::ITEM_TYPE>
		(GetRand(static_cast<int>(ItemBase::ITEM_TYPE::MAX) - 1));
	
	for (int i = 0; i < size; i++)
	{
		//�z��̍ŏ����猩�āA�A�C�e��������łĂ��̎�ނ�������������ė��p
		if (items_[i]->GetIsDead() && randType == items_[i]->GetItemType())
		{
			switch (randType)
			{
			case ItemBase::ITEM_TYPE::SPEEKER:
				items_[i] = new Speaker();
				break;
			}
			
			return items_[i];
		}
	}
	//�ė��p���Ȃ������̂ŐV�������
	switch (randType)
	{
	case ItemBase::ITEM_TYPE::SPEEKER:
		it = new Speaker();
		break;
	case ItemBase::ITEM_TYPE::MAX:
		break;
	default:
		break;
	}

	items_.push_back(it);

	return it;

}
#pragma endregion
void SceneGame::ProcessItem(void)
{
	if (itemSpornCnt_ <= 0)
	{
		ItemBase* item = GetValidItem();
		itemCnt_++;
		item->Init(slime_[0], slime_[1]);
		itemSpornCnt_ = ITEM_SPORN_CNT;
	}
	//�A�C�e���o����̃X�|�[���Ԋu�����炷

	if (itemSpornCnt_ > 0&&itemCnt_<=ITEM_CNT_MAX)
	{
		itemSpornCnt_--;
	}
}

void SceneGame::PlAtkPowCompare(int pl1Atknum, int pl2Atknum)
{
	int diff;
	int ret;
	//�ǂ����0��������
	if (pl1Atknum ==0 && pl2Atknum == 0)
	{
		//ret = -2;
		PVPKnockBack(0);
		PVPKnockBack(1);
	}
	//����0��������
	else if (pl1Atknum==pl2Atknum)
	{
		
		PVPKnockBack(0);
		PVPKnockBack(1);
	}

	//�v���C���[�������Ă�����
	else if (pl1Atknum < pl2Atknum)
	{
		diff = pl2Atknum - pl1Atknum;
		slimeLoseNum_ = PLAYER;
		slimeWinNum_ = PLAYER2;
		PVPKnockBack(PLAYER);
		if (player2_->GetState() == CommonData::PLAYERSTATE::GUARD)
		{
			player2_->SetGuardCoolTime(Player::GUARD_COOLTIME_SUCCESS);
			slime_[PLAYER2]->Score(100);
		}
		slime_[PLAYER2]->Score(300);
	}

	//�v���C���[2�������Ă�����
	else if (pl1Atknum > pl2Atknum)
	{
		//P2�������Ă�����2��Ԃ�
		slimeLoseNum_ = PLAYER2;
		slimeWinNum_ = PLAYER;
		PVPKnockBack(1);
		if (player_->GetState() == CommonData::PLAYERSTATE::GUARD)
		{
			player_->SetGuardCoolTime(Player::GUARD_COOLTIME_SUCCESS);
			slime_[PLAYER2]->Score(100);
		}
		slime_[PLAYER]->Score(300);
	}
}
















//�������Ă��邩�ǂ����Q�b�^
bool SceneGame::GetIsCollision(void)
{
	return isCollision_;
}





//�����蔻��
bool SceneGame::IsHitSpheres(const VECTOR& pos1, float radius1
	, const VECTOR& pos2, float radius2)
{
	//���̓��m�̓����蔻��
	bool ret = false;

	//���݂��̔��a�̍��v
	float radius = radius1 + radius2;

	//���W�̍����炨�݂��̋������Ƃ�
	VECTOR diff = VSub(pos2, pos1);

	//�O�����̒藝�Ŕ�r(SprMagnitude�Ɠ���)
	float dis = (diff.x * diff.x) + (diff.y * diff.y) + (diff.z * diff.z);
	if (dis < (radius * radius))
	{
		ret = true;
	}

	return ret;
}

bool SceneGame::IsHitItem(void)
{
	return true;
}





