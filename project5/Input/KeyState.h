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
	void SetKeyConfing(void);				// 設定用
	void (KeyState::*func)(void);			// 関数ﾎﾟｲﾝﾀｰ  変数		かっこをつけないと別の認識をされる

	char _buf[256];							// 全てのｷｰの情報取得用
	std::vector<int> _keyCon;				// 今のｷｰｺﾝ
	std::vector<int> _keyConDef;			// ﾃﾞﾌｫﾙﾄ
	int modeKeyOld;
	INPUT_ID _confID;
};

