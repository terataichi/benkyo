#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>

#define PI 3.141592						// ‰~ü—¦

enum class STATE
{
	NORMAL,			// ’Êí
	EX,				// “Áêó‘Ô
	DETH,			// ”š”­ (€–S)
	MAX
};

class Obj;			// ÌßÛÄÀ²Ìß¾İ¹Şİ‚Ä‚«‚È
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);								// ±ÆÒ·°‚Ìİ’è
	const STATE state(void) const;								// •Ô‚·‚æ
	const Vector2dbl &pos(void) const;
	const Vector2dbl &size(void) const;


	bool SetAnim(const STATE state, AnimVector& data);			// ±ÆÒ°¼®İdata‚Ì“o˜^

	bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// ó‘Ô‚ğæ“¾‚·‚é‚½‚ß‚¾‚¯
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ±ÆÒ°¼®İC—¹Šm”F
private:
	std::map<STATE, AnimVector> _animMap;						// ±ÆÒ°¼®İŠi”[
	STATE _state;												// ó‘Ô
	unsigned int _animFrame;									// ±ÆÒ°¼®İ—pÌÚ°Ñ
	unsigned int _animCount;									// ±ÆÒ°¼®İ—p¶³İÄ

protected:
	bool DestroyPrpc(void);
	bool _alive;												// ¶‚«‚Ä‚¢‚é‚©
	bool _dead;													// €‚ñ‚Å‚¢‚é‚©
	Vector2dbl _pos;											// À•W
	Vector2dbl _size;											// ‰æ‘œ»²½Ş
	double _rad;												// Šp“x
	int _zOder;													// •`‰æ‚Ì—Dæ
};

