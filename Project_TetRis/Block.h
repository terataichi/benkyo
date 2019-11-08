#pragma once
#include "Obj.h"

// ﾌﾞﾛｯｸの種類
enum class BLOCK_TYPE
{
	I,
	O,
	T,
	J,
	L,
	S,
	Z,
	MAX
};

// ﾌﾞﾛｯｸの状態
enum class BLOCK_STATE
{
	TYPE,			// 種類
	VECTOR,			// 座標
	RECT,			// 画像左上の座標
	SIZE,			// 画像サイズS
	MAX
};

// ﾌﾞﾛｯｸの管理用		画像左上の座標	ﾌﾞﾛｯｸのデータ
using BlockPair = std::pair<Vector2, std::vector<int>>;

//							 種類と	座標	画像左上の座標  画像のサイズ
using BlockState = std::tuple<BLOCK_TYPE, Vector2, Vector2, Vector2>;

class Block :
	public Obj
{
public:
	Block();
	Block(BlockState state);									// ｹﾞｰﾑｼｰﾝから情報をもらって初期化する
	~Block();
	void Update(void) override;									// 更新

private:
	std::map<BLOCK_TYPE, BlockPair>_blockmap;					// ﾌﾞﾛｯｸの種類に情報を持たせる
	void init(void);											// 初期化
	BLOCK_TYPE _type;											// 種類、objに作る必要はない?
};

