//#pragma once
#include"./SceneBase.h"
class InputManager;
class SceneGameOver :public SceneBase
{
public:
	////�����o�[�֐�
	//	//------------------------

	//	//�f�t�H���g�R���X�g���N�^
	//SceneGame(void);

	////�f�X�g���N�^
	//~SceneGame(void);

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:����������	false:�������~�܂�</returns>
	bool Init(void) override;		

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name=""></param>
	void Update(void) override;		
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name=""></param>
	void Draw(void) override;		

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:����������	false:�������~�܂�</returns>
	bool Release(void) override;		

private:
	//�|�C���^�錾
	//--------------------------
	//���쐧��
	InputManager *inputManager_;
	//�����o�[�ϐ�
	//SceneManager* sceneManager_;
	int bgImage_;

	/// <summary>
	/// �f�o�b�O�p�֐�
	/// </summary>
	/// <param name=""></param>
	void DrawDebug(void);
};

