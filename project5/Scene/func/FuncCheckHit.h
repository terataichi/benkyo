#pragma once
#include "../BaseScene.h"
#include <vector>
#include "../../common/Vector2.h"

// “–‚½‚è”»’è
struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	int _posLength;			// µÌŞ¼Şª¸Ä‚ÌÀ•W‚Ì‹——£
	int _sizeLength;		// µÌŞ¼Şª¸Ä‚Ì»²½Ş‚Ì‹——£
};

