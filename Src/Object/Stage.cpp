#include<DxLib.h>
#include"../Application.h"
#include"../Utility/SunUtility.h"
#include "Stage.h"

void Stage::Init(void)
{
	model_ = MV1LoadModel((Application::PATH_MODEL + "EmaBeni3.mv1").c_str());
	MV1SetScale(model_, { 1.0f,0.1f,1.0f });

	//3Dモデルの位置(引数は、3D座標)
	//MV1SetPosition(model_, { -STAGE_ONE_SQUARE / 2,0.0f,-STAGE_ONE_SQUARE / 2 });
	MV1SetPosition(model_,SunUtility::VECTOR_ZERO);

	//3Dモデルの向き(引数は、x,y,zの回転量。単位はラジアン)
	MV1SetRotationXYZ(model_, { 0.0f,0.0f/*DX_PI_F / 180*/,0.0f });
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	//ロードされた３Dモデルをメモリから解放
	MV1DrawModel(model_);
}

void Stage::Release(void)
{
	//ロードされた３Dモデルをメモリから解放
	MV1DeleteModel(model_);
}
