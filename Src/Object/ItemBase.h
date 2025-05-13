#pragma once
#include<DxLib.h>
#include"../Scene/SceneGame.h"
#include"../Object/SlimeBase.h"
class SlimeBase;
class ItemBase
{
public:
	ItemBase(void);
	~ItemBase(void);

	//�A�C�e���̓����蔻��̑傫��
	static constexpr float ITEM_RADIUS = 25;

	//�͈͍U���̓����蔻��p
	static constexpr float WAID_ATK_COL = SlimeBase::RADIUS * 6;

	//���̊p�x�̕�����
	static constexpr int DIV_NUM = 8;

	//�A�C�e�����
	enum class ITEM_TYPE
	{
		SPEEKER
		, MAX
	};
	virtual void Init(SlimeBase* p1,SlimeBase* p2);
	virtual void Update(void);
	virtual void Draw(void);
	void Release (void);
	VECTOR GetPos(void);
	void IsDead(void);
	bool GetIsDead(void);

	//�U����Ԃ��ǂ���
	bool IsAtkAlive(void);

	//�U����ԃQ�b�^
	bool GetIsAtkAlive(void);

	//�A�C�e���Q�b�g�������̃Z�b�^
	void SetIsGetItem(const bool isGetItem);

	//�A�C�e���Q�b�g�������̃Q�b�^
	 bool GetIsGetItem(void)const;

	 //�U�����I��������ǂ����Q�b�^
	 bool GetIsAtkEnd(void);

	virtual void SetParam(void);
	//�L�͈͍U��
	virtual void UpdateWaidAttack(void);

	virtual float GetWaidAtk(void);
	virtual void SetWaidAtk(float waidAtk);

	ITEM_TYPE GetItemType(void);
protected:

	SlimeBase* slime_[SceneGame::SLIME_NUM_MAX];
	ITEM_TYPE itype_;	//�A�C�e���^�C�v
	VECTOR pos_;
	float waidAtkCol_;
	float waidAtkRadius_;		//�L�͈͍U���̓����蔻���傫�����Ă���

	bool isDead_;	//�A�C�e���̏��
	bool isAtkAlive_;	//�͈͍U���̐�����ԁ@true:�����Ă���
	bool isGetItem_;	//�A�C�e�����Q�b�g���ꂽ��
	bool isAtkEnd_;		//�U�����I�������
private:
	
	

};

