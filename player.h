#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "DxLib.h"
#include "object.h"

#define PL_WIDTH 24
//#define PL_HEIGHT 32
#define PL_HEIGHT 29

#define BLACK_WORLD 0
#define WHITE_WORLD 1

#define POS_X_INIT 960 * 0.25 
#define POS_Y_INIT 540 * 0.5-32

//TODO ジャンプ連続したら浮くので接地するまで次のジャンプ無効にする
//反転ジャンプ実装

class player
{
public:
	int pos_x, pos_y;
	int pl_gh;
	int anim_cnt,anim_x;
	int pl_speed;

	int y_prev, y_temp;
	int jcount, jtimer;

	int worldchange;

	bool hitflg;
	bool jflg;
	bool wcflg;
	bool changef;
	bool jumpstartflg;

	int jump_se;

	player()
	{
		pl_gh = LoadGraph("Data/Image/player.png");
		pos_x = (int)(POS_X_INIT);
		pos_y = (int)(POS_Y_INIT)+50;

		anim_x = 0; anim_cnt = 0;
		y_prev = 0, y_temp = 0;
		jcount = 0, jtimer = 0;

		worldchange = WHITE_WORLD;

		jump_se = LoadSoundMem("Data/Music/se/powerup01.mp3");

		hitflg=false;
		jflg = false;
		wcflg = false;
		changef = false;
		jumpstartflg = true;
	}

	void Jump();

	void Move(player*, block*);

	void setPlayerPos();

	void Draw();
};

#endif // !_PLAYER_H_