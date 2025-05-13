#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"../Utility/SunUtility.h"
#include"./Camera.h"

//コンストラクタ
Camera::Camera(void)
{
	angles_ = SunUtility::VECTOR_ZERO;
	pos_ = SunUtility::VECTOR_ZERO;
	shakeCnt_ = 0.0f;
	shakeState_ = SHAKE_STATE::SHAKE_UP;
}

//デストラクタ
Camera::~Camera(void)
{

}

/// <summary>
///初期化処理(基本的に最初の1回だけ実装)
/// </summary>
/// <param name=""></param>
void Camera::Init(void)
{
	//カメラの位置
	pos_ = INIT_POS;

	//カメラの角度
	angles_ = INIT_ANGLES;
	shakeState_ = SHAKE_STATE::SHAKE_UP;
}

/// <summary>
/// 更新処理(毎フレーム実行)
/// </summary>
/// <param name=""></param>
void Camera::Update(void)
{
	Effekseer_Sync3DSetting();
}

/// <summary>
/// カメラ設定
/// </summary>
/// <param name=""></param>
void Camera::SetBeforeDraw(void)
{
	//クリップ距離を設定する(SetDrawScreenでリセット)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	//カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle
	(
		pos_
		, angles_.x
		, angles_.y
		, angles_.z
	);
}

/// <summary>
/// 描画処理(毎フレーム実行)
/// </summary>
/// <param name=""></param>
void Camera::Draw(void)
{

}

/// <summary>
/// 解放処理(基本的に最後の1回だけ実装)
/// </summary>
/// <param name=""></param>
void Camera::Release(void)
{

}

void Camera::CameraShake(int shakeCnt,float cameraLimit)
{
	//shakeCnt_ = shakeCnt;
	//shakeCnt_
	while(shakeCnt>=0)
	{
		shakeCnt--;
		switch (shakeState_)
		{
		case Camera::SHAKE_STATE::SHAKE_UP:
			pos_.y -= cameraLimit;
			shakeState_ = SHAKE_STATE::SHAKE_DOWN;
			break;
		case Camera::SHAKE_STATE::SHAKE_DOWN:
			pos_.y += cameraLimit;
			shakeState_ = SHAKE_STATE::SHAKE_UP;
			break;
	
		}
		
	}

}

void Camera::SetCameraWork(VECTOR pos, VECTOR rot)
{
	pos_ = pos;
	angles_ = rot;
}
