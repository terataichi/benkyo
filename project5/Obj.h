#pragma once
#include <string>
#include <map>
#include <vector>
#include <Vector2.h>

using AnimVector = std::vector<std::pair<int, unsigned int>>;

class Obj
{
public:
	Obj();
	void Update(void);
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool animKey(const std::string key);						// ��ҷ��̐ݒ�
	const std::string animKey(void) const;

	bool SetAnim(const std::string key, AnimVector& data);		// ��Ұ���data�̓o�^
private:

	std::map<std::string, AnimVector> _animMap;					// ��Ұ��݊i�[
	std::string _animKey;										// ��Ұ��ݗp�L�[
	unsigned int _animFrame;									// ��Ұ��ݗp�ڰ�
	unsigned int _animCount;									// ��Ұ��ݗp����

	Vector2 _pos;
};

