#pragma once
#include <string>
#include <vector>
#include <Vector2.h>

class Obj
{
public:
	Obj();
	void Update(void);
	void Draw(void);
	virtual ~Obj();

private:
	Vector2 _pos;
};

