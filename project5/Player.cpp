#include <DxLib.h>
#include "ImageMng.h"
#include "Player.h"
#include <Input\KeyState.h>
#include <Input\InputState.h>
#include <Obj.h>
#include "Scene\SceneMng.h"
#include "Scene\BaseScene.h"

Player::Player()
{
	init();
}

Player::Player(Vector2dbl pos, Vector2dbl size)
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

	(*_input).Update();												// ·°î•ñ‚ÌXV

	// ‚ç‚Ş‚¾‚µ‚«—ûK
	auto move = [](std::weak_ptr<InputState> keyData,const INPUT_ID id, double& pNum, const int speed)
	{
		if (!keyData.expired())
		{
			if ((*keyData.lock()).State(id).first)
			{
				pNum += speed;
			}
		}
	};

	move(_input, INPUT_ID::DOWN, _pos.y, +2);
	move(_input, INPUT_ID::UP, _pos.y, -2);
	move(_input, INPUT_ID::LEFT, _pos.x, -2);
	move(_input, INPUT_ID::RIGHT, _pos.x, +2);

	if ((*_input).State(INPUT_ID::BTN_1).first == true)
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
	}

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


	_input = std::make_shared<KeyState>();
	// Ò¿¯Ä‚ğg‚¤‚â‚è•û
	//_input.reset(new KeyState());

	state(STATE::NORMAL);
}
