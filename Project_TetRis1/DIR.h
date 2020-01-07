#pragma once

// ÌÞÛ¯¸‚ÌŒü‚«
enum class DIR
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	MAX
};

DIR begin(DIR);
DIR end(DIR);
DIR operator*(DIR dir);
DIR operator++(DIR& dir);