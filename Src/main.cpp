//---------------------------------------------------------
//�Q�[������FAGS�č�i
// ����	    :2316004 �䓌���z
//---------------------------------------------------------
#include <DxLib.h>
#include"Application.h"

//�ϐ���`
//--------------------------

//WinMain�֐�
//--------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application::CreateInstance();

	Application::GetInstance().Run();
	Application::GetInstance().Release();

	return 0;
}