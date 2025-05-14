#include"../Application.h"
#include "SoundManager.h"


void SoundManager::LoadBgm(const BGM_TYPE bgm)
{
	bgm_[bgm] = LoadSoundMem((Application::PATH_SOUND + bgmPass_[bgm]).c_str());
}

void SoundManager::LoadSe(const SE_TYPE se)
{
	se_[se] = LoadSoundMem((Application::PATH_SOUND + sePass_[se]).c_str());
}

void SoundManager::BGMInit(void)
{
	bgmPass_[BGM_TYPE::TITLE] = TITLE_BGM;
	bgmPass_[BGM_TYPE::GAME] = GAME_BGM;
	bgmPass_[BGM_TYPE::GAME2] = GAME2_BGM;
	bgmPass_[BGM_TYPE::RESULT] = RESULT_BGM;
}

void SoundManager::SEInit(void)
{
	sePass_[SE_TYPE::SLIMEMOVE] = STEP_SE;
	sePass_[SE_TYPE::ATTACK] = ATTACK_SE;
	sePass_[SE_TYPE::WAIDATK] = WAID_ATK_SE;
	sePass_[SE_TYPE::WAIDATKCHARGE] = CHARGE_WAID_ATK_SE;
	sePass_[SE_TYPE::BUTTON] = BUTTON_SE;
	sePass_[SE_TYPE::CANCEL] = CANCEL_SE;
	sePass_[SE_TYPE::CURSOR] = MOVE_CURSOR;
	sePass_[SE_TYPE::GAMESTART] = GAME_START_SE;
	sePass_[SE_TYPE::RESULT_TITLE] = RESULT_2_TITLE;
}



void SoundManager::PlayBgm(BGM_TYPE bgm, int type, int volPer,bool isTopPosition)
{
	PlaySoundMem(bgm_[bgm], type,isTopPosition);
	ChangeVolumeSoundMem(MAX_VOLUME_VALUE * volPer / VOLUME_MAX, bgm_[bgm]);
}

void SoundManager::PlaySe(SE_TYPE se, int type, int volPer, bool isTopPosition)
{
	PlaySoundMem(se_[se], type, isTopPosition);
	ChangeVolumeSoundMem(MAX_VOLUME_VALUE * volPer / VOLUME_MAX,se_[se]);
}

void SoundManager::StopBgm(BGM_TYPE bgm)
{
	StopSoundMem(bgm_[bgm]);
}

void SoundManager::StopSe(SE_TYPE se)
{
	StopSoundMem(se_[se]);
}

void SoundManager::Release(void)
{
	DeleteSoundMem(bgm_[BGM_TYPE::TITLE]);
	DeleteSoundMem(bgm_[BGM_TYPE::GAME]);
	DeleteSoundMem(bgm_[BGM_TYPE::GAME2]);
	DeleteSoundMem(bgm_[BGM_TYPE::RESULT]);
	DeleteSoundMem(se_[SE_TYPE::SLIMEMOVE]);
	DeleteSoundMem(se_[SE_TYPE::ATTACK]);
	DeleteSoundMem(se_[SE_TYPE::BUTTON]);
	DeleteSoundMem(se_[SE_TYPE::CANCEL]);
	DeleteSoundMem(se_[SE_TYPE::WAIDATK]);
	DeleteSoundMem(se_[SE_TYPE::WAIDATKCHARGE]);
	DeleteSoundMem(se_[SE_TYPE::CURSOR]);
}
