#include <type_traits>
#include "LAYER.h"

LAYER begin(LAYER)
{
	return LAYER::BG;
}
LAYER end(LAYER)
{
	return LAYER::MAX;
}
LAYER operator*(LAYER key)
{
	return key;
}
LAYER operator++(LAYER & key)
{
	// ‹K’è‚ÌŒ^‚ð•Ô‚µ‚Ä‚­‚ê‚é
	// std::underlying_type<>::type()

	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1);
}
