#include<DxLib.h>
#include"../Application.h"
#include"../Utility/SunUtility.h"
#include "Stage.h"

void Stage::Init(void)
{
	model_ = MV1LoadModel((Application::PATH_MODEL + "EmaBeni3.mv1").c_str());
	MV1SetScale(model_, { 1.0f,0.1f,1.0f });

	//3D���f���̈ʒu(�����́A3D���W)
	//MV1SetPosition(model_, { -STAGE_ONE_SQUARE / 2,0.0f,-STAGE_ONE_SQUARE / 2 });
	MV1SetPosition(model_,SunUtility::VECTOR_ZERO);

	//3D���f���̌���(�����́Ax,y,z�̉�]�ʁB�P�ʂ̓��W�A��)
	MV1SetRotationXYZ(model_, { 0.0f,0.0f/*DX_PI_F / 180*/,0.0f });
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	//���[�h���ꂽ�RD���f����������������
	MV1DrawModel(model_);
}

void Stage::Release(void)
{
	//���[�h���ꂽ�RD���f����������������
	MV1DeleteModel(model_);
}
