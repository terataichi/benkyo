#pragma once
#include <vector>
#include <memory>
#include <Obj.h>
#include <Input/INPUT_ID.h>

#define CHIP_MAX_X 14
#define CHIP_MAX_Y 24
#define ONE_LINE 10		// 一列のﾁｯﾌﾟ数

#define lpMapChip MapChip::GetInstance()

class MapChip
{
public:
	static MapChip &GetInstance(void)
	{
		return *_sInstance;	// * ｽﾏｰﾄﾎﾟｲﾝﾀの中身を返す
	}

	void InitMap(void);																// ﾏｯﾌﾟの初期化
	void WriteMap(Vector2& pos, BlockMap& blockData, DIR dir);						// 書き込む
	void DeleteLine(void);															// ﾗｲﾝ消します
	bool CheckLine(void);															// ﾗｲﾝﾁｪｯｸ
	bool CheckMove(Vector2& pos, INPUT_ID id, BlockMap& blockData, DIR dir);		// 動いていいかどうか
	bool CheckDown(Vector2& pos, BlockMap& blockData, DIR dir);						// 下が地面やったら終了させる
	bool CheckRota(Vector2& pos, BlockMap& blockData, DIR dir);						// 回転させていいかどうか
	bool CheckGameOver(void);															// ｹﾞｰﾑｵｰﾊﾞｰﾁｪｯｸ

	void GameDraw(void);
	void GemeOverDraw(void);

	Vector2 OutFix(Vector2& pos, BlockMap& blockData, DIR dir);						// ﾌﾞﾛｯｸが外に出たら内側に移動させる

private:


	struct MapChipDeleter	// ｶｽﾀﾑﾃﾞﾘｰﾀｰ
	{
		void operator()(MapChip* mapChip)const
		{
			delete mapChip;
		}
	};

	static std::unique_ptr<MapChip, MapChipDeleter>_sInstance;

	std::vector<std::vector<int>>_mapData;					// ﾏｯﾌﾟﾃﾞｰﾀ格納用
	Vector2 _chip;											// 今のﾌﾞﾛｯｸのﾁｯﾌﾟの場所格納用
	int _delChipY;											// ﾗｲﾝﾁｪｯｸで見つかった時にYを保存しておく

	MapChip();
	~MapChip();
};

