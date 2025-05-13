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

	//アイテムの当たり判定の大きさ
	static constexpr float ITEM_RADIUS = 25;

	//範囲攻撃の当たり判定用
	static constexpr float WAID_ATK_COL = SlimeBase::RADIUS * 6;

	//球の角度の分割数
	static constexpr int DIV_NUM = 8;

	//アイテム種類
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

	//攻撃状態かどうか
	bool IsAtkAlive(void);

	//攻撃状態ゲッタ
	bool GetIsAtkAlive(void);

	//アイテムゲットした時のセッタ
	void SetIsGetItem(const bool isGetItem);

	//アイテムゲットした時のゲッタ
	 bool GetIsGetItem(void)const;

	 //攻撃が終わったかどうかゲッタ
	 bool GetIsAtkEnd(void);

	virtual void SetParam(void);
	//広範囲攻撃
	virtual void UpdateWaidAttack(void);

	virtual float GetWaidAtk(void);
	virtual void SetWaidAtk(float waidAtk);

	ITEM_TYPE GetItemType(void);
protected:

	SlimeBase* slime_[SceneGame::SLIME_NUM_MAX];
	ITEM_TYPE itype_;	//アイテムタイプ
	VECTOR pos_;
	float waidAtkCol_;
	float waidAtkRadius_;		//広範囲攻撃の当たり判定を大きくしていく

	bool isDead_;	//アイテムの状態
	bool isAtkAlive_;	//範囲攻撃の生存状態　true:生きている
	bool isGetItem_;	//アイテムがゲットされたか
	bool isAtkEnd_;		//攻撃が終わったか
private:
	
	

};

