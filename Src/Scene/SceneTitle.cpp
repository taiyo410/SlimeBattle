#include<DxLib.h>"
#include"../Common/Vector2.h"
#include"../Application.h"
#include"../Rule/RuleBase.h"
#include"../Manager/InputManager.h"
#include"../Manager/SoundManager.h"
#include"../Common/CommonData.h"
#include"../Object/Grid.h"
#include"../Manager/SceneManager.h"
#include"../Scene/SceneTitle.h"

//初期化処理
bool SceneTitle::Init(void)
{
	CommonData::GetData().SetMode(CommonData::MODE::PVE);
	CommonData::GetData().SetRule(CommonData::RULE::HP);
	//mode_ = 1;
	//rule_ = 1;
	circleSlimeImage_ = LoadGraph((Application::PATH_IMAGE + "CircleSlime.png").c_str());
	bgImage_ = LoadGraph((Application::PATH_IMAGE + "BgImage.png").c_str());
	cloudPos_ = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 2 };
	cloudImage_ = LoadGraph((Application::PATH_IMAGE + "BgMoveImage.png").c_str());
	kintounImage_ = LoadGraph((Application::PATH_IMAGE + "kintoun.png").c_str());
	kintounPos_ = { Application::SCREEN_SIZE_X * 2 ,Application::SCREEN_SIZE_Y / 2+100 };
	rogoImage_ = LoadGraph((Application::PATH_IMAGE + "Rogo.png").c_str());
	modeImage_ = LoadGraph((Application::PATH_IMAGE + "mode2.png").c_str());
	ruleImage_ = LoadGraph((Application::PATH_IMAGE + "rule.png").c_str());
	selectImage_ = LoadGraph((Application::PATH_IMAGE + "Select.png").c_str());

	//タガメ剣持（アニメーション）
	int ret;
	ret = LoadDivGraph((Application::PATH_IMAGE + "tagame.png").c_str()
		, TAGAME_ANIME_ALL
		, TAGAME_ANIME_ALL
		, TAGAME_ANIME_DIR
		, TAGAME_SIZE_X
		, TAGAME_SIZE_Y
		, & (tagameImg_[0]));
	if (ret == -1)
	{
		return false;
	}
	



	//titlebgm_ = LoadSoundMem((Application::PATH_SOUND + "Title.mp3").c_str());
	moveFlg_ = false;
	sound_ = new SoundManager();
	sound_->BGMInit();
	sound_->SEInit();
	sound_->LoadBgm(SoundManager::BGM_TYPE::TITLE);
	sound_->PlayBgm(SoundManager::BGM_TYPE::TITLE, DX_PLAYTYPE_LOOP, 50);


	sound_->LoadSe(SoundManager::SE_TYPE::BUTTON);
	sound_->LoadSe(SoundManager::SE_TYPE::CANCEL);
	sound_->LoadSe(SoundManager::SE_TYPE::CURSOR);
	sound_->LoadSe(SoundManager::SE_TYPE::GAMESTART);

	selectPos_ = { Application::SCREEN_SIZE_X / 2 - MODE_IMG_SIZE_X / 2 - 30
					, Application::SCREEN_SIZE_Y - 400 - MODE_IMG_SIZE_Y / 2 };

	ChangeSelect(CommonData::SELECT::MODE);
	ChangeMode(CommonData::MODE::PVE);
	ChangeRule(CommonData::RULE::HP);

	speedAnim_ = ANIM_SPEED_DEFAULT;

	//ChangeVolumeSoundMem(255 * 50 / 100, titlebgm_);

	return true;
}

//更新処理
void SceneTitle::Update(void)
{
	rot_+=ROT_SPEED;
	cntAnim_++;
	//雲画像の移動
	cloudPos_.x -= MOVE_SPEED_X;
	kintounPos_.x -= KINTOUN_MOVE_SPEED_X;
	if (cloudPos_.x+ Application::SCREEN_SIZE_X/2 <= 0)
	{
		cloudPos_.x = Application::SCREEN_SIZE_X / 2;
	}
	if (kintounPos_.x + Application::SCREEN_SIZE_X < 0)
	{
		kintounPos_.x = Application::SCREEN_SIZE_X * 2;
	}
	switch (select_)
	{
	case CommonData::SELECT::MODE:
		ModeUpdate();
		break;
	case CommonData::SELECT::RULE:
		RuleUpdate();
		break;
	}
}

//描画処理
void SceneTitle::Draw(void)
{
	int font=CreateFontToHandle("Gill Sans MT", 100, 8, DX_FONTTYPE_EDGE);
	
	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y /2
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
		cloudPos_.x+Application::SCREEN_SIZE_X
		, cloudPos_.y
		, 1.0f
		, 0.0f
		, cloudImage_
		, true
		, false
		, false);

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y / 2
		, 1.0f
		, 0.0f
		, rogoImage_
		, true
		, false
		, false);

	DrawRotaGraph(
		kintounPos_.x
		, kintounPos_.y
		, 1.0f
		, 0.0f
		, kintounImage_
		, true
		, false
		, false);

	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2
		, Application::SCREEN_SIZE_Y + 130
		, 1.0f
		, rot_
		, circleSlimeImage_
		, true
		, false
		, false);


	DrawGraph(selectPos_.x
		, selectPos_.y
		, selectImage_
		, true);

	DrawRectGraph(
		Application::SCREEN_SIZE_X / 2-MODE_IMG_SIZE_X/2
		, Application::SCREEN_SIZE_Y -400-MODE_IMG_SIZE_Y/2
		, modeImgRectPos_.x			//描画するモード画像上の表示したい矩形の左上座標
		, modeImgRectPos_.y
		,MODE_DRAW_SIZE_X
		,MODE_DRAW_SIZE_Y
		, modeImage_
		, true
		, false
		, false);

	DrawRectGraph(
		Application::SCREEN_SIZE_X / 2 - MODE_IMG_SIZE_X / 2
		, Application::SCREEN_SIZE_Y - 300 - MODE_IMG_SIZE_Y / 2
		, ruleImgRectPos_.x			//描画するモード画像上の表示したい矩形の左上座標
		, ruleImgRectPos_.y
		, RULE_DRAW_SIZE_X
		, RULE_DRAW_SIZE_Y
		, ruleImage_
		, true
		, false
		, false);

	int idxAnim = 
		static_cast<int>(static_cast<float>(cntAnim_) * speedAnim_) % TAGAME_ANIME_ALL;
	DrawRotaGraph(tagamePos_.x
		, tagamePos_.y, 1.0f, tagameRot_, tagameImg_[idxAnim], true, false);


	


	DATEDATA time;
	GetDateTime(&time);
	

	DrawFormatStringToHandle(0, 0, 0xffffff,font,"%d:%.2d", time.Hour, time.Min);
	//DrawDebug();
	DeleteFontToHandle(font);
}
//解放処理
bool SceneTitle::Release(void)
{
	//rule_->Release();
	DeleteGraph(circleSlimeImage_);
	DeleteGraph(cloudImage_);
	DeleteGraph(rogoImage_);
	DeleteGraph(bgImage_);

	sound_->Release();
	delete sound_;
	sound_ = nullptr;
	return true;
}

//デバッグ用の関数
void SceneTitle::DrawDebug(void)
{
	//DrawString(0, 0, "タイトルシーン描画", 0xffffff);
	//DrawBox(50
	//	, 50
	//	, Application::SCREEN_SIZE_X - 50
	//	, Application::SCREEN_SIZE_Y - 50
	//	, 0x00ffff
	//	, true);


	DrawFormatString(0, 16, 0x000000, "MODE(%d)\nRULE(%d)\nFLG(%d)"
		,mode_
		,rule_
	,moveFlg_);


	//VECTOR pos=VGet(0.0f,0.0f,0.0f);
	//VECTOR pos = { 0.0f,0.0f,0.0f };
	//3D球体の描画
	//(位置、半径、ポリゴン数、)
	//
	//DrawSphere3D(pos, 80.0f, 16, 0xffffff, 0xffffff,true);
	//pos.z = 40.0f;
	//DrawSphere3D(pos, 100.0f, 16, 0xff0000, 0xffffff, true);
	//grid_->Draw();

	
}

void SceneTitle::ModeUpdate(void)
{
	auto& ins = InputManager::GetInput();
	auto& comins = CommonData::GetData();
	auto padNum= DX_INPUT_KEY_PAD1;
	if (ins.IsPadPush(padNum, PAD_INPUT_LEFT))
	{
		sound_->PlaySe(SoundManager::SE_TYPE::CURSOR, DX_PLAYTYPE_BACK, SoundManager::SE_VOL);
		comins.SetMode(CommonData::MODE::PVE);
		ChangeMode(CommonData::MODE::PVE);
		moveFlg_ = true;
		modeGoalPos_.x = 0;
		
	}

	if (ins.IsPadPush(padNum, PAD_INPUT_RIGHT))
	{
		sound_->PlaySe(SoundManager::SE_TYPE::CURSOR, DX_PLAYTYPE_BACK,SoundManager::SE_VOL);
		comins.SetMode(CommonData::MODE::PVP);
		ChangeMode(CommonData::MODE::PVP);
		moveFlg_ = true;
		modeGoalPos_.x = MODE_GOAL_MAX;

	}
	
	switch (mode_)
	{
	case CommonData::MODE::PVE:
		MoveTagame(TAGAME_MOVE_SPEED);
		if (moveFlg_)
		{
			modeImgRectPos_.x -= MODE_MOVE_SPEED;
		}
		if (modeImgRectPos_.x <= modeGoalPos_.x)
		{
			modeImgRectPos_.x = modeGoalPos_.x;
			moveFlg_ = false;
		}
		break;
	case CommonData::MODE::PVP:
		MoveTagame(-TAGAME_MOVE_SPEED);
		
		if (moveFlg_)
		{
			modeImgRectPos_.x += MODE_MOVE_SPEED;
		}
		
		if (modeImgRectPos_.x >= modeGoalPos_.x)
		{
			modeImgRectPos_.x = modeGoalPos_.x;
			moveFlg_ = false;
		}
		break;
	}
	if (ins.IsPadPush(padNum,PAD_INPUT_A)&&!moveFlg_)
	{
		sound_->PlaySe(SoundManager::SE_TYPE::BUTTON, DX_PLAYTYPE_BACK, SoundManager::SE_VOL);
		ChangeSelect(CommonData::SELECT::RULE);
	}
}

void SceneTitle::RuleUpdate(void)
{
	auto& ins = InputManager::GetInput();
	auto& comins = CommonData::GetData();
	auto padNum = DX_INPUT_KEY_PAD1;
	if (ins.IsPadPush(padNum,PAD_INPUT_LEFT))
	{
		CommonData::GetData().SetRule(CommonData::RULE::HP);
		sound_->PlaySe(SoundManager::SE_TYPE::CURSOR, DX_PLAYTYPE_BACK, SoundManager::SE_VOL);
		ChangeRule(CommonData::RULE::HP);
		moveFlg_ = true;
		ruleGoalPos_.x = 0;
	}
	if (ins.IsPadPush(padNum, PAD_INPUT_RIGHT))
	{
 		CommonData::GetData().SetRule(CommonData::RULE::SCORE);
		sound_->PlaySe(SoundManager::SE_TYPE::CURSOR, DX_PLAYTYPE_BACK, SoundManager::SE_VOL);
		ChangeRule(CommonData::RULE::SCORE);
		moveFlg_ = true;
		ruleGoalPos_.x = RULE_GOAL_MAX;
	}
	switch (rule_)
	{
	case CommonData::RULE::HP:
		MoveTagame(TAGAME_MOVE_SPEED);
		if (moveFlg_)
		{
			ruleImgRectPos_.x -= MODE_MOVE_SPEED;
		}
		if (ruleImgRectPos_.x <= ruleGoalPos_.x)
		{
			ruleImgRectPos_.x = ruleGoalPos_.x;
			moveFlg_ = false;
		}
		break;
	case CommonData::RULE::SCORE:
		MoveTagame(-TAGAME_MOVE_SPEED);
		if (moveFlg_)
		{
			ruleImgRectPos_.x += MODE_MOVE_SPEED;
		}
		if (ruleImgRectPos_.x >= ruleGoalPos_.x)
		{
			ruleImgRectPos_.x = ruleGoalPos_.x;
			moveFlg_ = false;
		}
		break;
	default:
		break;
	}
	if (ins.IsPadPush(padNum,PAD_INPUT_A)&&!moveFlg_)
	{
		sound_->PlaySe(SoundManager::SE_TYPE::GAMESTART, DX_PLAYTYPE_BACK,SoundManager::SE_VOL);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
	if (ins.IsPadPush(padNum,PAD_INPUT_B)&&!moveFlg_)
	{
		sound_->PlaySe(SoundManager::SE_TYPE::CANCEL, DX_PLAYTYPE_BACK, SoundManager::SE_VOL);
		ChangeSelect(CommonData::SELECT::MODE);
	}
}

void SceneTitle::ChangeSelect(CommonData::SELECT select)
{
	select_ = select;
	switch (select_)
	{
	case CommonData::SELECT::MODE:
		selectPos_ = { Application::SCREEN_SIZE_X / 2 - MODE_IMG_SIZE_X / 2 - 30, Application::SCREEN_SIZE_Y - 400 - MODE_IMG_SIZE_Y / 2 };
		if (mode_ == CommonData::MODE::PVE)
		{
			ChangeMode(CommonData::MODE::PVE);
		}
		else
		{
			ChangeMode(CommonData::MODE::PVP);
		}
		
		break;
	case CommonData::SELECT::RULE:
		selectPos_ = { Application::SCREEN_SIZE_X / 2 - MODE_IMG_SIZE_X / 2 - 30, Application::SCREEN_SIZE_Y - 300 - MODE_IMG_SIZE_Y / 2 };
		if (rule_ == CommonData::RULE::HP)
		{
			ChangeRule(CommonData::RULE::HP);
		}
		else
		{
			ChangeRule(CommonData::RULE::SCORE);
		}
		break;
	}
}

void SceneTitle::ChangeRule(const CommonData::RULE rule)
{
	rule_ = rule;
	moveframe_ = 0;
	switch (rule_)
	{
	case CommonData::RULE::HP:
		tagamePos_ = { selectPos_.x + SELECT_SIZE_X + TAGAME_SIZE_Y / 2, selectPos_.y + SELECT_SIZE_Y / 2 };
		tagameRot_ = -(90.0 * DX_PI_F / 180);
		break;
	case CommonData::RULE::SCORE:
		tagamePos_ = { selectPos_.x - TAGAME_SIZE_Y / 2, selectPos_.y + SELECT_SIZE_Y / 2 };
		tagameRot_ = 90.0 * DX_PI_F / 180;
		break;
	default:
		break;
	}
	startPos_ = tagamePos_;
}

void SceneTitle::ChangeMode( CommonData::MODE mode)
{
	mode_ = mode;
	moveframe_ = 0;
	switch (mode)
	{
	case CommonData::MODE::PVE:
		tagamePos_ = { selectPos_.x + SELECT_SIZE_X + TAGAME_SIZE_Y / 2, selectPos_.y + SELECT_SIZE_Y / 2 };
		tagameRot_ = -(90.0 * DX_PI_F / 180);
		break;
	case CommonData::MODE::PVP:
		tagamePos_ = { selectPos_.x - TAGAME_SIZE_Y / 2, selectPos_.y + SELECT_SIZE_Y / 2 };
		
		tagameRot_ = 90.0 * DX_PI_F / 180;
		break;
	case CommonData::MODE::MAX:
		break;
	default:
		break;
	}
	startPos_ = tagamePos_;
}

void SceneTitle::MoveTagame(int move)
{
	moveframe_++;
	if (moveframe_ < TAGAME_MOVE_FRAME)
	{
		tagamePos_.x += move;
	}
	else
	{
		tagamePos_ = startPos_;
		moveframe_ = 0;
	}
}
