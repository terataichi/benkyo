#include <DxLib.h>
#include "ImageMng.h"
#include "Player.h"
#include <Input\KeyState.h>
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

void Player::Update(void)
{
	if (DestroyPrpc())
	{
		return;
	}

	(*_input).Update();												// ｷｰ情報の更新

	// らむだしき練習
	auto move = [](const int keyID, int& pNum, const int speed)
	{
		if (CheckHitKey(keyID))
		{
			pNum += speed;
		}
	};

	move(KEY_INPUT_DOWN, _pos.y, +2);
	move(KEY_INPUT_UP, _pos.y, -2);
	move(KEY_INPUT_LEFT, _pos.x, -2);
	move(KEY_INPUT_RIGHT, _pos.x, +2);

	

}


Player::~Player()
{

}

void Player::init(void)
{
	AnimVector data;

	data.reserve(2);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ")[2], 90);
	SetAnim(STATE::EX, data);

	data.emplace_back(IMAGE_ID("ｷｬﾗ爆発")[0], 20);
	data.emplace_back(IMAGE_ID("ｷｬﾗ爆発")[1], 25);
	data.emplace_back(IMAGE_ID("ｷｬﾗ爆発")[2], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ爆発")[3], 35);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH,data);


	_input = std::make_unique<KeyState>();
	// ﾒｿｯﾄを使うやり方
	//_input.reset(new KeyState());

	state(STATE::NORMAL);
}
