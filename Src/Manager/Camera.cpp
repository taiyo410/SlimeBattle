#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./Camera.h"

//�R���X�g���N�^
Camera::Camera(void)
{

}

//�f�X�g���N�^
Camera::~Camera(void)
{

}

/// <summary>
///����������(��{�I�ɍŏ���1�񂾂�����)
/// </summary>
/// <param name=""></param>
void Camera::Init(void)
{
	//�J�����̈ʒu
	pos_ = INIT_POS;
	//pos_ = { 0.0f,450.0f,-300.0f };
	//pos_ = { 0.0f,570.0f,-900.0f };

	//�J�����̊p�x
	angles_ = INIT_ANGLES;
	//angles_ = { 60.0f * DX_PI_F / 180.0f,0.0f,0.0f };
	//angles_ = { 20.0f * DX_PI_F / 180.0f,0.0f,0.0f };

	shakeState_ = SHAKE_STATE::SHAKE_UP;
}

/// <summary>
/// �X�V����(���t���[�����s)
/// </summary>
/// <param name=""></param>
void Camera::Update(void)
{
	Effekseer_Sync3DSetting();
}

/// <summary>
/// �J�����ݒ�
/// </summary>
/// <param name=""></param>
void Camera::SetBeforeDraw(void)
{
	//�N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);
	//�J�����̐ݒ�(�ʒu�Ɗp�x�ɂ�鐧��)
	SetCameraPositionAndAngle
	(
		pos_
		, angles_.x
		, angles_.y
		, angles_.z
	);
}

/// <summary>
/// �`�揈��(���t���[�����s)
/// </summary>
/// <param name=""></param>
void Camera::Draw(void)
{

}

/// <summary>
/// �������(��{�I�ɍŌ��1�񂾂�����)
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
