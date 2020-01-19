#pragma once
#include <memory>

#define lpScoreMng ScoreMng::GetInstance()

#define SCORE_SIZE_X 16
#define SCORE_SIZE_Y 16
#define MAX_SCORE 9		// Å‘åŒ…”
#define MAX_LINE 2

class ScoreMng
{
public:
	static ScoreMng &GetInstance(void)
	{
		return *_sInstance;				// ’†g‚ğ•Ô‚·
	}

	void Draw(void);						// •`‰æ
	void ScoreDraw(void);
	void LineDraw(void);

	void AddScore(void);					// ½º±‰ÁZ
	void Init(void);						// ‰Šú‰»
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

	int _score;										// scoreŠi”[—p
	int _line;										// lineŠi”[
	int _drawScrNum[MAX_SCORE];						// •`‰æ—p
	int _drawLineNum[MAX_LINE];						// •`‰æ—p
};

