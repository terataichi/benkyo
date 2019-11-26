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
	_unitID = UNIT_ID::PLAYER;
	_pos = pos;
	_size = size;
	init();
}

void Player::Update(sharedObj obj)
{
	// 死んでたら処理をしない
	if (DestroyPrpc())
	{
		return;
	}

	(*_input).Update();												// ｷｰ情報の更新

	// らむだしき練習
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

	// ﾄﾘｶﾞｰ処理と押したら弾を出す
	if ((*_input).State(INPUT_ID::BTN_1).first && !(*_input).State(INPUT_ID::BTN_1).second)
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


	_input = std::make_shared<KeyState>();
	// ﾒｿｯﾄを使うやり方
	//_input.reset(new KeyState());

	state(STATE::NORMAL);
}
