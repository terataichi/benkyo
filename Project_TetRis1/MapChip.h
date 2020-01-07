#pragma once
#include <vector>
#include <memory>
#include <Obj.h>
#include <Input/INPUT_ID.h>

#define CHIP_MAX_X 14
#define CHIP_MAX_Y 24
#define ONE_LINE 10		// �������ߐ�

#define lpMapChip MapChip::GetInstance()

class MapChip
{
public:
	static MapChip &GetInstance(void)
	{
		return *_sInstance;	// * �ϰ��߲���̒��g��Ԃ�
	}

	void InitMap(void);																// ϯ�߂̏�����
	void WriteMap(Vector2& pos, BlockMap& blockData, DIR dir);						// ��������
	void DeleteLine(void);															// ײݏ����܂�
	bool CheckLine(void);															// ײ�����
	bool CheckMove(Vector2& pos, INPUT_ID id, BlockMap& blockData, DIR dir);		// �����Ă������ǂ���
	bool CheckDown(Vector2& pos, BlockMap& blockData, DIR dir);						// �����n�ʂ������I��������
	bool CheckRota(Vector2& pos, BlockMap& blockData, DIR dir);						// ��]�����Ă������ǂ���
	bool CheckGameOver(void);															// �ްѵ��ް����

	void GameDraw(void);
	void GemeOverDraw(void);

	Vector2 OutFix(Vector2& pos, BlockMap& blockData, DIR dir);						// ��ۯ����O�ɏo��������Ɉړ�������

private:


	struct MapChipDeleter	// ������ذ��
	{
		void operator()(MapChip* mapChip)const
		{
			delete mapChip;
		}
	};

	static std::unique_ptr<MapChip, MapChipDeleter>_sInstance;

	std::vector<std::vector<int>>_mapData;					// ϯ���ް��i�[�p
	Vector2 _chip;											// ������ۯ������߂̏ꏊ�i�[�p
	int _delChipY;											// ײ������Ō�����������Y��ۑ����Ă���

	MapChip();
	~MapChip();
};

