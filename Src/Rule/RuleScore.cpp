#include<DxLib.h.>
#include"../Application.h"
#include"../Manager/SceneManager.h"
#include"../Object/SlimeBase.h"
#include"../Scene/SceneGame.h"





#include "RuleScore.h"

void RuleScore::Init(SceneGame* parent)
{
	sceneGame_ = parent;
	startTime_ = GetNowCount();
	countDown_ = TIME_LIMIT;;
}

void RuleScore::Update(void)
{
	if (countDown_ <= 0)
	{
		int playerScore = sceneGame_->GetPlayerScore();
		int enemyScore = sceneGame_->GetEnemyScore(); 
		if (playerScore > enemyScore)
		{
			CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P1WIN);
		}
		else if (playerScore == enemyScore)
		{
			CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::DRAW);
		}
		else if(playerScore<enemyScore)
		{
			CommonData::GetData().SetWinPattern(CommonData::WINPATTERN::P2WIN);
		}
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT, true);
		return;

	}
	if (GetNowCount() - startTime_ > 1000)
	{
		count_++;
		countDown_--;
		startTime_ = GetNowCount();
	}
	

	

	if (count_ >= 60)
	{
		minute_++;
		count_ = 0;
	}
	//SetFontSize(36);

}

void RuleScore::Draw(void)
{
	int font = CreateFontToHandle("Gill Sans MT", 45, 8, DX_FONTTYPE_EDGE);
	int playerScore = sceneGame_->GetPlayerScore();
	int timeposX= Application::SCREEN_SIZE_X / 2 -GetDrawFormatStringWidthToHandle(font, "TIME(%.2d:%.2d)"
		, minute_, countDown_)/2;
	DrawFormatStringToHandle(timeposX, 0, 0xffffff, font, "TIME(%.2d:%.2d)"
		, minute_, countDown_);

	int plScorePosX = GetDrawFormatStringWidthToHandle(font, "%.5d", playerScore) *0.5f;
	DrawFormatStringToHandle(plScorePosX, 0,0x5195e1, font, "%.5d", playerScore);
	auto& ins = CommonData::GetData();
	//ChangeFont("Dela Gothic One",DX_CHARSET_DEFAULT);
	if (ins.GetMode() == CommonData::MODE::PVE)
	{
		
		int enemyScore = sceneGame_->GetEnemyScore();
		Vector2 pos;
		pos.x = Application::SCREEN_SIZE_X -GetDrawFormatStringWidthToHandle(font, "%.5d", enemyScore) * 1.5;
		pos.y = 0;
		DrawFormatStringToHandle(pos.x, pos.y, 0xed784a,font, "%.5d"
			,  enemyScore);
	}
	else if (ins.GetMode() == CommonData::MODE::PVP)
	{
		int enemyScore = sceneGame_->GetPlayer2Score();
		Vector2 pos;
		pos.x = Application::SCREEN_SIZE_X - GetDrawFormatStringWidthToHandle(font, "%.5d", enemyScore) * 1.5;
		pos.y = 0;

		DrawFormatStringToHandle(pos.x, pos.y, 0xed784a, font, "%.5d"
			,enemyScore);

	}
	DeleteFontToHandle(font);
}

void RuleScore::Release(void)
{

}
