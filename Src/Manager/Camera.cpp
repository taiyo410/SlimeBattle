#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./Camera.h"

//コンストラクタ
Camera::Camera(void)
{

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
	//pos_ = { 0.0f,450.0f,-300.0f };
	//pos_ = { 0.0f,570.0f,-900.0f };

	//カメラの角度
	angles_ = INIT_ANGLES;
	//angles_ = { 60.0f * DX_PI_F / 180.0f,0.0f,0.0f };
	//angles_ = { 20.0f * DX_PI_F / 180.0f,0.0f,0.0f };

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
