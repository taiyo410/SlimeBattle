#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./Manager/InputManager.h"
#include"./Manager/EffectManager.h"
#include"Application.h"
#include"./Manager/SceneManager.h"


//�V���O���g����
//------------------------------------
//�C���X�^���X�̏���������
Application* Application::instance_ = nullptr;

const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_SOUND = "Data/Sound/";

//�f�t�H���g�R���X�g���N�^
Application::Application(void)
{

}

//�f�X�g���N�^
Application::~Application(void)
{

}

//����������
bool Application::Init(void)
{

	//�V�X�e������
	SetWindowText("2316004 �䓌���z");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);		//�Q�[���E�B���h�E�̕\�����@

	if (DxLib_Init() == -1)
	{
		OutputDebugString("DxLib�̏��������s");
		return false;
	}
	currentTime_ = 0;			
	lastFrameTime_ = 0;			

	frameCnt_;				
	updateFrameRateTime_ = 0;	

	frameRate_ = 0;			

	//���쐧��C���X�^���X����
	InputManager::CreateInput();

	//Effekseer�̏�����
	EffectManager::CreateEffect();


	//�C���X�^���X�𐶐�
	SceneManager::CreateInstance();

	return true;
}

//�Q�[�����[�v����
void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Sleep(1);	//�V�X�e���ɏ�����Ԃ�

		//���݂̎������擾
		currentTime_ = GetNowCount();
		//1/60�b�o�߂��Ă����珈�������s����
		if (currentTime_ - lastFrameTime_ >= FRAME_RATE)
		{
			//�t���[�����s���̎��Ԃ��X�V
			lastFrameTime_ = currentTime_;

			//�t���[�������J�E���g
			frameCnt_++;

			//�Q�[���̃��C������
		//---------------------------------

		//�`�揈��
		//-------------------------------
		//�`�悷���ʂ𗠂̉�ʂɐݒ�
			SetDrawScreen(DX_SCREEN_BACK);

			//�`�悷���ʂ̓��e������
			ClearDrawScreen();

			SceneManager::GetInstance().Draw();	//�e�V�[���̕`�揈�����Ăяo��

			InputManager::GetInput().StepInput();			//���̓X�e�b�v
			InputManager::GetInput().StepPadInput();
			EffectManager::GetEffect().Update();
			SceneManager::GetInstance().Update();

			//�t���[�����[�g�v�Z
			CalcFrameRate();

			//�t���[�����[�g�\���i�f�o�b�O�p�j
			//DrawFrameRate();

			ScreenFlip();						//���̉�ʂ�\�̉�ʂɏu�ԃR�s�[
		}
		
	}
}

//�������
bool Application::Release(void)
{
	//�Ǘ��}�l�[�W���̉������
	//�V�[���Ǘ��p
	SceneManager::GetInstance().Release();

	//����}�l�[�W���̊J��
	InputManager::GetInput().Destroy();

	//Effekseer���I������
	Effkseer_End();

	//�V���O���g����
	Destroy();

	

	//�V�X�e���I������
	//----------------------------------
	DxLib_End();	//DX���C�u�����̏I��
	return true;
}

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

//�C���X�^���X�̃Q�b�^
Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Destroy(void)
{
	delete instance_;		//�C���X�^���X�폜
	instance_ = nullptr;	//�C���X�^���X�̈��������
}

void Application::CalcFrameRate(void)
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int nDifTime = currentTime_ - updateFrameRateTime_;
	//�O��̃t���[�����[�g�X�V����
	//1�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if (nDifTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�����̂�float�ɃL���X�g
		float fFrameCnt = static_cast<float>(frameCnt_ * 1000);

		//�t���[�����[�g�����߂�
		//���z�ʂ�Ȃ�60000 / 1000��60�ƂȂ�
		frameRate_ = fFrameCnt / nDifTime;

		//�t���[���J�E���g���N���A
		frameCnt_ = 0;

		//�t���[�����[�g�X�V���Ԃ��X�V
		updateFrameRateTime_ = currentTime_;
	}
}

void Application::DrawFrameRate(void)
{
	DrawFormatString(SCREEN_SIZE_X - 90, 0, GetColor(255, 30, 30), "FPS[%.2f]", frameRate_);
}
