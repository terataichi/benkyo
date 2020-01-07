#include <type_traits>
#include "DIR.h"


DIR begin(DIR)
{
	return DIR::UP;
}
DIR end(DIR)
{
	return DIR::MAX;
}
DIR operator*(DIR dir)
{
	return dir;
}
DIR operator++(DIR & dir)
{
	// �K��̌^��Ԃ��Ă����
	// std::underlying_type<>::type()

	return dir = static_cast<DIR>(std::underlying_type<DIR>::type(dir) + 1);
}