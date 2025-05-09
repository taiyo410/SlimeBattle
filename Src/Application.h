#pragma once
#include<string>
class InputManager;
class Application
{
public:
	//�萔
	static constexpr int SCREEN_SIZE_X = 1200;
	static constexpr int SCREEN_SIZE_Y = 800;

	//static constexpr int SCREEN_SIZE_X = 1920;
	//static constexpr int SCREEN_SIZE_Y = 1080;


	static constexpr float FRAME_RATE = 1000 / 60;
#pragma region Path
	static const std::string PATH_MODEL;
	static const std::string PATH_IMAGE;
	static const std::string PATH_FONT;
	static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND;
#pragma endregion

	

	bool Init(void);		//����������
	void Run(void);			//�Q�[�����[�v����
	bool Release(void);		//�������

	//�V���O���g����
	static void CreateInstance(void);
	//�O���ŃC���X�^���X�𗘗p�\�Ƃ���
	static Application& GetInstance(void);

private:
#pragma region �V���O���g����
	//�C���X�^���X����
	InputManager* inputManager_;

	//�f�t�H���g�R���X�g���N�^
	Application(void);
	//�f�X�g���N�^
	~Application(void);

	//�R�s�[�R���X�g���N�^�𗘗p�s�ɂ���
	Application(const Application& ins);

	//�C���X�^���X�̍폜
	void Destroy(void);

	//�ÓI�ȃC���X�^���X������
	static Application* instance_;
#pragma endregion
	int currentTime_;			//���݂̎���
	int lastFrameTime_;			//�O��̃t���[�����s�̎���

	int frameCnt_;				//�t���[���J�E���g�p
	int updateFrameRateTime_;	//�t���[�����[�g���X�V��������

	float frameRate_;			//�t���[�����[�g(�\���p)

	//�t���[�����[�g�v�Z
	void CalcFrameRate(void);

	//�t���[�����[�g�\���i�f�o�b�O�p�j
	void DrawFrameRate(void);


	
};
