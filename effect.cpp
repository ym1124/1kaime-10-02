#include "all.h"

void spark::drawSpark()
{
	if (Valid == 1)
	{
		switch (anim_flg)
		{
		case 0:
			anim_x++;
			anim_x2--;
			if (anim_x >= 10)anim_flg = 1;
			break;
		case 1:
			anim_y++;
			anim_y2--;
			if (anim_y >= 10)anim_flg = 2;
			break;
		case 2:
			anim_x--;
			anim_x2++;
			if (anim_x <= 0)anim_flg = 3;
			break;
		case 3:
			anim_y--;
			anim_y2++;
			if (anim_y <= 0)anim_flg = 0;
			break;
		}
		if (Y <= WINDOW_Y / 2)DrawBox(X+anim_x, Y+anim_y, X + anim_x2, Y + anim_y2, GetColor(0, 0, 0), true);
		else if(Y > WINDOW_Y/2)DrawBox(X + anim_x, Y + anim_y, X + anim_x2, Y + anim_y2, GetColor(255, 255, 255), true);
	}
}

void spark::createSpark(int x, int y)
{
	/*int i;*///よくない？

	// 使われていない火花データを探す
	/*for ( i = 0; i < MAX_SPARK; i++)
	{
		if (Valid == 0) break;
	}*/

	// もし使われていない火花データがあったら火花を出す
	/*if (i != MAX_SPARK)
	{*/
	if (Valid == 0) {
		// 火花の位置を設定
		X = x;
		Y = WINDOW_Y / 2;

		// 移動力を設定
		Sx = GetRand(7) - 3;
		Sy = -GetRand(7)+3;

		// 火花の重さをセット
		G = GetRand(0);

		// 火花の明るさセット
		Bright = 255;

		// 火花データを使用中にセット
		Valid = 1;
	}
	//}
}

// 火花移動処理
void spark::moveSpark()
{
	// 火花データが無効だったらスキップ
	if (Valid == 0);

	else {
		// 位置を移動力に応じてずらす
		Y += Sy;
		X += Sx;

		// 移動力を変更
		Sy += G;

		// 火花の明るさを下げる
		Bright -= 2;

		// 火花の明るさが０以下になったら火花データを無効にする
		if (Bright < 0) Valid = 0;
	}
}

void spark::sparkAll(int x,int y)
{
	createSpark(x, y);
	moveSpark();
}

void spark::jumpSpark(player *pl)
{
	if (pl->worldchange == BLACK_WORLD&&pl->jflg==true&&pl->changef==true)//このへんと
	{
		if (particle_seflg == false)
		{
			PlaySoundMem(particle_se, DX_PLAYTYPE_BACK);
			particle_seflg = true;
		}
		sparkAll(pl->pos_x, pl->pos_y);
		drawSpark();
	}
	if (pl->worldchange == WHITE_WORLD&&pl->jflg == true && pl->changef == true)//このへん微妙やから直す
	{
		if (particle_seflg == false)
		{
			PlaySoundMem(particle_se, DX_PLAYTYPE_BACK);
			particle_seflg = true;
		}
		sparkAll(pl->pos_x, pl->pos_y);
		drawSpark();
	}

	if (pl->jflg == false && pl->changef == true)
	{
		particle_flg = false;
		particle_seflg = false;
		Bright = -1;
		drawSpark();
	}
}

void setParticleSe(spark *sp)
{
	sp[0].particle_se = LoadSoundMem("Data/Music/se/strange_bell.mp3");
}