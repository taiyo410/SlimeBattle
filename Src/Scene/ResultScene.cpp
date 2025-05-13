#include<DxLib.h>
#include"../Common/CommonData.h"
#include"../Common/Easing.h"
#include"../Utility/SunUtility.h"
#include"../Application.h"
#include"../Common/Easing.h"
#include"../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/SoundManager.h"
#include"../Manager/ModelManager.h"
#include"../Object/SlimeBase.h"
#include "ResultScene.h"

bool ResultScene::Init(void)
{
	sound_ = new SoundManager();
	sound_->BGMInit();
	sound_->SEInit();
	sound_->LoadSe(SoundManager::SE_TYPE::RESULT_TITLE);
	sound_->LoadBgm(SoundManager::BGM_TYPE::RESULT);
	sound_->PlayBgm(SoundManager::BGM_TYPE::RESULT, DX_PLAYTYPE_LOOP, 50);
	model_ = new ModelManager();
	model_->ModelInit();
	
	easeStep_ = 0.0f;

	modelPos_ = {SunUtility::VECTOR_ZERO};
	modelRot_ = {SunUtility::VECTOR_ZERO};
	modelScl_ = {1.0f,1.0f,1.0f};
	resultImg_ = LoadGraph((Application::PATH_IMAGE + "ResultBack.png").c_str());
	curtainImg_ = LoadGraph((Application::PATH_IMAGE + "curtain.png").c_str());
	resultBackImg_ = LoadGraph((Application::PATH_IMAGE + "PastelRainBow.png").c_str());
	if (CommonData::GetData().GetWinPattern() == CommonData::WINPATTERN::DRAW)
	{
		resultImg_= LoadGraph((Application::PATH_IMAGE + "ResultBack(DrawNoback).png").c_str());

		modelType_ = ModelManager::MODEL_TYPE::KOKAGE;
		modelType2_ = ModelManager::MODEL_TYPE::YUUHI;
		modelPar_.pos = { SunUtility::VECTOR_ZERO.x - SlimeBase::RADIUS-SLIME_DISTANCE,SunUtility::VECTOR_ZERO.y,SunUtility::VECTOR_ZERO.z };
		modelPar_.rot = { SunUtility::VECTOR_ZERO };
		modelPar_.scl = { 1.0f,1.0f,1.0f };

		model2Pos_ = { SunUtility::VECTOR_ZERO.x + SlimeBase::RADIUS + SLIME_DISTANCE, SunUtility::VECTOR_ZERO.y, SunUtility::VECTOR_ZERO.z };
		
		model2Rot_ = { SunUtility::VECTOR_ZERO };
		model2Scl_ = { 1.0f,1.0f,1.0f };

	}
	else if (CommonData::GetData().GetWinPattern() == CommonData::WINPATTERN::P1WIN)
	{
		modelType_ = ModelManager::MODEL_TYPE::KOKAGE;
	}
	else if (CommonData::GetData().GetWinPattern() == CommonData::WINPATTERN::P2WIN)
	{
		modelType_ = ModelManager::MODEL_TYPE::YUUHI;
	}
	model_->LoadModel(modelType_);
	model_->LoadModel(modelType2_);
	model_->SetModelParam(modelType_, modelPar_.pos, SunUtility::DIR_3D::BACK);
	model_->SetModelParam(modelType2_, model2Pos_, SunUtility::DIR_3D::BACK);






	return true;
}

void ResultScene::Update(void)
{
	easeStep_++;
	stringCnt_++;
	resultBackImgRot_ += 0.05;
	if (resultBackImgRot_ > 2.0f * DX_PI_F)
	{
		resultBackImgRot_ = 0.0f;
	}
	curtainPos_.y= BackIn(easeStep_,EASING_TOTAL_TIME,0,-800,0.5);
	if (CommonData::GetData().GetWinPattern() == CommonData::WINPATTERN::DRAW)
	{
		int i = 0;
		model_->AnimUpdate(modelType_, 0.0f);
		model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::DRAW_K);
		model_->Animation(modelType_, modelPar_.pos, modelPar_.scl, SunUtility::DIR_3D::BACK);
		model_->AnimUpdate(modelType2_, 0.0f);
		model_->ChangeAnim(modelType2_, ModelManager::ANIM_TYPE::DRAW_Y);
		model_->Animation(modelType2_, model2Pos_, model2Scl_, SunUtility::DIR_3D::BACK);
	}
	else
	{
		int i = 0;
		model_->AnimUpdate(modelType_, 0.0f);
		model_->ChangeAnim(modelType_, ModelManager::ANIM_TYPE::WIN);
		model_->Animation(modelType_, modelPar_.pos, modelPar_.scl, SunUtility::DIR_3D::BACK);
	}
		
	

	

	auto& ins = InputManager::GetInput();
	if (ins.IsPadPush(DX_INPUT_KEY_PAD1, PAD_INPUT_A)&&easeStep_>=EASING_TOTAL_TIME)
	{
		sound_->PlaySe(SoundManager::SE_TYPE::RESULT_TITLE, DX_PLAYTYPE_BACK,SoundManager::SE_VOL);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
	}
}

void ResultScene::Draw(void)
{
	int font = CreateFontToHandle("Gill Sans MT", 45, 8, DX_FONTTYPE_EDGE);
	DrawRotaGraph(Application::SCREEN_SIZE_X/2, Application::SCREEN_SIZE_Y / 2+50, 1.0f, resultBackImgRot_,resultBackImg_, true);
	DrawGraph(0, 0, resultImg_, true);
	model_->DrawModel(modelType_);
	if (CommonData::GetData().GetWinPattern() == CommonData::WINPATTERN::DRAW)
	{
		model_->DrawModel(modelType2_);
	}

	if (((stringCnt_ / 30) % 2) == 0 && easeStep_ >= EASING_TOTAL_TIME)
	{
		int stringSize = GetDrawFormatStringWidthToHandle(font, "Push The Botton!");
		DrawStringToHandle((Application::SCREEN_SIZE_X - stringSize) / 2
			, Application::SCREEN_SIZE_Y / 2 + 240, "Push The A Button!", 0xfab75e, font);
	}

	DrawGraph(curtainPos_.x,curtainPos_.y, curtainImg_,false);

	DeleteFontToHandle(font);
}

bool ResultScene::Release(void)
{
	sound_->Release();
	delete sound_;
	sound_ = nullptr;
	model_->DeleteModel(modelType_);
	delete model_;
	model_ = nullptr;
	return true;
}
