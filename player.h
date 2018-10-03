#pragma once
#include "all.h"

#define PL_WIDTH 28

#define PL_HEIGHT 28

#define BLACK_WORLD 0

#define WHITE_WORLD 1

#define POS_X_INIT WINDOW_X * 0.25 
#define POS_Y_INIT WINDOW_Y * 0.5-32

//TODO ジャンプ連続したら浮くので接地するまで次のジャンプ無効にする
//反転ジャンプ実装

class player
{
public:
	int pos_x, pos_y;
	int pl_gh;
	int anim_cnt,anim_x;

	int y_prev, y_temp;
	int jcount, jtimer;

	int worldchange;

	bool jflg;
	bool wcflg;
	bool changef;

	player()
	{
		pl_gh = LoadGraph("Data/Image/player.png");
		pos_x = (int)(POS_X_INIT);
		pos_y = (int)(POS_Y_INIT)+50;

		anim_x = 0; anim_cnt = 0;
		y_prev = 0, y_temp = 0;
		jcount = 0, jtimer = 0;

		worldchange = BLACK_WORLD;

		jflg = false;
		wcflg = false;
		changef = false;
	}

	void Jump()
	{
		//ジャンプ処理
		switch (worldchange) {

		case BLACK_WORLD:

			if (jflg == true) {

				y_temp = pos_y;
				pos_y += (pos_y - y_prev) + 1;
				y_prev = y_temp;

				if (pos_y <= 50 && changef == false)
					wcflg = true;

				if (pos_y >= POS_Y_INIT/* && changef == false*/) {
					if (wcflg == true && changef == false) {
						worldchange = WHITE_WORLD;
						changef = true;
					}
					else {
						pos_y = POS_Y_INIT;
						jcount = 2, jflg = false;
					}
				}
			}

			if (jcount >= 2) {
				jtimer++;
				//次のジャンプまでの間隔をのばす
				if (jtimer >= 11)
				{
					jtimer = 0;
					jcount = 0;
				}
			}

			if (CheckHitKey(KEY_INPUT_SPACE) && jflg == false && jcount == 0) {
				jcount = 1;
				jflg = true, changef = false;
				y_prev = pos_y;
				pos_y -= 15;
			}
			if (CheckHitKey(KEY_INPUT_NUMPADENTER))
				worldchange = WHITE_WORLD;

			break;

		case WHITE_WORLD:

			if (jflg == true) {

				y_temp = pos_y;
				pos_y += (pos_y - y_prev) - 1;
				y_prev = y_temp;

				if (pos_y >= 400 && changef == false)
					wcflg = false;

				if (pos_y <= POS_Y_INIT) {
					if (wcflg == false && changef == false) {
						worldchange = BLACK_WORLD;
						changef = true;
					}
					else {
						pos_y = POS_Y_INIT + 32;
						jcount = 2, jflg = false;
					}
				}
			}

			if (jcount >= 2) {
				jtimer++;
				//次のジャンプまでの間隔をのばす//
				if (jtimer >= 11)
				{
					jtimer = 0;
					jcount = 0;
				}
			}

			if (CheckHitKey(KEY_INPUT_SPACE) && jflg == false && jcount == 0) {
				jcount = 1;
				jflg = true, changef = false;
				y_prev = pos_y;
				pos_y += 15;
			}

			if (CheckHitKey(KEY_INPUT_NUMPADENTER))
				worldchange = BLACK_WORLD;
			break;
		}
	}

	void setPlayerPos()
	{
		if (jflg == false)
		{
			if (worldchange == 0)
			{
				pos_x = (int)(POS_X_INIT);
				pos_y = (int)(POS_Y_INIT);
			}
			else
			{
				pos_x = (int)(POS_X_INIT);
				pos_y = (int)(POS_Y_INIT)+32;
			}
		}
	}

	void Draw()
	{
		//タイトル画面用アニメーションになるかも？
		anim_cnt ++;
		anim_x = anim_cnt / 10 % 4;
		if (worldchange == BLACK_WORLD) {
			DrawRectGraph(pos_x, pos_y, 32*anim_x, 0, 32, 32, pl_gh, true);
		}
		else {
			DrawRectGraph(pos_x, pos_y, 32*anim_x, 32, 32, 32, pl_gh, true);
		}
		DrawFormatString(300, 100, 256, "pos_x:%d,pos_y:%d,world:%d,change:%d", pos_x, pos_y, worldchange, changef);

	}
};
