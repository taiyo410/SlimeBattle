#include"../Application.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SlimeManager.h"
#include"../Scene/SceneGame.h"
#include "RuleHp.h"

void RuleHp::Init(SceneGame* parent)
{
	sceneGame_ = parent;
}

void RuleHp::Update(void)
{
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
	{
		float playerHp = sceneGame_->GetPlayerHpPercent(SlimeManager::PLAYER);
		float enemyHp = sceneGame_->GetPlayerHpPercent(SlimeManager::ENEMY);
		if (enemyHp <= 0.0f || playerHp <= 0.0f)
		{
			if (enemyHp <= 0.0f && playerHp <= 0.0f)
			{
				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::DRAW);
			}
			else if (playerHp <= 0.0f)
			{
				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P2WIN);
			}
			
			else if (enemyHp <= 0.0f)
			{
				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P1WIN);
			}
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT, true);
			return;

		}
	}
	else if (CommonData::GetData().GetMode() == CommonData::MODE::PVP)
	{
		float playerHp = sceneGame_->GetPlayerHpPercent(SlimeManager::PLAYER);
		float player2Hp = sceneGame_->GetPlayerHpPercent(SlimeManager::ENEMY);
		if (player2Hp <= 0.0f || playerHp <= 0.0f)
		{
			if (player2Hp <= 0.0f && playerHp <= 0.0f)
			{
				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::DRAW);
			}

			else if (player2Hp <= 0.0f)
			{

				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P1WIN);
			}
			else if (playerHp <= 0.0f)
			{
				CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P2WIN);
			}
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT, true);
			return;

		}
	}
	
	
}

void RuleHp::Draw(void)
{
	float playerHp = sceneGame_->GetPlayerHpPercent(SceneGame::PLAYER);

	//プレイヤーのHP表示
	DrawBox(15, 15, 275, 40, 0x000000, true);
	if (playerHp >= 0.0f)
	{
		DrawBox(274
			, 16
			, 274 - playerHp * 260/*バーの長さ*/
			, 39, 0x2ce70b, true);
	}
	if (CommonData::GetData().GetMode() == CommonData::MODE::PVE)
	{
		float enemyHp = sceneGame_->GetPlayerHpPercent(SceneGame::ENEMY);

		//敵のHP表示
		//0を下回ったら表示しない
		DrawBox(HP_GAUGE_START_X, 15, Application::SCREEN_SIZE_X - 15, 40, 0x000000, true);
		if (enemyHp >= 0.0f)
		{
			DrawBox(HP_GAUGE_START_X, 16, HP_GAUGE_START_X + enemyHp * 260, 39, 0x2ce70b, true);
		}	
	}

	else if (CommonData::GetData().GetMode() == CommonData::MODE::PVP)
	{
		float player2Hp = sceneGame_->GetPlayer2HpPercent();

		//P2のHP表示
		DrawBox(HP_GAUGE_START_X, 15/*530 - 32*/, Application::SCREEN_SIZE_X - 15, 40, 0x000000, true);
		//0を下回ったら表示しない
		if (player2Hp >= 0.0f)
		{
			DrawBox(HP_GAUGE_START_X, 16, HP_GAUGE_START_X + player2Hp * 260, 39, 0x2ce70b, true);
		}
	}
}

void RuleHp::Release(void)
{

}
