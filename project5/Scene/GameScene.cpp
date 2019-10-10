#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	TRACE("¹Þ°Ñ¼°Ý‚Ì¶¬\n");
	TRACE("¡‚Ì¼°Ý‚Í");
	lpImageMng.GetID("·¬×", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("’e", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("“G”š”­", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("·¬×”š”­", "image/pl_blast.png", { 64,64 }, { 4,1 });


	obj.resize(1);
	obj[0] = new Player({ 190,100 }, { 0,0 });
	//obj[1] = new Enemy();




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

