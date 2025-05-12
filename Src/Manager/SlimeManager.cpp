#include"../Object/Player.h"
#include"../Object/Enemy.h"
#include "SlimeManager.h"

SlimeManager* SlimeManager::instance_ = nullptr;

SlimeManager::SlimeManager(CommonData::MODE _mode):mode_(_mode)
{
	
}

SlimeManager::~SlimeManager(void)
{
}

void SlimeManager::CreateInstance(CommonData::MODE _mode, SceneGame* _sceneGame)
{
	if (instance_ == nullptr)
	{
		instance_ = new SlimeManager(_mode);
	}
	instance_->Init(_sceneGame);
}

SlimeManager& SlimeManager::GetInstance(void)
{
	return *instance_;
}

void SlimeManager::Init(SceneGame* _sceneGame)
{
	//slime_[0] = new Player();
	//slime_[0]->Init(_sceneGame);
	//if (mode_ == CommonData::MODE::PVE)
	//{
	//	slime_[1] = new Enemy();
	//}
	//else if (mode_ == CommonData::MODE::PVP)
	//{
	//	slime_[1] = new Player();
	//}
	//slime_[1]->Init(_sceneGame);
}

void SlimeManager::Update(void)
{
	for (int i = 0; i < SLIME_NUM; i++)
	{
		slime_[i]->Update();
	}

	//if (CommonData::GetData().GetMode() == CommonData::MODE::PVP)
	//{
	//	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
	//	{
	//		if (playerHp <= 0.5f || GetPlayer2HpPercent() <= 0.5f)
	//		{
	//			ChangeBgm(BGM_TYPE::BGM2);
	//		}
	//		else
	//		{
	//			ChangeBgm(BGM_TYPE::BGM);
	//		}
	//	}
	//	else
	//	{
	//		ChangeBgm(BGM_TYPE::BGM);
	//	}


	//	ProcessItem();
	//	for (int s = 0; s < SLIME_NUM_MAX; s++)
	//	{
	//		for (auto item : items_)
	//		{
	//			if (IsHitSpheres(slime_[s]->GetPos(), SlimeBase::RADIUS, item->GetPos(), ItemBase::ITEM_RADIUS))
	//			{
	//				if (!item->GetIsDead() && !item->GetIsGetItem() && !slime_[s]->IsGetItemPtr() && slime_[s]->GetItemReGetCnt() < 0)
	//				{
	//					slime_[s]->SetItem(item);
	//					slime_[s]->SetIsUse(true);
	//					//アイテムゲットのエフェクトを流す
	//					Parameta par;
	//					par.pos = slime_[s]->GetPos();
	//					par.rot = { 0.0f,0.0f,0.0f };
	//					par.scl = { SlimeBase::RADIUS,SlimeBase::RADIUS,SlimeBase::RADIUS };
	//					slime_[s]->SetIsItemGetEffect(true);
	//					item->SetIsGetItem(true);
	//					itemCnt_--;
	//				}
	//			}
	//		}

	//	}
	//	//通常時
	//	if (IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[PLAYER2]->GetPos(), SlimeBase::RADIUS)
	//		&& slime_[PLAYER]->GetInvincibleCnt() <= 0 && slime_[PLAYER2]->GetInvincibleCnt() <= 0)
	//	{
	//		int p1AtkPow = player_->GetAtkPow();
	//		int p2AtkPow = player2_->GetAtkPow();
	//		PlaySoundMem(hitSE_, DX_PLAYTYPE_BACK);
	//		//プレイヤー1とプレイヤー2の攻撃力を比べる
	//		PlAtkPowCompare(p1AtkPow, p2AtkPow);
	//		PVPKnockBack(slimeLoseNum_);

	//		EffectManager::GetEffect().PlayEffect(EffectManager::EFF_TYPE::HIT, slime_[PLAYER], hitEffectPar_);



	//		isCollision_ = true;
	//	}
	//	else
	//	{
	//		isCollision_ = false;
	//	}


	//	////P1の範囲攻撃
	//	for (auto item : items_)
	//	{
	//		if (item->GetIsAtkAlive())
	//		{
	//			if (slime_[PLAYER]->IsItemAtk() && IsHitSpheres(slime_[PLAYER]->GetPos(), SlimeBase::RADIUS, slime_[ENEMY]->GetPos(), item->GetWaidAtk()))
	//			{
	//				if (slime_[PLAYER]->GetInvincibleCnt() <= 0)
	//				{
	//					float waidAtkCol = item->GetWaidAtk();
	//					slime_[PLAYER2]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
	//					slime_[PLAYER2]->Damage((Speaker::WAID_ATK_COL - waidAtkCol) / 1.5, SlimeBase::INVINCIBLE_TIME);
	//					slime_[PLAYER]->AddScore((Speaker::WAID_ATK_COL - waidAtkCol) * 5);
	//					player2_->ChangePlayerState(SlimeBase::PLAYERSTATE::KNOCKBACK);
	//				}
	//			}




	//			if (IsHitSpheres(slime_[PLAYER2]->GetPos(), SlimeBase::RADIUS, slime_[PLAYER]->GetPos(), item->GetWaidAtk()) && slime_[PLAYER2]->IsItemAtk())
	//			{
	//				if (slime_[PLAYER]->GetInvincibleCnt() <= 0)
	//				{
	//					float waidAtkCol = item->GetWaidAtk();
	//					slime_[PLAYER]->SetKnockBack(SlimeBase::KNOCKBUCK_FRAME);
	//					slime_[PLAYER]->Damage((Speaker::WAID_ATK_COL - waidAtkCol) / 1.5, SlimeBase::INVINCIBLE_TIME);
	//					slime_[PLAYER2]->AddScore((Speaker::WAID_ATK_COL - waidAtkCol) * 5);
	//					player_->ChangePlayerState(SlimeBase::PLAYERSTATE::KNOCKBACK);
	//				}
	//			}
	//		}
	//	}






	//}
}

void SlimeManager::Draw(void)
{
	for (int i = 0; i < SLIME_NUM; i++)
	{
		slime_[i]->Draw();
	}
}

const float SlimeManager::GetPlayerHpPercent(const int _num)
{
	return slime_[_num]->GetHpPercent();
}

const VECTOR SlimeManager::GetPos(const int _num)
{
	return slime_[_num]->GetPos();
}


#pragma region プレイヤーゲッター
////プレイヤー座標
//VECTOR SlimeManager::GetPlayerPos(void)
//{
//	VECTOR playerPos;
//	playerPos = slime_[PLAYER]->GetPos();
//	return playerPos;
//}

////プレイヤーの方向
//SunUtility::DIR_3D SlimeManager::GetPlayerDir(void)
//{
//	SunUtility::DIR_3D playerDir;
//	playerDir = slime_[PLAYER]->GetDir();
//	return playerDir;
//}


////プレイヤーの状態
//SlimeBase::PLAYERSTATE SlimeManager::GetPlayerState(void)
//{
//	return slime_[PLAYER]->GetState();
//}
//
//float SlimeManager::GetPlayerHpPercent(void)
//{
//	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
//	{
//		return slime_[PLAYER]->GetHpPercent();
//	}
//
//}
////スコア
//int SlimeManager::GetPlayerScore(void)
//{
//	if (CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
//	{
//		return slime_[PLAYER]->GetScore();
//	}
//
//}
//
//int SlimeManager::GetPlayerInvincible(void)
//{
//	return slime_[PLAYER]->GetInvincibleCnt();
//}
//
//SunUtility::DIR_3D SlimeManager::GetPlayer2Dir(void)
//{
//	SunUtility::DIR_3D player2Dir;
//	player2Dir = slime_[PLAYER2]->GetDir();
//	return player2Dir;
//}
//
//VECTOR SlimeManager::GetPlayer2Pos(void)
//{
//	VECTOR player2Pos;
//	player2Pos = slime_[PLAYER2]->GetPos();
//	return player2Pos;
//}
//
//SlimeBase::PLAYERSTATE SlimeManager::GetPlayer2State(void)
//{
//	return player2_->GetState();
//}
//
//float SlimeManager::GetPlayer2HpPercent(void)
//{
//	if (CommonData::GetData().GetRule() == CommonData::RULE::HP)
//	{
//		return slime_[PLAYER2]->GetHpPercent();
//	}
//}
//
//int SlimeManager::GetPlayer2Score(void)
//{
//	if (CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
//	{
//		return slime_[PLAYER2]->GetScore();
//	}
//}
//
//int SlimeManager::GetPlayer2Invincible(void)
//{
//	return slime_[PLAYER2]->GetInvincibleCnt();;
//}
//
//
//
//#pragma endregion
//
//#pragma region 敵ゲッター
////敵座標
//VECTOR SlimeManager::GetEnemyPos(void)
//{
//	VECTOR enemyPos;
//	enemyPos = slime_[ENEMY]->GetPos();
//	return enemyPos;
//}
//
//
//// 敵方向
//SunUtility::DIR_3D SlimeManager::GetEnemyDir(void)
//{
//	SunUtility::DIR_3D enemyDir;
//	enemyDir = slime_[ENEMY]->GetDir();
//	return enemyDir;
//}
//
//// 敵の状態
//SlimeBase::ENEMYSTATE SlimeManager::GetEnemyState(void)
//{
//	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
//	{
//		return enemy_->GetState();
//	}
//}
////敵のHP割合ゲッタ
//float SlimeManager::GetEnemyHpPercent(void)
//{
//	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE
//		&& CommonData::GetData().GetRule() == CommonData::RULE::HP)
//	{
//		/*return (*slime_[ENEMY]).GetHpPercent();*/
//		return slime_[ENEMY]->GetHpPercent();
//	}
//}
////敵のスコア
//int SlimeManager::GetEnemyScore(void)
//{
//	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE
//		&& CommonData::GetData().GetRule() == CommonData::RULE::SCORE)
//	{
//		return slime_[ENEMY]->GetScore();
//	}
//}
//int SlimeManager::GetEnemyInvincible(void)
//{
//	return slime_[ENEMY]->GetInvincibleCnt();
//}