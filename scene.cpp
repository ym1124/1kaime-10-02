#pragma once
#include "scene.h"
#include "UI.h"

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

void scene::doOverMode(int *cnt,Score *sc,player *pl)
{
	switch (select)
	{
	case 0:
		DrawGraph(100, WINDOW_Y - 200, retry_gh, true);
		DrawGraph(WINDOW_X - 340, WINDOW_Y - 200, title_gh, true);
		break;
	case 1:
		DrawExtendGraph(70, WINDOW_Y-230, 340, WINDOW_Y-100,retry_gh, true);
		DrawGraph(WINDOW_X - 340, WINDOW_Y - 200, title_gh, true);
		break;
	case 2:
		DrawGraph(100, WINDOW_Y - 200, retry_gh, true);
		DrawExtendGraph(WINDOW_X-370, WINDOW_Y-230, WINDOW_X-100, WINDOW_Y-100, title_gh, true);
		break;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		select = 1;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		select = 2;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && select==1)//リトライ
	{
		nowscene = PLAY;
		pl->worldchange = WHITE_WORLD;
		pl->setPlayerPos();
		*cnt = 0;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && select == 2)//タイトル
	{
		nowscene = TITLE;
		pl->worldchange = WHITE_WORLD;
		pl->setPlayerPos();
		*cnt = 0;
	}
	sc->setScore(cnt);
	sc->getScore();
	pl->jumpstartflg = true;
}

void scene::moveString()
{
	upperside += 4;
	downside -= 4;
	if (upperside >= WINDOW_Y&&downside <= 0)
	{
		upperside = 0;
		downside = WINDOW_Y;
		longpress_cnt = 0;
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