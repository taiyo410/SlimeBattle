//---------------------------------------------------------
//ゲーム制作：AGS夏作品
// 氏名	    :2316004 井東太陽
//---------------------------------------------------------
#include <DxLib.h>
#include<crtdbg.h>
#include"Application.h"

//変数定義
//--------------------------

//WinMain関数
//--------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application::CreateInstance();

	Application::GetInstance().Run();
	Application::GetInstance().Release();

	return 0;
}