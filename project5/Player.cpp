#include "ImageMng.h"
#include "Player.h"
#include <Obj.h>

Player::Player()
{
	init();
}

Player::Player(Vector2 pos, Vector2 size)
{
	_pos = pos;
	_size = size;
	init();
}


Player::~Player()
{

}

void Player::init(void)
{
	AnimVector data;
	data.reserve(2);
	data.emplace_back(IMAGE_ID("·¬×")[0], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("·¬×")[2], 90);
	SetAnim(STATE::EX, data);

	data.emplace_back(IMAGE_ID("·¬×”š”­")[0], 20);
	data.emplace_back(IMAGE_ID("·¬×”š”­")[1], 25);
	data.emplace_back(IMAGE_ID("·¬×”š”­")[2], 30);
	data.emplace_back(IMAGE_ID("·¬×”š”­")[3], 35);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH,data);

	state(STATE::NORMAL);
}
