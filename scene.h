#pragma once
#include "define.h"
#include "DxLib.h"
#include "player.h"
#include "UI.h"

enum { TITLE, PLAY, OVER, CLEAR,TUTORIAL };
class scene
{
public:
	int nowscene;
	int start_timer;
	int o_select,t_select;
	int title_string,upperside,downside;
	int start_gh,tutorial_gh,totitle_gh, retry_gh,gameover_gh;
	int tutorial_cnt, tutorial_cnt_temp, longpress_cnt;
	bool start_flg;
	scene()
	{
		start_flg = false;
		start_timer = 0;
		t_select = 1;
		o_select = 0;
		upperside = 0;
		longpress_cnt = 0;
		tutorial_cnt = 0;
		tutorial_cnt_temp = 0;
		downside = WINDOW_Y;
		nowscene = TITLE;//é¿ç€ÇÕTITLE
		start_gh = LoadGraph("Data/Image/start.png",true);
		tutorial_gh = LoadGraph("Data/Image/tutorial.png",true);
		title_string = LoadGraph("Data/Image/title_char.png", true);
		totitle_gh = LoadGraph("Data/Image/title.png", true);
		retry_gh = LoadGraph("Data/Image/retry.png", true);
		gameover_gh = LoadGraph("Data/Image/gameover.png", true);
	}
	void doTitleMode(int pad);
	void doPlayMode();
	void drawString();
	void drawTitleMenu(int pad);
	void moveString(); 
	void doOverMode(int *cnt, Score *sc,player *pl,int pad);
	void endGame(player *pl,int pad);
};