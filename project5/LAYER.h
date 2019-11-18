#pragma once


// ID‚Ì¬‚³‚¢‚Ù‚¤‚ª‰œ‚É•`‰æ
enum class LAYER
{
	BG,
	CHAR,
	UI,
	MAX,
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER key);
LAYER operator++(LAYER& key);