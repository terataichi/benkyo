#include "ScoreMng.h"
#include "common/ImageMng.h"
#include "Scene/SceneMng.h"

std::unique_ptr<ScoreMng, ScoreMng::ScoreMngDeleter> ScoreMng::_sInstance(new ScoreMng());

void ScoreMng::Draw()
{
	ScoreDraw();
	LineDraw();
}

void ScoreMng::ScoreDraw(void)
{
	int drawScr;
	int tmpNum = 100000000;

	drawScr = _score >= 1000000000 ? 999999999 : drawScr = _score;		// Å‘å’lÁª¯¸

	for (int i = 0; i < MAX_SCORE; i++)
	{
		_drawScrNum[i] = drawScr / tmpNum;
		drawScr %= tmpNum;
		tmpNum /= 10;

		lpSceneMng.AddDrawQue({ IMAGE_ID("½º±")[0],
								40 + SCORE_SIZE_X * i,
								280,
								SCORE_SIZE_X * _drawScrNum[i],
								0,
								SCORE_SIZE_X,
								SCORE_SIZE_Y,
								100000,
								LAYER::CHAR });
	}
}

void ScoreMng::LineDraw(void)
{
	int drawScr;
	int tmpNum = 10;

	drawScr = _line >= 100 ? 99 : drawScr = _line;		// Å‘å’lÁª¯¸

	for (int i = 0; i < MAX_LINE; i++)
	{
		_drawLineNum[i] = drawScr / tmpNum;
		drawScr %= tmpNum;
		tmpNum /= 10;

		lpSceneMng.AddDrawQue({ IMAGE_ID("½º±")[0],
								144 + SCORE_SIZE_X * i,
								120,
								SCORE_SIZE_X * _drawLineNum[i],
								0,
								SCORE_SIZE_X,
								SCORE_SIZE_Y,
								100000,
								LAYER::CHAR });
	}
}

void ScoreMng::AddScore()
{
	_score += 100;
	_line += 1;
}

void ScoreMng::Init()
{
	_score = 0;
	_line = 0;
}

const int & ScoreMng::score(void) const
{
	return _score;
}

ScoreMng::ScoreMng()
{
}

ScoreMng::~ScoreMng()
{
}
