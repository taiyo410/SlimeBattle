#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"../Utility/SunUtility.h"
#include"./Camera.h"

//�R���X�g���N�^
Camera::Camera(void)
{
	angles_ = SunUtility::VECTOR_ZERO;
	pos_ = SunUtility::VECTOR_ZERO;
	shakeCnt_ = 0.0f;
	shakeState_ = SHAKE_STATE::SHAKE_UP;
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

	//�J�����̊p�x
	angles_ = INIT_ANGLES;
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
