#include"Stage.h"
#include"../Utility/SunUtility.h"
#include "Speaker.h"
#include "ItemBase.h"

ItemBase::ItemBase(void)
{
	pos_.x = GetRand(Stage::STAGE_ALL_SIZE_X-Stage::STAGE_ONE_SQUARE) - Stage::STATE_HALF_SIZE_X;
	pos_.z = GetRand(Stage::STAGE_ALL_SIZE_Z - Stage::STAGE_ONE_SQUARE) - Stage::STATE_HALF_SIZE_Z;
}

ItemBase::~ItemBase(void)
{
}

void ItemBase::Init(SlimeBase* p1, SlimeBase* p2)
{
	p1 = slime_[0];
	p2 = slime_[1];

	SetParam();

	switch (itype_)
	{
	case ItemBase::ITEM_TYPE::SPEEKER:
		break;
	case ItemBase::ITEM_TYPE::MAX:
		break;
	default:
		break;
	}

	
}

void ItemBase::Update(void)
{
	
}

void ItemBase::Draw(void)
{
	unsigned color;
	if (!isGetItem_)
	{
		color = 0x00ff00;
		DrawSphere3D(pos_, ITEM_RADIUS, 8, color, 0xffffff, true);
	}
	
}

void ItemBase::Release(void)
{
}

VECTOR ItemBase::GetPos(void)
{
	return pos_;
}

void ItemBase::IsDead(void)
{
	isDead_ = true;
}

bool ItemBase::GetIsDead(void)
{
	return isDead_;
}

bool ItemBase::IsAtkAlive(void)
{
	return isAtkAlive_ = true;
}

bool ItemBase::GetIsAtkAlive(void)
{
	return isAtkAlive_;
}

void ItemBase::SetIsGetItem(const bool isGetItem)
{
	isGetItem_ = isGetItem;
}

bool ItemBase::GetIsGetItem(void) const
{
	return isGetItem_;
}

bool ItemBase::GetIsAtkEnd(void)
{
	return isAtkEnd_;
}

void ItemBase::SetParam(void)
{
	
}

void ItemBase::UpdateWaidAttack(void)
{

}

float ItemBase::GetWaidAtk(void)
{
	return waidAtkRadius_;
}

void ItemBase::SetWaidAtk(float waidAtk)
{
	waidAtkRadius_ = waidAtk;
}

ItemBase::ITEM_TYPE ItemBase::GetItemType(void)
{
	return itype_;
}