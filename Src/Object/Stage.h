#pragma once
#include<DxLib.h>
class Stage
{
public:
	//１マス
	static constexpr int STAGE_ONE_SQUARE = 60;
	//マスの数
	static constexpr int STAGE_SQUARE_NUM = 11;
	//ステージ全体サイズ
	static constexpr int STAGE_ALL_SIZE_X = STAGE_ONE_SQUARE * STAGE_SQUARE_NUM;
	static constexpr int STAGE_ALL_SIZE_Z = STAGE_ONE_SQUARE * STAGE_SQUARE_NUM;

	//ステージ半分サイズ
	static constexpr int STATE_HALF_SIZE_X = STAGE_ALL_SIZE_X / 2;
	static constexpr int STATE_HALF_SIZE_Z = STAGE_ALL_SIZE_Z / 2;



	//ステージの中心からのサイズ
	//上側と右側
	static constexpr VECTOR STAGE_UP_RIGHT_CENTER2SIZE = { 330,0,330 };
	//下側と左側
	static constexpr VECTOR STAGE_DOWN_LEFT_CENTER2SIZE = { -330,0,-330 };
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	int model_;
};

