#include<DxLib.h>
#include"../Application.h"
#include "ModelManager.h"

void ModelManager::ModelInit(void)
{
	modelFilePass_[MODEL_TYPE::KOKAGE] = "SilmeAnimKokage.mv1";
	modelFilePass_[MODEL_TYPE::YUUHI] = "SilmeAnimYuuhi.mv1";
}

int ModelManager::LoadModel(MODEL_TYPE model)
{
	//モデルの読み込み
	modelId_[model] = MV1LoadModel((Application::PATH_MODEL + modelFilePass_[model]).c_str());
	return modelId_[model];
}

void ModelManager::SetModelParam(MODEL_TYPE model,VECTOR pos, SunUtility::DIR_3D dir)
{
	//モデルの角度設定
	SetRotation(dir, model);
	//再生するアニメーションの設定
	animAttachNo_[model] = MV1AttachAnim(modelId_[model], animNo_[model]);
	// アニメーション総時間の取得
	animTotalTime_[model] = MV1GetAttachAnimTotalTime(modelId_[model], animAttachNo_[model]);
	stepAnim_[model] = 0.0f;
	MV1SetPosition(modelId_[model], pos);
}

void ModelManager::SetRotation(SunUtility::DIR_3D dir, MODEL_TYPE model)
{
	switch (dir)
	{
	case SunUtility::DIR_3D::FLONT:
		rot_.y = FLONT_DEG * DEG_TO_RAD;
		break;
	case SunUtility::DIR_3D::BACK:
		rot_.y = BACK_DEG * DEG_TO_RAD;
		break;
	case SunUtility::DIR_3D::RIGHT:
		rot_.y = RIGHT_DEG * DEG_TO_RAD;
		break;
	case SunUtility::DIR_3D::LEFT:
		rot_.y = LEFT_DEG * DEG_TO_RAD;
		break;
	}

	MV1SetRotationXYZ(modelId_[model], rot_);
}

void ModelManager::Animation(MODEL_TYPE model, VECTOR pos, VECTOR scl, SunUtility::DIR_3D dir)
{
	float deltaTime = SunUtility::DELTA_TIME;
	//座標
	MV1SetPosition(modelId_[model], pos);

	//モデルの角度設定
	SetRotation(dir,model);

	//スケール
	MV1SetScale(modelId_[model], scl);

	//アニメーション時間
	stepAnim_[model] += (speedAnim_[model] * deltaTime);
	if (stepAnim_[model] > animTotalTime_[model])
	{
		endAnim_[model] = true;
		EndAnimation(model);
	}
	else
	{
		endAnim_[model] = false;
	}

	//再生するanimation時間の指定
	MV1SetAttachAnimTime(modelId_[model], animAttachNo_[model], stepAnim_[model]);
}



void ModelManager::AnimUpdate(MODEL_TYPE model, float accel)
{
	switch (anim_)
	{
	case ANIM_TYPE::IDLE:
		speedAnim_[model] = ANIM_SPEED_DEFAULT;
		break;
	case ANIM_TYPE::STEP:
		speedAnim_[model] = ANIM_SPEED_DEFAULT * (animTotalTime_[model] / accel);
		break;
	case ANIM_TYPE::CHARGE:
		speedAnim_[model] = ANIM_SPEED_DEFAULT;
		break;
	case ANIM_TYPE::ATTACK:
		speedAnim_[model] = ANIM_SPEED_DEFAULT * (animTotalTime_[model] / accel);
		break;
	case ANIM_TYPE::WIN:
		speedAnim_[model] = ANIM_SPEED_DEFAULT;
		break;
	case ANIM_TYPE::DRAW_K:
		speedAnim_[model] = ANIM_SPEED_DEFAULT;
		break;
	case ANIM_TYPE::DRAW_Y:
		speedAnim_[model] = ANIM_SPEED_DEFAULT;
	case ANIM_TYPE::MAX:
		break;
	default:
		break;
	}
}

void ModelManager::DrawModel(MODEL_TYPE model)
{
	MV1DrawModel(modelId_[model]);
}


void ModelManager::EndAnimation(MODEL_TYPE model)
{
	switch (anim_)
	{
	case ModelManager::ANIM_TYPE::IDLE:
		stepAnim_[model] = 0.0f;
		break;
	case ModelManager::ANIM_TYPE::STEP:
		stepAnim_[model] = END_ANIM;
		break;
	case ModelManager::ANIM_TYPE::CHARGE:
		stepAnim_[model] = END_ANIM;
		break;
	case ModelManager::ANIM_TYPE::ATTACK:
		stepAnim_[model] = END_ANIM;
		break;
	case ModelManager::ANIM_TYPE::WIN:
		stepAnim_[model] = 0.0f;
		break;
	case ModelManager::ANIM_TYPE::DRAW_K:
		stepAnim_[model] = 0.0f;
		break;
	case ModelManager::ANIM_TYPE::DRAW_Y:
		stepAnim_[model] = 0.0f;
		break;
	case ModelManager::ANIM_TYPE::MAX:
		break;
	default:
		break;
	}
}

void ModelManager::ChangeAnim(MODEL_TYPE model, ANIM_TYPE anim)
{
	
	anim_ = anim;
	MV1DetachAnim(modelId_[model], animAttachNo_[model]);
	animAttachNo_[model] = MV1AttachAnim(modelId_[model], static_cast<int>(anim_));
	
}

void ModelManager::SetStepAnim(MODEL_TYPE model, float num)
{
	stepAnim_[model] = num;
}

void ModelManager::DeleteModel(MODEL_TYPE model)
{
	MV1DeleteModel(modelId_[model]);
}

int ModelManager::GetModelHandle(MODEL_TYPE model)
{
	return modelId_[model];
}

void ModelManager::SetModelHandle(MODEL_TYPE model,int handle)
{
	modelId_[model]=handle;
}
