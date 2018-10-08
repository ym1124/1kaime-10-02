#pragma once
#include "define.h"
#include "DxLib.h"
#include "UI.h"

enum { TITLE, PLAY, OVER, CLEAR,MENU };
class scene
{
public:
	int nowscene;
	int start_timer;
	int select;
	int title_string,upperside,downside;
	bool start_flg;
	scene()
	{
		start_flg = false;
		start_timer = 0;
		select = 0;
		upperside = 0;
		downside = WINDOW_Y;
		nowscene = TITLE;//é¿ç€ÇÕTITLE
		title_string = LoadGraph("Data/Image/title_char.png", true);
	}
	void doTitleMode();
	void doPlayMode();
	void drawString();
	void moveString(); 
	void doOverMode(int *cnt, Score *sc);
};