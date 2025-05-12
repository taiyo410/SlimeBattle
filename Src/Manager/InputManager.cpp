#include <DxLib.h>
#include"./InputManager.h"

//�V���O���g����
//-----------------------------------
//input_�̏���������
InputManager* InputManager::input_ = nullptr;

//�f�t�H���g�R���X�g���N�^
InputManager::InputManager(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf_[index] = '\0';
		preKeyBuf_[index] = '\0';
	}
	//���͐���̏�����
	for (int n = 0; n < PAD_NUM; n++)
	{
		currentPadBuf_[n] = 0;
		prePadBuf_[n] = 0;
	}
}

//�f�X�g���N�^
InputManager::~InputManager(void)
{

}



//���͐��䏉����
void InputManager::InitInput(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf_[index] = '\0';
		preKeyBuf_[index] = '\0';
	}
	//���͐���̏�����
	for (int n = 0; n < PAD_NUM; n++)
	{
		currentPadBuf_[n] = 0;
		prePadBuf_[n] = 0;
	}
}

//���͐���X�e�b�v
//����Step����葁���Ă�
void InputManager::StepInput(void)
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
 		preKeyBuf_[index] = currentKeyBuf_[index];
	}

	//���݂̃L�[�����擾
	GetHitKeyStateAll(currentKeyBuf_);
}

//�P���ɉ�����Ă��邩
bool InputManager::IsKeyDown(int key_code)
{
	//���t���[���ŉ�����Ă���(�O�t���[���̏�Ԃ͊֌W�Ȃ�)
	if (currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//�������ꂽ����
bool InputManager::IsKeyPush(int key_code)
{
	//�O�t���[���ŉ�����ĂȂ��@���@���t���[���ŉ�����Ă���
	if (preKeyBuf_[key_code] == 0 && currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//����������
bool InputManager::IsKeyKeep(int key_code)
{
	//�O�t���[���ŉ�����Ă���@���@���t���[���ł�������Ă���
	if (preKeyBuf_[key_code] == 1 && currentKeyBuf_[key_code] == 1)
	{
		return true;
	}
	return false;
}

//�������ꂽ����
bool InputManager::IsKeyRelease(int key_code)
{
	//�O�t���[���ŉ�����Ă���@���@���t���[���ŉ�����Ă��Ȃ�
	if (preKeyBuf_[key_code] == 1 && currentKeyBuf_[key_code] == 0)
	{
		return true;
	}
	return false;
}

void InputManager::StepPadInput(void)
{
	//���݂̃R���g���[���[�ڑ���
	int padNumber = GetJoypadNum();
	for (int n = 0; n < PAD_NUM; n++)
	{
		//�O�t���[���̃L�[���ϐ��ɋL�����Ă���
		prePadBuf_[n] = currentPadBuf_[n];

		//�p�b�h������q�����ĂȂ��Ƃ�
		if (padNumber == 0)
		{
			//�z��0�ԖڂɃL�[�{�[�h�̌��݂̃L�[�����擾
			currentPadBuf_[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		}
		else
		{
			//���݂̃L�[�����擾
			currentPadBuf_[n] = GetJoypadInputState(n + 1);
		}
	}
}

bool InputManager::IsPadDown(int padNum, int key_code)
{
	//�R���g���[���[�̔ԍ����킹�p
	int padNumber;

	//�R���g���[���[�ƃL�[�{�[�h�p
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//�P�Ԃɍ��킹��
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//�z��p�ɐ��������킹��
		padNumber = padNum - 1;
	}
	//���t���[���ŉ�����Ă���(�O�t���[���̏�Ԃ͊֌W�Ȃ�)
	if ((currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}

bool InputManager::IsPadPush(int padNum, int key_code)
{
	//�R���g���[���[�̔ԍ����킹�p
	int padNumber;

	//�R���g���[���[�ƃL�[�{�[�h�p
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//�P�Ԃɍ��킹��
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//�z��p�ɐ��������킹��
		padNumber = padNum - 1;
	}
	//�O�t���[���ŉ�����ĂȂ��@���@���t���[���ŉ�����Ă���
	if ((prePadBuf_[padNumber]&key_code )== 0 && (currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}

bool InputManager::IsPadKeep(int padNum, int key_code)
{
	//�R���g���[���[�̔ԍ����킹�p
	int padNumber;

	//�R���g���[���[�ƃL�[�{�[�h�p
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//�P�Ԃɍ��킹��
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//�z��p�ɐ��������킹��
		padNumber = padNum - 1;
	}
	//�O�t���[���ŉ�����Ă�@���@���t���[���ŉ�����Ă�
	if ((prePadBuf_[padNumber] & key_code) != 0 && (currentPadBuf_[padNumber] & key_code) != 0)
	{
		return true;
	}
	return false;
}


bool InputManager::IsPadRelease(int padNum, int key_code)
{
	//�R���g���[���[�̔ԍ����킹�p
	int padNumber;

	//�R���g���[���[�ƃL�[�{�[�h�p
	if (padNum == DX_INPUT_KEY_PAD1)
	{
		//�P�Ԃɍ��킹��
		padNumber = DX_INPUT_PAD1 - 1;
	}
	else
	{
		//�z��p�ɐ��������킹��
		padNumber = padNum - 1;
	}
	//�O�t���[���ŉ�����Ă�@���@���t���[���ŉ�����ĂȂ�
	if ((prePadBuf_[padNumber] & key_code) != 0 && (currentPadBuf_[padNumber] & key_code) == 0)
	{
		return true;
	}
	return false;
}

//���쐧��C���X�^���X�̊J��
void InputManager::ReleaseInput(void)
{
	//�V���O���g����
	Destroy();
}

void InputManager::CreateInput(void)
{
	if (input_ == nullptr)
	{
		input_ = new InputManager();
	}
	input_->InitInput();
}

//�C���X�^���X���O���ɌĂяo����悤�ɂ���
InputManager& InputManager::GetInput(void)
{
	return *input_;
}

void InputManager::Destroy(void)
{
	delete input_;		//�C���X�^���X���폜
	input_ = nullptr;	//�C���X�^���X�̈��������
}