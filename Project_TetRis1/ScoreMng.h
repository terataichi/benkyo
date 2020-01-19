#pragma once
#include <memory>

#define lpScoreMng ScoreMng::GetInstance()

#define SCORE_SIZE_X 16
#define SCORE_SIZE_Y 16
#define MAX_SCORE 9		// �ő包��
#define MAX_LINE 2

class ScoreMng
{
public:
	static ScoreMng &GetInstance(void)
	{
		return *_sInstance;				// ���g��Ԃ�
	}

	void Draw(void);						// �`��
	void ScoreDraw(void);
	void LineDraw(void);

	void AddScore(void);					// ������Z
	void Init(void);						// ������
	const int& score(void)const;

private:
	struct ScoreMngDeleter
	{
		void operator()(ScoreMng* scoreMng)const
		{
			delete scoreMng;
		}
	};

	ScoreMng();
	~ScoreMng();

	static std::unique_ptr<ScoreMng, ScoreMngDeleter> _sInstance;

	int _score;										// score�i�[�p
	int _line;										// line�i�[
	int _drawScrNum[MAX_SCORE];						// �`��p
	int _drawLineNum[MAX_LINE];						// �`��p
};

