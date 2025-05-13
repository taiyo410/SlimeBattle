#include<DxLib.h>
#include<EffekseerForDXLib.h>
#include"./InputManager.h"
#include"./ModelManager.h"
#include"../Application.h"
#include"../Common/Fade.h"
#include"./Camera.h"
#include"../Object/Grid.h"
#include"../Common/CommonData.h"
#include"../Scene/SceneTitle.h"
#include"../Scene/SceneGame.h"
#include"../Scene/SceneGameOver.h"
#include"../Scene/ResultScene.h"
#include"./SceneManager.h"


//instance_�̏���������
SceneManager* SceneManager::instance_ = nullptr;

//�f�t�H���g�R���X�g���N�^
SceneManager::SceneManager(void)
{
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::NONE;
	//�t�F�[�h�C���X�^���X����
	fader_ = new Fader();
	fader_->Init();
	isSceneChanging_ = false;

	//�t�F�[�h�C���X�^���X����
	fader_ = new Fader();
	fader_->Init();

	//�J�����C���X�^���X����
	camera_ = new Camera();
	camera_->Init();

	//�O���b�h�C���X�^���X����
	grid_ = new Grid();
	grid_->Init();

	scene_ = nullptr;

	//�f�[�^�C���X�^���X����
	CommonData::CreateData();

	//�C���X�^���X�����������Ȃ�
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;

	//�V�[���؂�ւ���Ԃ̏�����
	isSceneChanging_ = true;

	//�ΐ���
	type_ = TYPE::PVE;
}

//�f�X�g���N�^
SceneManager::~SceneManager(void)
{

}
//����������
bool SceneManager::Init(void)		
{
	Init3D();

	//�f�[�^�C���X�^���X����
	CommonData::CreateData();

	//�C���X�^���X�����������Ȃ�
	sceneID_ = SCENE_ID::NONE;
	waitSceneID_ = SCENE_ID::TITLE;

	ChangeScene(SCENE_ID::TITLE, false);

	//�^�C�g���V�[������t�F�[�h�C���ŕ\��
	fader_->SetFade(Fader::STATE::FADE_IN);

	return true;
}

/// <summary>
/// 3D�̏���������
/// </summary>
/// <param name=""></param>
void SceneManager::Init3D(void)
{
	//�w�i�F�ݒ�
	SetBackgroundColor(BG_COLOR_R, BG_COLOR_G, BG_COLOR_B);

	//Z�o�b�t�@��L���ɂ���)
	SetUseZBuffer3D(true);

	//Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	//3D�o�b�N�J�����O�L���ɂ���
	SetUseBackCulling(true);
}
//�X�V����
void SceneManager::Update(void)
{
	//�t�F�[�h����
	fader_->Update();
	//�t�F�[�h��
	if (isSceneChanging_ == true)
	{
		Fade();
	}
	else
	{
 		scene_->Update();
		camera_->Update();
	}
	UpdateEffekseer3D();

	////�O���b�h�̍X�V����
	grid_->Update();
}
//�`�揈��
void SceneManager::Draw(void)
{
	//�`���O���t�B�b�N�̈�̎w��
	// (3D�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʂ�������
	ClearDrawScreen();

	//�J�����ݒ�
	camera_->SetBeforeDraw();
	

	//�e�V�[���̕`�揈��
	scene_->Draw();

	//�J�����f�o�b�O��
	camera_->Draw();

	//Effekseer�ɂ��Đ����̃G�t�F�N�g�`��
	DrawEffekseer3D();

	//�t�F�[�h
	fader_->Draw();

	

}
//�������
bool SceneManager::Release(void)		
{
	//�V�[���̊J������
	ReleaseScene(sceneID_);

	//�f�[�^�̉������
	CommonData::GetData().Destroy();

	grid_->Release();
	delete grid_;
	grid_ = nullptr;

	camera_->Release();
	delete camera_;
	camera_ = nullptr;

	delete fader_;
	fader_ = nullptr;	
	return true;
}


//�V�[���؂�ւ�
void SceneManager::ChangeScene(SCENE_ID nextID, bool isToFade)
{
	waitSceneID_ = nextID;
	if (isToFade)
	{
		fader_->SetFade(Fader::STATE::FADE_OUT);
		isSceneChanging_ = true;
	}
	else
	{
		DoChangeScene();
	}
}
//�V�[����؂�ւ���
void SceneManager::DoChangeScene(void)
{
	//���݂̃V�[���̊J��
	ReleaseScene(sceneID_);

		//���Ɉړ�����V�[���������Ă�
		sceneID_ = waitSceneID_;
	switch (sceneID_)
	{
	case SCENE_ID::TITLE:
		scene_ = new SceneTitle();
		break;
	case SCENE_ID::GAME:
		camera_->SetCameraWork(GAME_CAMERA_POS, GAME_CAMERA_ANGLE);
		scene_ = new SceneGame();
		break;
	case SCENE_ID::RESULT:
		camera_->SetCameraWork(TITLE_CAMERA_POS, TITLE_CAMERA_ANGLE);
		scene_ = new ResultScene();
	default:
		break;
	}
	scene_->Init();

	//�V�[���̑J�ڂ��I�������̂ŁA���̃V�[�����N���A����
	waitSceneID_ = SCENE_ID::NONE;
}

//�t�F�[�h���{�p�֐�
void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			//�Ó]��V�[���ύX
			DoChangeScene();
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			//���]��A�V�[���J�ڏI��
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	}
}

//�V�[���̉��
void SceneManager::ReleaseScene(SCENE_ID isceneID)
{
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
		scene_ = nullptr;
	}
}
//�V���O���g����
//--------------------------------
void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}
//�O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂ɃC���X�^���X�ŕԂ��֐���p��
SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Destroy(void)
{
	delete instance_;		//�C���X�^���X�폜
	instance_ = nullptr;	//�C���X�^���X�̈��������
}

//�ΐ���
bool SceneManager::GetType(TYPE value)
{
	if (type_ == value)
	{
		return true;
	}
	return false;
}

Camera* SceneManager::GetCamera(void)
{
	return camera_;
}
