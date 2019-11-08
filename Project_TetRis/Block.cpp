#include "Block.h"



Block::Block()
{
}

// 引数付きコンストラクタ
Block::Block(BlockState state)
{
	_type = std::get<static_cast<int>(BLOCK_STATE::TYPE)>(state);
	_pos = std::get<static_cast<int>(BLOCK_STATE::VECTOR)>(state);
	_rect = std::get<static_cast<int>(BLOCK_STATE::RECT)>(state);
	_size = std::get<static_cast<int>(BLOCK_STATE::SIZE)>(state);

}


Block::~Block()
{
}

void Block::Update(void)
{
}

void Block::init(void)
{
}
