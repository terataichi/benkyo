#include "Bullet.h"
#include "ImageMng.h"
#include "Scene\SceneMng.h"
#include <SoundMng.h>

Bullet::Bullet()
{
	lpSceneMng.AddSoundQue({ SOUND_ID("弾")[0],true });

	Init();
}

Bullet::Bullet(UNIT_ID unitID ,Vector2dbl pos)
{
	lpSceneMng.AddSoundQue({ SOUND_ID("弾")[0],true });
	_unitID = unitID;
	_zOder = 0;
	_pos = pos;
	_size = { 8,3 };
	_rad = (PI * 270) / 180.0;
	Init();
}

void Bullet::Update(sharedObj obj)
{
	// 弾が死んでたら処理しない
	if (DestroyPrpc())
	{
		return;
	}

	// 当たり判定するよ
	lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT , *this });

	// 移動
	_pos.x = 5 * std::cos(_rad) + _pos.x;
	_pos.y = 5 * std::sin(_rad) + _pos.y;

	// 画面外に出たら弾を消す
	if (_pos.y < -_size.y / 2 || _pos.y >(lpSceneMng.GameScreenSize.y + _size.y / 2))
	{
		SetAlive(false);
	}
}

Bullet::~Bullet()
{
	
}

void Bullet::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back(IMAGE_ID("弾")[0] , 30);
	SetAnim(STATE::NORMAL, data);

	// プレイヤー死んだときに何も表示したくない
	data.reserve(1);
	data.emplace_back(-1, 40);				// -1はDxLibのLoadGraphの返り値に合わせてる
	SetAnim(STATE::DETH, data);
}
