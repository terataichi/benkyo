#pragma once

enum class BLOCK_TYPE
{
	//NON,
	I,
	O,
	T,
	J,
	L,
	S,
	Z,
	MAX
};

BLOCK_TYPE begin(BLOCK_TYPE);
BLOCK_TYPE end(BLOCK_TYPE);
BLOCK_TYPE rand(BLOCK_TYPE);
BLOCK_TYPE operator* (BLOCK_TYPE type);
BLOCK_TYPE operator++ (BLOCK_TYPE& type);
