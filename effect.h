#pragma once
#include "player.h"
#include "DxLib.h"
#include <stdlib.h>
#include <time.h>


class spark
{
public:
	int Valid;	// このデータが使用中か、フラグ
	int X, Y;	// 火花の位置
	int anim_x, anim_y;
	int anim_x2, anim_y2;
	int anim_flg;
	int Sx, Sy;	// 火花の移動力
	int G;		// 火花の重さ
	int Bright;	// 火花の明るさ
	int particle_se;
	bool particle_flg;
	bool particle_seflg;
	spark()
	{
		particle_flg = false;
		particle_seflg = false;
		particle_se=0;
		anim_flg=0;
		anim_x = 0;
		anim_y = 0;
		anim_x2 = 10;
		anim_y2 = 10;
		Valid = 0;
	}
	void createSpark(int x, int y);	// 火花を出す処理
	void moveSpark();	// 火花移動処理
	void drawSpark();
	void sparkAll(int x, int y);
	void jumpSpark(player *pl);
} ;

void setParticleSe(spark *sp);