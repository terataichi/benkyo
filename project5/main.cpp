#include <Dxlib.h>		// Dxlibײ���؂��g�p����
#include <iostream>
#include <Scene\SceneMng.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//SceneMng sceneMng;
	//sceneMng.Run();

	SceneMng::Create();
	SceneMng::GetInstance().Run();
	SceneMng::Destroy;
	
	return 0;

}