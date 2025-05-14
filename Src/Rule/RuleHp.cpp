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
	DrawBox(HP_GAUGE_PLAYER1_POS_X, HP_GAUGE_PLAYER1_POS_Y
		, HP_GAUGE_WIDTH_X, HP_GAUGE_HEIGHT_Y, SunUtility::BLACK, true);
	if (playerHp >= 0.0f)
	{
		DrawBox(HP_IN_GAUGE_PLAYER_X
			, HP_IN_GAUGE_PLAYER_Y
			, HP_IN_GAUGE_PLAYER_X - playerHp * HP_GAUGE_WIDTH/*バーの長さ*/
			, HP_IN_GAUGE_WIDTH, HP_GAUGE_ENEMY_COLOR, true);
	}

	float enemyHp = sceneGame_->GetPlayerHpPercent(SceneGame::ENEMY);

	//敵のHP表示
	//0を下回ったら表示しない
	DrawBox(HP_GAUGE_START_ENEMY_X, HP_GAUGE_ENEMY_POS_X, Application::SCREEN_SIZE_X - HP_GAUGE_ENEMY_POS_X
		, HP_GAUGE_P2_HEIGHT_Y, 0x000000, true);
	if (enemyHp >= 0.0f)
	{
		DrawBox(HP_GAUGE_START_ENEMY_X, HP_GAUGE_START_ENEMY_Y
			, HP_GAUGE_START_ENEMY_X + enemyHp * HP_GAUGE_ENEMY_WIDTH, HP_GAUGE_START_ENEMY_HEGHT, 0x2ce70b, true);
	}
}        

void RuleHp::Release(void)
{

}
