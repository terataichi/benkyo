#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);					// 
	void SetKeyConfing(void);				// İ’è—p
	void (KeyState::*func)(void);			// ŠÖ”Îß²İÀ°  •Ï”		‚©‚Á‚±‚ğ‚Â‚¯‚È‚¢‚Æ•Ê‚Ì”F¯‚ğ‚³‚ê‚é

	char _buf[256];							// ·°‚Ìî•ñæ“¾—p
	std::vector<int> _keyCon;				// ¡‚Ì·°ºİ
	std::vector<int> _keyConDef;			// ÃŞÌ«ÙÄ

};

