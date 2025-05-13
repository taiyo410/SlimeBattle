#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"
#include"SlimeBase.h"
#include "Speaker.h"

void Speaker::Update(void)
{

}

void Speaker::Draw(void)
{
	ItemBase::Draw();
}

void Speaker::SetParam(void)
{
	pos_ = { pos_.x,ITEM_RADIUS,pos_.z };
	isDead_ = false;
	isGetItem_ = false;
	isAtkAlive_ = false;
	isAtkEnd_ = false;
	itype_ = ITEM_TYPE::SPEEKER;
}

void Speaker::UpdateWaidAttack(void)
{
	if (!isDead_)
	{
		if (isAtkAlive_)
		{
			//ƒJƒƒ‰U“®ˆ—
			auto camera = SceneManager::GetInstance().GetCamera();
			camera = SceneManager::GetInstance().GetCamera();
			camera->CameraShake(SHALE_CNT, SHAKE_LIMIT);

			//“–‚½‚è”»’è‚ğL‚°‚é
			waidAtkRadius_ += WAID_COL_EXPAND_SPEED;
			if (waidAtkRadius_ >= WAID_ATK_COL)
			{
				//¶‘¶”»’è‚ğE‚µ‚Ä‰Šú‰»
				//waidAtkRadius_ = 0;
				isAtkAlive_ = false;
				isAtkEnd_ = true;
				isDead_ = true;
			}
		}
	}
}



//void Speaker::ChangeWaidAtkState(const WAID_ATK waidAtk)
//{
//	
//}
