#pragma once
#include<DxLib.h>
#include"../Common/CommonData.h"
class SceneGame;
class SlimeBase;
class RuleBase
{
public:
	
	virtual void Init(SceneGame* parent);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);



protected:
	SceneGame* sceneGame_;

	
private:
};

