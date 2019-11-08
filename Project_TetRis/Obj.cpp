#include <DxLib.h>
#include <Scene\SceneMng.h>
#include <ImageMng.h>
#include "Obj.h"



Obj::Obj()
{
	// ������
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
}

void Obj::Draw(void)
{
	// �`��p�̏���QUE�Ɏ�
	lpSceneMng.AddDrawQue({ ,_pos.x,_pos.y,{_rect.x,_rect.y},{_size.x,_size.y} });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,_pos.x,_pos.y,{_rect.x,_rect.y},{_size.x,_size.y} });
}

Obj::~Obj()
{
}