#pragma once
#include "Obj.h"

// ��ۯ��̎��
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

// ��ۯ��̏��
enum class BLOCK_STATE
{
	TYPE,			// ���
	VECTOR,			// ���W
	RECT,			// �摜����̍��W
	SIZE,			// �摜�T�C�YS
	MAX
};

// ��ۯ��̊Ǘ��p		�摜����̍��W	��ۯ��̃f�[�^
using BlockPair = std::pair<Vector2, std::vector<int>>;

//							 ��ނ�	���W	�摜����̍��W  �摜�̃T�C�Y
using BlockState = std::tuple<BLOCK_TYPE, Vector2, Vector2, Vector2>;

class Block :
	public Obj
{
public:
	Block();
	Block(BlockState state);									// �ްѼ�݂������������ď���������
	~Block();
	void Update(void) override;									// �X�V

private:
	std::map<BLOCK_TYPE, BlockPair>_blockmap;					// ��ۯ��̎�ނɏ�����������
	void init(void);											// ������
	BLOCK_TYPE _type;											// ��ށAobj�ɍ��K�v�͂Ȃ�?
};

