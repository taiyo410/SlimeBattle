#pragma once
#include<DxLib.h>
class Parameta
{
public:
	//デフォルトコンストラクタ
	Parameta(void);

	//コンストラクタ
	Parameta(VECTOR ipos, VECTOR irot, VECTOR iscl, bool iisLoop = false, bool iisStop = false);

	//デストラクタ
	~Parameta();


	//メンバー変数
	VECTOR pos;
	VECTOR rot;
	VECTOR scl;
	bool isLoop;
	bool isStop;
};

