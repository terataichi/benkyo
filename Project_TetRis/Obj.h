#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <Vector2.h>

enum class STATE
{
	NORMAL,			// �ʏ�
	DETH,			// ���S
	MAX
};

class Obj;			// �������߾ݹ�݂Ă���
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(void) = 0;
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

private:
	STATE _state;												// ���
	unsigned int _animFrame;									// ��Ұ��ݗp�ڰ�
	unsigned int _animCount;									// ��Ұ��ݗp����

protected:
	//bool DestroyPrpc(void);
	bool _alive;												// �����Ă��邩
	bool _dead;													// ����ł��邩
	Vector2 _pos;												// ���W
	Vector2 _size;												// �摜����
	Vector2 _rect;												// �摜�̍�����W
};

