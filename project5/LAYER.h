#pragma once


// IDの小さいほうが奥に描画
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