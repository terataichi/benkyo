#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>


GameScene::GameScene()
{
	TRACE("¹Þ°Ñ¼°Ý‚Ì¶¬\n");
	TRACE("¡‚Ì¼°Ý‚Í");
	lpImageMng.GetID("¹Þ°Ñ‰æ–Ê", "image/gameBG.png", { 640,464 }, { 1, 1 });
	lpImageMng.GetID("tama", "image/char.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("tekibakuha", "image/char.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("plbakuha", "image/char.png", { 64,64 }, { 4,1 });

	obj.resize(2);
	/*obj[0] = new Obj("image/char.png", { 0, 0 }, 10, 10, 30, 32);
	obj[1] = new Obj("image/char.png", { 100, 100 }, 10, 10, 30, 32);*/

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	
	for (auto data : obj)
	{
		data->Draw();
	}
	
	return std::move(own);
}

