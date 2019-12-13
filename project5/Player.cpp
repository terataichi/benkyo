#include <DxLib.h>
#include "Player.h"
#include <ImageMng.h>
#include <SoundMng.h>
#include <Input\KeyState.h>
#include <Input\InputState.h>
#include <Obj.h>
#include "Scene\SceneMng.h"
#include "Scene\BaseScene.h"

Player::Player()
{
	_zOder = 0;
	init();
}

Player::Player(Vector2dbl pos, Vector2dbl size)
{
	_unitID = UNIT_ID::PLAYER;
	_pos = pos;
	_size = size;
	_zOder = 0;
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

	// 移動
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

	_glowID[0] = MakeScreen(_size.x + 30, _size.y + 32);

	// ﾒｿｯﾄを使うやり方
	//_input.reset(new KeyState());

	state(STATE::NORMAL);
}

void Player::Draw(void)
{
	Obj::Draw();

	SetDrawScreen(_glowID[0]);
	ClsDrawScreen();				// 一回ﾘｾｯﾄ
	SetDrawBright(0, 200 + rand() % 55, 0);
	DrawRotaGraph(static_cast<int>(_size.x), static_cast<int>(_size.y), 1.25, 0, _animMap[_state][_animFrame].first, true);
	SetDrawBright(255, 255, 255);
	GraphFilter(_glowID[0], DX_GRAPH_FILTER_GAUSS, 5, 500);
	lpSceneMng.AddDrawQue({ _glowID[0],lpSceneMng.GameScreenOffset.x + _pos.x,lpSceneMng.GameScreenOffset.y + _pos.y,_rad,_zOder - 1,LAYER::CHAR,DX_BLENDMODE_ADD,255 });
}
