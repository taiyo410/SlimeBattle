#include<DxLib.h>
#include"../Application.h"
#include"Fade.h"

//�f�t�H���g�R���X�g���N�^
Fader::Fader(void)
{
	state_ = STATE::NONE;
	alpha_ = 0.0F;
	isPreEnd_ = true;
	isEnd_ = true;		//��������ĂȂ�
}

//�f�X�g���N�^
Fader::~Fader(void)
{

}

//����������
void Fader::Init(void)
{
	state_ = STATE::NONE;
	alpha_ = 0.0F;
	isPreEnd_ = true;
	isEnd_ = true;		//��������ĂȂ�
}

//�X�V����
void Fader::Update(void)
{
	if (isEnd_)
	{
		//�t�F�[�h�������I�����Ă����牽�����Ȃ�
		return;
	}

	if (isPreEnd_)
	{
		//1�t���[����(Draw��j�ɏI������
		isEnd_ = true;
		return;
	}

	switch (state_)
	{
	case STATE::NONE:
		return;
	case STATE::FADE_OUT:
		alpha_ += SPEED_ALPHA;
		if (alpha_ > 255)
		{
			//�t�F�[�h�I��
			alpha_ = 255;
			isPreEnd_ = true;
		}
		break;
	case STATE::FADE_IN:
		alpha_ -= SPEED_ALPHA;
		if (alpha_ < 0)
		{
			//�t�F�[�h�I��
			alpha_ = 0;
			isPreEnd_ = true;
		}
		break;

	default:
		return;
	}

}

//�`�揈��
void Fader::Draw(void)
{
	switch (state_)
	{
	case STATE::NONE:
		break;
	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha_));
		DrawBox(
			0, 0
			, Application::SCREEN_SIZE_X
			, Application::SCREEN_SIZE_Y
			, 0x000000
			, true
		);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;

	}


}

//�t�F�[�h��Ԃ̃Q�b�^
Fader::STATE Fader::GetState(void)
{
	return state_;
}

//�t�F�[�h��Ԃ��I��������ǂ���
bool Fader::IsEnd(void)
{
	return isEnd_;
}

//�t�F�[�h�̃Z�b�^
void Fader::SetFade(STATE state)
{
	state_ = state;
	if (state_ != STATE::NONE)
	{
		isPreEnd_ = false;
		isEnd_ = false;
	}
	//�t�F�[�h�C���̎��̏�����ǉ�
	if (state_ == STATE::FADE_IN)
	{
		alpha_ = 255;
	}
	else if (state_ == STATE::FADE_OUT)
	{
		alpha_ = 0;
	}
}