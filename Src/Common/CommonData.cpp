#include<DxLib.h>
#include"./CommonData.h"

//シングルトン化
//-----------------------------------
//data_の初期化処理
CommonData* CommonData::data_ = nullptr;

//デフォルトコンストラクタ
CommonData::CommonData(void)
{
	mode_ = MODE::PVE;
	win_ = WINPATTERN::P1WIN;
	playerScore_ = 0;
}

//デストラクタ
CommonData::~CommonData(void)
{

}
bool CommonData::DataInit(void)
{
	mode_ = MODE::PVE;
	win_ = WINPATTERN::P1WIN;
	return true;
}

void CommonData::ModeUpdate(void)
{
	switch (mode_)
	{
	case MODE::PVE:
		type_[0] = TYPE::PLAYER1;
		type_[1] = TYPE::ENEMY;
		break;
	case MODE::PVP:
		type_[0] = TYPE::PLAYER1;
		type_[1] = TYPE::PLAYER2;
		break;
	}
}

void CommonData::SetWinPattern(WINPATTERN win)
{
	win_ = win;
}

CommonData::WINPATTERN CommonData::GetWinPattern(void)
{
	return win_;
}

//操作制御インスタンスの開放
void CommonData::ReleaseData(void)
{
	//シングルトン化
	Destroy();
}

void CommonData::CreateData(void)
{
	if (data_ == nullptr)
	{
		data_ = new CommonData();
	}
	data_->DataInit();
}

//インスタンスを外部に呼び出せるようにする
CommonData& CommonData::GetData(void)
{
	return *data_;
}

void CommonData::Destroy(void)
{
	delete data_;		//インスタンスを削除
	data_ = nullptr;	//インスタンス領域を初期化
}

CommonData::MODE CommonData::GetMode(void)
{
	return mode_;
}

CommonData::RULE CommonData::GetRule(void)
{
	return rule_;
}

void CommonData::SetMode(MODE value)
{
	mode_ = value;
}

void CommonData::SetRule(RULE value)
{
	rule_ = value;
}

void CommonData::SetPlayerScore(const int playerScore)
{
	playerScore_ = playerScore;
}

void CommonData::SetEnemyScore(const int enemyScore)
{
	enemyScore_ = enemyScore;
}

int CommonData::GetPlayerScore(void)
{
	return playerScore_;
}

int CommonData::GetEnemyScore(void)
{
	return enemyScore_;
}
