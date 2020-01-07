#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>
#include "DIR.h"

#define PI 3.141592						// ‰~ü—¦
#define BLOCK_SIZE 16

enum class ANIMSTATE
{
	NORMAL,			// ’Êí
	DETH,			// (€–S)
	MAX
};

class Obj;			// ÌßÛÄÀ²Ìß¾İ¹Şİ‚Ä‚«‚È
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;
using BlockMap = std::map < DIR, std::vector<std::vector<int>>>;

class Obj
{
public:
	Obj();
	virtual void Update() = 0;
	virtual void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const ANIMSTATE state);								// ±ÆÒ·°‚Ìİ’è

	// ‚Ù‚µ‚¢‚à‚Ì‚ğ•Ô‚·‚¾‚¯
	const ANIMSTATE state(void) const;								
	const Vector2 &pos(void) const;
	const Vector2 &size(void) const;
	const BlockMap &blockData(void) const;
	const DIR &dir(void) const;

	// ¾¯Ä
	bool SetAnim(const ANIMSTATE state, AnimVector& data);			// ±ÆÒ°¼®İdata‚Ì“o˜^
	virtual bool SetAlive(bool alive);
	bool SetState(ANIMSTATE state);
	bool SetBlock(BlockMap data);								// ÌŞÛ¯¸‚Ì“à—e‚ğ‘‚«Š·‚¦‚é‚Æ‚«‚Ég‚¤
	bool isAlive(void) { return _alive; }						// ó‘Ô‚ğæ“¾‚·‚é‚½‚ß‚¾‚¯
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ±ÆÒ°¼®İC—¹Šm”F
protected:
	bool _moveFlg;												// ‘€ì‚µ‚Ä‚é‚â‚ÂÌ×¸Ş

	bool DestroyPrpc(void);
	bool _alive;												// ¶‚«‚Ä‚¢‚é‚©
	bool _dead;													// €‚ñ‚Å‚¢‚é‚©
	Vector2 _pos;												// À•W
	Vector2 _size;												// ‰æ‘œ»²½Ş
	Vector2 _upLeft;											// Ú¸Ä¸Ş×Ì‚Ì¶ã‚ÌÀ•W
	double _rad;												// Šp“x
	int _zOder;													// •`‰æ‚Ì—Dæ

	std::map<ANIMSTATE, AnimVector> _animMap;						// ±ÆÒ°¼®İŠi”[
	ANIMSTATE _state;												// ó‘Ô
	unsigned int _animFrame;									// ±ÆÒ°¼®İ—pÌÚ°Ñ
	unsigned int _animCount;									// ±ÆÒ°¼®İ—p¶³İÄ
	BlockMap _blockData;	// ÌŞÛ¯¸‚ÌÃŞ°ÀŠi”[—p
	DIR _dir;													// ÌŞÛ¯¸‚ÌŒü‚«
};

