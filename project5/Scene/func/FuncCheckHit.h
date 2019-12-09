#pragma once
#include <Scene\BaseScene.h>
#include <vector>
#include <Vector2.h>

// “–‚½‚è”»’è
struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	int _posLength;			// µÌŞ¼Şª¸Ä‚ÌÀ•W‚Ì‹——£
	int _sizeLength;		// µÌŞ¼Şª¸Ä‚Ì»²½Ş‚Ì‹——£
};

