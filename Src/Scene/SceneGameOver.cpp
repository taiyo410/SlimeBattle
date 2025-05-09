#include<DxLib.h>
#include"../Application.h"
#include"../Manager/InputManager.h"
#include"../Manager/SceneManager.h"
#include"../Scene/SceneGameOver.h"
bool SceneGameOver::Init(void)
{
	return true;
}
//�X�V����
void SceneGameOver::Update(void)
{
	if (InputManager::GetInput().IsKeyPush(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
	}
}
//�`�揈��
void SceneGameOver::Draw(void)
{
	DrawDebug();
	//DrawRotaGraph(
	//	Application::SCREEN_SIZE_X / 2
	//	, Application::SCREEN_SIZE_Y / 2
	//	, 1.3
	//	, 0.0
	//	, bgImage_
	//	, true
	//	, false
	//	, false);

}
//�������
bool SceneGameOver::Release(void)
{
	//InputManager::GetInput().Destroy();
	return true;
}

/// <summary>
/// �f�o�b�O�p�֐�
/// </summary>
/// <param name=""></param>
void SceneGameOver::DrawDebug(void)
{
	DrawString(0, 0, "�Q�[���I�[�o�[�V�[���`��", 0xffffff);
	DrawBox(50
		, 50
		, Application::SCREEN_SIZE_X - 50
		, Application::SCREEN_SIZE_Y - 50
		, 0xff00ff
		, true);
}

