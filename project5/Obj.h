#pragma once
#include <string>
#include <map>
#include <vector>
#include <Vector2.h>

using AnimVector = std::vector<std::pair<int, unsigned int>>;

class Obj
{
public:
	Obj();
	void Update(void);
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool animKey(const std::string key);						// ±ÆÒ·°‚Ìİ’è
	const std::string animKey(void) const;

	bool SetAnim(const std::string key, AnimVector& data);		// ±ÆÒ°¼®İdata‚Ì“o˜^
private:

	std::map<std::string, AnimVector> _animMap;					// ±ÆÒ°¼®İŠi”[
	std::string _animKey;										// ±ÆÒ°¼®İ—pƒL[
	unsigned int _animFrame;									// ±ÆÒ°¼®İ—pÌÚ°Ñ
	unsigned int _animCount;									// ±ÆÒ°¼®İ—p¶³İÄ

	Vector2 _pos;
};

