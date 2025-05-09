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

void SlimeManager::CreateInstance(CommonData::MODE _mode)
{
	if (instance_ == nullptr)
	{
		instance_ = new SlimeManager(_mode);
	}
	instance_->Init();
}

SlimeManager& SlimeManager::GetInstance(void)
{
	return *instance_;
}

void SlimeManager::Init(void)
{
	//slime_[0] = std::make_unique<Player>();
	//slime_[0]->Init();
	//if (mode_ == MODE::PVE)
	//{
	//	slime_[1] = std::make_unique<Enemy>();
	//}
	//else if (mode_ == MODE::PVP)
	//{
	//	slime_[1] = std::make_unique<Player>();
	//}
	//slime_[1]->Init();
}

void SlimeManager::Update(void)
{
	for (int i = 0; i < SLIME_NUM; i++)
	{
		slime_[i]->Update();
	}
}

void SlimeManager::Draw(void)
{
	for (int i = 0; i < SLIME_NUM; i++)
	{
		slime_[i]->Draw();
	}
}
