#include "Block.h"
#include <DxLib.h>
#include <_DebugConOut.h>
#include <ImageMng.h>
#include <SceneMng.h>
#include <GameScene.h>
#include <Input/KeyState.h>
#include "DIR.h"
#include "MapChip.h"
#include <TitleScene.h>
#include <ScoreMng.h>

std::shared_ptr<InputState> Block::_input;

Block::Block()
{

}

Block::Block(BLOCK_TYPE type)
{
	_input = std::make_shared<KeyState>();
	_pos = { BLOCK_SIZE * 4,0 };
	_size = { 16 , 16 };
	_dir = DIR::UP;
	_state = ANIMSTATE::NORMAL;
	BlockInit(type);										// タイプによって形が違う
	Init(type);												// 初期化
	_endCount = 0;
	_moveCount = 60;
}


Block::~Block()
{
	TRACE("死にました");
}

void Block::Update()
{
	// 死んでたら処理をしない
	if (DestroyPrpc())
	{
		return;
	}

	(*_input).Update();												// ｷｰ情報の更新

	// ﾄﾘｶﾞｰ処理と押したら向きが変わる
	if ((*_input).State(INPUT_ID::BTN_1).first && !(*_input).State(INPUT_ID::BTN_1).second)
	{
		if (lpMapChip.CheckRota(_pos, _blockData, _dir))
		{
			++_dir;
			if (_dir >= DIR::MAX)
			{
				_dir = begin(DIR());
			}
			_pos = lpMapChip.OutFix(_pos, _blockData, _dir);
		}
	}

	// 移動処理
	auto move = [&](std::weak_ptr<InputState> keyData, const INPUT_ID id, int& pNum, const int speed)
	{
		if (!keyData.expired())
		{
			if (lpMapChip.CheckMove(_pos, id, _blockData, _dir))
			{
				if ((*keyData.lock()).State(id).first && !(*keyData.lock()).State(id).second)
				{
					if (id == INPUT_ID::UP)
					{
						// ﾊｰﾄﾞﾄﾞﾛｯﾌﾟにする
						_moveCount = 1;
					}
					pNum += speed;
				}
			}
		}
	};

	// 移動
	move(_input, INPUT_ID::LEFT, _pos.x, -BLOCK_SIZE);
	move(_input, INPUT_ID::RIGHT, _pos.x, BLOCK_SIZE);
	move(_input, INPUT_ID::DOWN, _pos.y, BLOCK_SIZE);
	move(_input, INPUT_ID::UP, _pos.y, BLOCK_SIZE);

	// 真で++
	if (lpMapChip.CheckDown(_pos, _blockData, _dir))
	{

		_endCount++;
	}

	// 次のブロックをｲﾝｽﾀﾝｽ
	if (_endCount >= _moveCount)
	{
		SetAlive(false);
		lpMapChip.WriteMap(_pos, _blockData, _dir);						// ﾏｯﾌﾟに書き込み

		if (!lpMapChip.CheckGameOver())
		{
			lpSceneMng.AddBlockInsQue({ rand(BLOCK_TYPE()), true });		// ｲﾝｽﾀﾝｽﾘｽﾄに追加
		}
	}

	// 勝手に下に進む
	if (lpMapChip.CheckMove(_pos, INPUT_ID::DOWN, _blockData, _dir))
	{
		if (lpSceneMng._gameCount % _moveCount == 0)
		{
			_pos.y += BLOCK_SIZE;
		}
	}
}

void Block::Init(BLOCK_TYPE type)
{
	AnimVector data;
	data.reserve(1);
	// ﾚｸﾄｸﾞﾗﾌとｱﾆﾒｰｼｮﾝの設定
	switch (type)
	{
	case BLOCK_TYPE::I:
		_upLeft = { 0 , 415 };
		data.emplace_back(IMAGE_ID("I")[0], 30);
		break;

	case BLOCK_TYPE::O:
		_upLeft = { BLOCK_SIZE * 1, 415 };
		data.emplace_back(IMAGE_ID("O")[0], 30);
		break;

	case BLOCK_TYPE::T:
		_upLeft = { BLOCK_SIZE * 2, 415 };
		data.emplace_back(IMAGE_ID("T")[0], 30);
		break;

	case BLOCK_TYPE::J:
		_upLeft = { BLOCK_SIZE * 3, 415 };
		data.emplace_back(IMAGE_ID("J")[0], 30);
		break;

	case BLOCK_TYPE::L:
		_upLeft = { BLOCK_SIZE * 4, 415 };
		data.emplace_back(IMAGE_ID("L")[0], 30);
		break;

	case BLOCK_TYPE::S:
		_upLeft = { BLOCK_SIZE * 5, 415 };
		data.emplace_back(IMAGE_ID("S")[0], 30);
		break;

	case BLOCK_TYPE::Z:
		_upLeft = { BLOCK_SIZE * 6, 415 };
		data.emplace_back(IMAGE_ID("Z")[0], 30);
		break;

	default:
		// 変なの入ってたらあさーと
		AST();
		_upLeft = { 0 , 415 };
		data.emplace_back(IMAGE_ID("I")[0], 30);
	}

	// ｱﾆﾒｰｼｮﾝの登録
	SetAnim(ANIMSTATE::NORMAL, data);
}

void Block::BlockInit(BLOCK_TYPE type)
{
	if (BLOCK_TYPE::I == type)
	{
		_blockData[DIR::UP] = { {0,0,1,0},
								{0,0,1,0},
								{0,0,1,0},
								{0,0,1,0} };

		_blockData[DIR::DOWN] ={{0,0,1,0},
								{0,0,1,0},
								{0,0,1,0},
								{0,0,1,0} };

		_blockData[DIR::LEFT] ={{0,0,0,0},
								{1,1,1,1},
								{0,0,0,0},
								{0,0,0,0} };

		_blockData[DIR::RIGHT] ={{0,0,0,0},
								 {1,1,1,1},
								 {0,0,0,0},
								 {0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::O == type)
	{
		_blockData[DIR::UP] = { {0,0,0,0},
								{0,2,2,0}, 
								{0,2,2,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,0,0,0},
								{0,2,2,0},
								{0,2,2,0},
								{0,0,0,0} };

		_blockData[DIR::LEFT] = { {0,0,0,0},
								{0,2,2,0},
								{0,2,2,0},
								{0,0,0,0} };

		_blockData[DIR::RIGHT] = { {0,0,0,0},
								{0,2,2,0},
								{0,2,2,0},
								{0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::T == type)
	{
		_blockData[DIR::UP] = { {0,3,0,0},
								{3,3,3,0},
								{0,0,0,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,0,0,0},
								 {3,3,3,0},
								 {0,3,0,0},
								 {0,0,0,0} };

		_blockData[DIR::LEFT] = {{0,3,0,0},
								 {3,3,0,0},
								 {0,3,0,0},
								 {0,0,0,0} };

		_blockData[DIR::RIGHT] = {{0,3,0,0},
								  {0,3,3,0},
								  {0,3,0,0},
								  {0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::J == type)
	{
		_blockData[DIR::UP] = { {0,0,4,0},
								{0,0,4,0},
								{0,4,4,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,4,4,0},
								 {0,4,0,0},
								 {0,4,0,0},
								 {0,0,0,0} };

		_blockData[DIR::LEFT] = {{0,0,0,0},
								 {4,4,4,0},
								 {0,0,4,0},
								 {0,0,0,0} };

		_blockData[DIR::RIGHT] = {{0,4,0,0},
								  {0,4,4,4},
								  {0,0,0,0},
								  {0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::L == type)
	{
		_blockData[DIR::UP] = { {0,5,0,0},
								{0,5,0,0},
								{0,5,5,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,5,5,0},
								 {0,0,5,0},
								 {0,0,5,0},
								 {0,0,0,0} };

		_blockData[DIR::LEFT] = {{0,0,5,0},
								 {5,5,5,0},
								 {0,0,0,0},
								 {0,0,0,0} };

		_blockData[DIR::RIGHT] = {{0,0,0,0},
								  {0,5,5,5},
								  {0,5,0,0},
								  {0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::S == type)
	{
		_blockData[DIR::UP] = { {0,6,0,0},
								{0,6,6,0},
								{0,0,6,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,6,0,0},
								 {0,6,6,0},
								 {0,0,6,0},
								 {0,0,0,0} };

		_blockData[DIR::LEFT] = {{0,0,0,0},
								 {0,6,6,0},
								 {6,6,0,0},
								 {0,0,0,0} };

		_blockData[DIR::RIGHT] = {{0,0,0,0},
								  {0,6,6,0},
								  {6,6,0,0},
								  {0,0,0,0} };

		return;
	}

	if (BLOCK_TYPE::Z == type)
	{
		_blockData[DIR::UP] = { {0,0,7,0},
								{0,7,7,0},
								{0,7,0,0},
								{0,0,0,0} };

		_blockData[DIR::DOWN] = {{0,0,7,0},
								 {0,7,7,0},
								 {0,7,0,0},
								 {0,0,0,0} };

		_blockData[DIR::LEFT] = {{0,0,0,0},
								 {7,7,0,0},
								 {0,7,7,0},
								 {0,0,0,0} };

		_blockData[DIR::RIGHT] = {{0,0,0,0},
								  {7,7,0,0},
								  {0,7,7,0},
								  {0,0,0,0} };
	}
}
