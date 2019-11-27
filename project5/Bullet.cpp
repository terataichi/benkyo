#include "Bullet.h"
#include "ImageMng.h"
#include "Scene\SceneMng.h"
#include <SoundMng.h>

Bullet::Bullet()
{
	lpSceneMng.AddSoundQue({ SOUND_ID("�e")[0],true });

	Init();
}

Bullet::Bullet(UNIT_ID unitID ,Vector2dbl pos)
{
	lpSceneMng.AddSoundQue({ SOUND_ID("�e")[0],true });
	_unitID = unitID;
	_zOder = 0;
	_pos = pos;
	_size = { 8,3 };
	_rad = (PI * 270) / 180.0;
	Init();
}

void Bullet::Update(sharedObj obj)
{
	// �e������ł��珈�����Ȃ�
	if (DestroyPrpc())
	{
		return;
	}

	// �����蔻�肷���
	lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT , *this });

	// �ړ�
	_pos.x = 5 * std::cos(_rad) + _pos.x;
	_pos.y = 5 * std::sin(_rad) + _pos.y;

	// ��ʊO�ɏo����e������
	if (_pos.y < -_size.y / 2 || _pos.y >(lpSceneMng.GameScreenSize.y + _size.y / 2))
	{
		SetAlive(false);
	}
}

Bullet::~Bullet()
{
	
}

void Bullet::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back(IMAGE_ID("�e")[0] , 30);
	SetAnim(STATE::NORMAL, data);

	// �v���C���[���񂾂Ƃ��ɉ����\���������Ȃ�
	data.reserve(1);
	data.emplace_back(-1, 40);				// -1��DxLib��LoadGraph�̕Ԃ�l�ɍ��킹�Ă�
	SetAnim(STATE::DETH, data);
}
