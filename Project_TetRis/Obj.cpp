#include <DxLib.h>
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include "Obj.h"

Obj::Obj()
{
}

void Obj::Update(void)
{

}

void Obj::Draw(void)
{
	lpSceneMng.AddDrawQue({ lpImageMng.GetID("�ްщ��")[0],0,0 });
}

Obj::~Obj()
{
}
