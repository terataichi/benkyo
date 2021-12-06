#include "MapChip.h"
#include "_Debug/_DebugConOut.h"
#include "_Debug/_DebugDispOut.h"
#include "Obj.h"
#include "Scene/SceneMng.h"
#include "common/ImageMng.h"

std::unique_ptr <MapChip, MapChip::MapChipDeleter> MapChip::_sInstance(new MapChip());

void MapChip::InitMap(void)
{
	_mapData.resize(CHIP_MAX_Y);

	for (int y = 0; y < CHIP_MAX_Y; y++)
	{
		_mapData[y].resize(CHIP_MAX_X);

		for (int x = 0; x < CHIP_MAX_X; x++)
		{
			if (x <= 1 || x >= CHIP_MAX_X - 2 || y >= CHIP_MAX_Y - 2)
			{
				_mapData[y][x] = -1 ;
			}
			else
			{
				_mapData[y][x] = 0;
			}
		}
	}
}

void MapChip::WriteMap(Vector2& pos, BlockMap& blockData, DIR dir)
{
	_chip = pos / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockData[dir][y][x] != 0)
			{
				_mapData[_chip.y + y][_chip.x + x] = blockData[dir][y][x];
			}
		}
	}
}

void MapChip::DeleteLine(void)
{
	// ﾏｯﾌﾟﾃﾞｰﾀを削除
	for (int x = 2; x < CHIP_MAX_X - 2; x++)
	{
		_mapData[_delChipY][x] = 0;
	}

	for (int y = _delChipY; y > 1; y--)
	{
		for (int x = 2; x < CHIP_MAX_X - 2; x++)
		{
			_mapData[y][x] = _mapData[y - 1][x];
		}
	}
}

bool MapChip::CheckLine(void)
{
	int lineCount;		// ﾗｲﾝがそろっているか数える

	for (int y = 0; y < CHIP_MAX_Y - 2; y++)
	{
		lineCount = 0;
		for (int x = 2; x < CHIP_MAX_X - 2; x++)
		{
			if (_mapData[y][x] != 0 && _mapData[y][x] != -1)
			{
				lineCount++;
				if (lineCount >= ONE_LINE)
				{
					_delChipY = y;
					return true;
				}
			}
		}
	}
	return false;
}

bool MapChip::CheckMove(Vector2& pos, INPUT_ID id, BlockMap& blockData , DIR dir)
{
	_chip = pos / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	switch (id)
	{
	case INPUT_ID::LEFT:
		_chip.x -= 1;
		break;
	case INPUT_ID::DOWN:
		_chip.y += 1;
		break;
	case INPUT_ID::RIGHT:
		_chip.x += 1;
		break;
	case INPUT_ID::UP:
		break;
	default:
		AST();
		_chip.x = 0;
		_chip.y = 0;
		break;
	}

	// 範囲外ｱｸｾｽ回避
	if (_chip.x < 0)
	{
		return false;
	}
	if (_chip.x > CHIP_MAX_X)
	{
		_chip.x = CHIP_MAX_X - 1;
	}
	if (_chip.y > CHIP_MAX_Y)
	{
		_chip.y = CHIP_MAX_Y - 1;
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockData[dir][y][x] != 0)
			{
				if (_mapData[_chip.y + y][_chip.x + x] != 0)
				{
					// 動けないようにする
					return false;
				}
			}
		}
	}
	return true;
}

bool MapChip::CheckDown(Vector2 & pos, BlockMap & blockData, DIR dir)
{
	_chip = pos / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	_chip.y += 1;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockData[dir][y][x] != 0)
			{
				if (_mapData[_chip.y + y][_chip.x + x] != 0)
				{
					// 終了
					return true;
				}
			}
		}
	}
	return false;
}

bool MapChip::CheckRota(Vector2 & pos, BlockMap & blockData, DIR dir)
{
	_chip = pos / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	// 回転先がほかのブロックと被っていないかを見る
	++dir;
	if (dir >= DIR::MAX)
	{
		dir = begin(DIR());
	}

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockData[dir][y][x] != 0)
			{
				if ((_mapData[_chip.y + y][_chip.x + x] != 0)&& (_mapData[_chip.y + y][_chip.x + x] != -1))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool MapChip::CheckGameOver(void)
{
	_chip = Vector2{ BLOCK_SIZE * 4,0 } / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (_mapData[_chip.y + y][_chip.x + x] != 0)
			{
				return true;
			}
		}
	}
	return false;
}

void MapChip::GameDraw(void)
{
	for (int y = 0; y < CHIP_MAX_Y - 2; y++)
	{
		for (int x = 2; x < CHIP_MAX_X - 2; x++)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("ﾏｯﾌﾟ")[0],
									lpSceneMng.GameScreenOffset.x + BLOCK_SIZE * x,lpSceneMng.GameScreenOffset.y + BLOCK_SIZE * y,
									-BLOCK_SIZE + (BLOCK_SIZE * _mapData[y][x]),415,
									BLOCK_SIZE,BLOCK_SIZE,
									50000,
									LAYER::CHAR });
		}
	}
}

void MapChip::GemeOverDraw(void)
{
	for (int y = 0; y < CHIP_MAX_Y - 2; y++)
	{
		for (int x = 2; x < CHIP_MAX_X - 2; x++)
		{
			if (_mapData[y][x] != 0)
			{
				lpSceneMng.AddDrawQue({ IMAGE_ID("ﾏｯﾌﾟ")[0],
										lpSceneMng.GameScreenOffset.x + BLOCK_SIZE * x,lpSceneMng.GameScreenOffset.y + BLOCK_SIZE * y,
										-BLOCK_SIZE + (BLOCK_SIZE * 8),415,
										BLOCK_SIZE,BLOCK_SIZE,
										50000,
										LAYER::CHAR });
			}
		}
	}
}

Vector2 MapChip::OutFix(Vector2 & pos, BlockMap & blockData, DIR dir)
{
	_chip = pos / Vector2{ BLOCK_SIZE, BLOCK_SIZE };

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (blockData[dir][y][x] != 0)
			{
				if (_mapData[_chip.y + y][_chip.x + x] == -1 && pos.x <= BLOCK_SIZE * 2)
				{
					pos.x += BLOCK_SIZE;
				}
				if (_mapData[_chip.y + y][_chip.x + x] == -1 && pos.x + (BLOCK_SIZE * 4) >= BLOCK_SIZE * 12)
				{
					pos.x -= BLOCK_SIZE;
				}
				if ((_mapData[_chip.y + y][_chip.x + x] == -1) && pos.y + (BLOCK_SIZE * 4) >= BLOCK_SIZE * 22)
				{
					pos.y -= BLOCK_SIZE;
				}
			}
		}
	}
	return pos;
}

MapChip::MapChip()
{
}


MapChip::~MapChip()
{
}
