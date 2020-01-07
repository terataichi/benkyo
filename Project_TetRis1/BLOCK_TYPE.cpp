#include <type_traits>
#include "BLOCK_TYPE.h"


BLOCK_TYPE bigin(BLOCK_TYPE)
{
	return BLOCK_TYPE::I;
}

BLOCK_TYPE end(BLOCK_TYPE)
{
	return BLOCK_TYPE::MAX;
}

BLOCK_TYPE rand(BLOCK_TYPE)
{
	return static_cast<BLOCK_TYPE>(std::underlying_type<BLOCK_TYPE>::type(rand() % (int)BLOCK_TYPE::MAX));
}

BLOCK_TYPE operator*(BLOCK_TYPE type)
{
	return type;
}

BLOCK_TYPE operator++(BLOCK_TYPE & type)
{
	return type = static_cast<BLOCK_TYPE>(std::underlying_type<BLOCK_TYPE>::type(type) + 1);
}
