//---------------------------------------------------------
//�Q�[������FAGS�č�i
// ����	    :2316004 �䓌���z
//---------------------------------------------------------
#include <DxLib.h>
#include<crtdbg.h>
#include"Application.h"

//�ϐ���`
//--------------------------

//WinMain�֐�
//--------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application::CreateInstance();

	Application::GetInstance().Run();
	Application::GetInstance().Release();

	return 0;
}