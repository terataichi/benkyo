#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include "common/Vector2.h"

#define PI 3.141592						// �~����

enum class STATE
{
	NORMAL,			// �ʏ�
	EX,				// ������
	DETH,			// ���� (���S)
	MAX
};

// 
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	PL_BULLET,
	EM_BULLET
};

class Obj;			// �������߾ݹ�݂Ă���
using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj obj) = 0;
	virtual void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);								// ��ҷ��̐ݒ�

	// �ق������̂�Ԃ�����
	const STATE state(void) const;								
	const Vector2dbl &pos(void) const;
	const Vector2dbl &size(void) const;
	const UNIT_ID &unitID(void) const;
	const bool &exFlag(void) const;

	// ���
	bool SetAttack(bool exflag);								// �U���׸ނ̃Z�b�g
	bool SetAnim(const STATE state, AnimVector& data);			// ��Ұ���data�̓o�^
	virtual bool SetAlive(bool alive);
	bool isAlive(void) { return _alive; }						// ��Ԃ��擾���邽�߂���
	bool isDead(void) { return _dead; }
	bool isAnimEnd(void);										// ��Ұ��ݏC���m�F
private:


protected:
	bool DestroyPrpc(void);
	bool _alive;												// �����Ă��邩
	bool _dead;													// ����ł��邩
	Vector2dbl _pos;											// ���W
	Vector2dbl _size;											// �摜����
	double _rad;												// �p�x
	int _zOder;													// �`��̗D��
	UNIT_ID _unitID;											// ���ʗp
	bool _exFlag;												// �U���׸�

	std::map<STATE, AnimVector> _animMap;						// ��Ұ��݊i�[
	STATE _state;												// ���
	unsigned int _animFrame;									// ��Ұ��ݗp�ڰ�
	unsigned int _animCount;									// ��Ұ��ݗp����
};

