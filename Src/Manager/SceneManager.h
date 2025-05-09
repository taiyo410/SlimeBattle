//#pragma once
#include<DxLib.h>
#include"../Common/CommonData.h"
//�O���錾
class Fader;
class InputManager;
class ModelManager;
class SceneBase;
class CommonData;
class SceneTitle;
class SceneGame;
class Camera;
class Grid;

class SceneManager
{

public:
	//�����o�[�֐�
	//�񋓌^
	enum class SCENE_ID
	{
		NONE		//���ݒ�
		,TITLE		//�^�C�g��
		,GAME		//�Q�[��
		,GAMEOVER	//�Q�[���I�[�o�[
		,RESULT
		,MAX
	};

	//�G�������
	enum class TYPE
	{
		PVP
		,PVE
	};
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�������s		false:������~</returns>
	bool Init(void);		

	/// <summary>
	/// 3D�̏���������
	/// </summary>
	/// <param name=""></param>
	void Init3D(void);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void);		

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	void Draw(void);		

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:�������s		false:������~</returns>
	bool Release(void);		//�������

	/// <summary>
	/// �V�[���J�ڗp�֐�
	/// </summary>
	/// <param name="nextID">���̃V�[���̐ݒ�</param>
	/// <param name="isToFade">true:�t�F�[�h����	false:�t�F�[�h���Ȃ�</param>
	void ChangeScene(SCENE_ID nextID, bool isToFade);

	//�V���O���g����
	//--------------------------------
	static void CreateInstance(void);
	//�O���ŃC���X�^���X�𗘗p�\�Ƃ��邽�߂ɃC���X�^���X�ŕԂ��֐���p��
	static SceneManager& GetInstance(void);

	//�ΐ���
	bool GetType(TYPE value);

	//�J�����̃C���X�^���X��Ԃ�
	Camera* GetCamera(void);

private:
	//�����o�[�ϐ�
	SCENE_ID sceneID_;		//���̃V�[���i�[
	SCENE_ID waitSceneID_;	//���̃V�[���i�[

	bool isSceneChanging_;	//�V�[���J�ڒ����ǂ����itrue:�J�ڒ��j
	//�Ǘ��}�l�[�W��
	SceneBase* scene_;		//�V�[���C���X�^���X
	SceneTitle* title_;		//�^�C�g��
	SceneGame* game_;       //�Q�[��

	InputManager* inputManager_;	//���쐧��C���X�^���X
	CommonData* data_;
	Fader* fader_;					//�t�F�[�h�C���X�^���X
	Camera* camera_;				//�J�����C���X�^���X
	Grid* grid_;					//�O���b�h�C���X�^���X
	ModelManager* model_;			//���f���C���X�^���X
	//�����o�[�ϐ�
	//�ΐ���
	TYPE type_;
	CommonData::MODE mode_;

	//BGM�i�[
	VECTOR cameraPos_;		//�J�������W
	VECTOR cameraAngle_;		//�J�����p�x
	
	
	
	
	/// <summary>
	/// �V�[���؂�ւ�
	/// </summary>
	/// <param name=""></param>
	void DoChangeScene(void);

	/// <summary>
	/// �t�F�[�h���{�p
	/// </summary>
	/// <param name=""></param>
	void Fade(void);

	/// <summary>
	/// �w��V�[���̊J��
	/// </summary>
	/// <param name="isceneID"></param>
	void ReleaseScene(SCENE_ID isceneID);

	//�V���O���g����
	//-------------------------------------
	//�f�t�H���g�R���X�g���N�^
	SceneManager(void);
	
	//�f�X�g���N�^
	~SceneManager(void);

	//�R�s�[�R���X�g���N�^�𗘗p�s�ɂ���
	SceneManager(const SceneManager& ins);

	/// <summary>
	/// �C���X�^���X�̍폜
	/// </summary>
	/// <param name=""></param>
	void Destroy(void);

	//�ÓI�ȃC���X�^���X������
	static SceneManager* instance_;
};

