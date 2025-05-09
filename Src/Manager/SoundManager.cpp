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
	bgmPass_[BGM_TYPE::TITLE] = "Title.mp3";
	bgmPass_[BGM_TYPE::GAME] = "GameScene.mp3";
	bgmPass_[BGM_TYPE::GAME2] = "GameScene2.mp3";
	bgmPass_[BGM_TYPE::RESULT] = "Result.mp3";
}

void SoundManager::SEInit(void)
{
	sePass_[SE_TYPE::SLIMEMOVE] = "MoveSlime.mp3";
	sePass_[SE_TYPE::ATTACK] = "Attack.mp3";
	sePass_[SE_TYPE::WAIDATK] = "WaidAtk.mp3";
	sePass_[SE_TYPE::WAIDATKCHARGE] = "WaidCharge.mp3";
	sePass_[SE_TYPE::BUTTON] = "button.mp3";
	sePass_[SE_TYPE::CANCEL] = "Cancel.mp3";
	sePass_[SE_TYPE::CURSOR] = "Cursor.mp3";
	sePass_[SE_TYPE::GAMESTART] = "GameStart.mp3";
	sePass_[SE_TYPE::RESULT_TITLE] = "ResultButton.mp3";
}



void SoundManager::PlayBgm(BGM_TYPE bgm, int type, int volPer,bool isTopPosition)
{
	PlaySoundMem(bgm_[bgm], type,isTopPosition);
	ChangeVolumeSoundMem(255 * volPer / 100, bgm_[bgm]);
}

void SoundManager::PlaySe(SE_TYPE se, int type, int volPer, bool isTopPosition)
{
	PlaySoundMem(se_[se], type, isTopPosition);
	ChangeVolumeSoundMem(255 * volPer / 100,se_[se]);
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
