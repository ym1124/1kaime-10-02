
#include "all.h"

void scene::doTitleMode()
{
	nowscene = TITLE;
}

void scene::doPlayMode()
{
	/*start_timer += 1;
	if (start_timer >= 120)
	{*/
		nowscene = PLAY;
		start_flg = false;
		/*
		start_timer = 0;
	}*/
}

void scene::doOverMode(int *cnt,Score *sc)
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		select = 1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		select = 2;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && select==1)//リトライ
	{
		nowscene = PLAY;
		*cnt = 0;
	}
	if (CheckHitKey(KEY_INPUT_RETURN) && select == 2)//タイトル
	{
		nowscene = TITLE;
		*cnt = 0;
	}
	sc->setScore(cnt);
}

void scene::moveString()
{
	upperside += 4;
	downside -= 4;
	if (upperside >= WINDOW_Y&&downside <= 0)
	{
		upperside = 0;
		downside = WINDOW_Y;
		doPlayMode();
	}
}

void scene::drawString()
{//左上右上右下左下
	DrawModiGraph(
		0, upperside,
		WINDOW_X, upperside,
		WINDOW_X, downside,
		0,downside,
		title_string, true);
}