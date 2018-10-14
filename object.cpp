#include "object.h"
#include "player.h"
void block::All()
{
	Draw();
	Move();
}

void block::Draw()
{
	DrawGraph(bl_x + set_x, bl_y + set_y, bl_gh, true);
}

void block::Move()
{
	bl_x -= SCROLL_SPEED;
}

void setStairs(int cnt,int nowcnt,int world,block* stairs)
{
	if (nowcnt == cnt)
	{
		stairs->world = world;
		for (int i = 0; i < 6; i++)
		{
			stairs[i].bl_x = WINDOW_X;
		}
		for (int i = 0; i < 3; i++)
		{
			stairs[i].set_x = 32 * i;
		}
		stairs[3].set_x = 32;		
		stairs[4].set_x = 32 * 2;		
		stairs[5].set_x = 32 * 2;		
	}
}

void changeWorld(block* stairs)
{
	switch (stairs->world)
	{
	case BLACK_WORLD:
		for (int i = 0; i < 3; i++)
		{
			stairs[i].set_y = 0;
		}
		stairs[3].set_y = -32;
		stairs[4].set_y = -32 * 2;
		stairs[5].set_y = -32;
		break;
	case WHITE_WORLD:
		for (int i = 0; i < 3; i++)
		{
			stairs[i].set_y = 32;
		}
		stairs[3].set_y = 32 * 2;
		stairs[4].set_y = 32 * 3;
		stairs[5].set_y = 32 * 2;
		break;
	}
}

void drawStairs(block* stairs)
{
	for (int i = 0; i < 6; i++)
	{
		if (stairs->world==BLACK_WORLD)
			DrawRectGraph(stairs[i].bl_x + stairs[i].set_x, stairs[i].bl_y + stairs[i].set_y, 0, 0, 32, 32, stairs[i].bl_gh, true);
		else
			DrawRectGraph(stairs[i].bl_x + stairs[i].set_x, stairs[i].bl_y + stairs[i].set_y, 32, 0, 32, 32, stairs[i].bl_gh, true);
		stairs[i].bl_x -= SCROLL_SPEED;
	}
}

void resetStairs(block *stairs)
{
		for (int i = 0; i < 6; i++)
		{
			stairs[i].bl_x = WINDOW_X;
		}
}

void setStairsAll(int cnt,int nowcnt,int world,block* stairs)
{
	setStairs(cnt, nowcnt,world, stairs);
	changeWorld(stairs);
	drawStairs(stairs);
}

void setWallsAll(int cnt, int nowcnt, int world, block* walls)
{
	setWalls(cnt,nowcnt,world,walls);
	drawWalls(walls);
	resetWalls(walls);
}

void setWalls(int cnt, int nowcnt, int world, block* walls)
{
	if (nowcnt == cnt)
	{
		walls->world = world;
		for (int i = 0; i < 3; i++)
		{
			walls[i].bl_x = WINDOW_X;
		}
	}
	switch (walls->world)
	{
	case BLACK_WORLD:
		for (int i = 0; i < 3; i++)
		{
			walls[i].set_y = i*-32;
		}
		break;
	case WHITE_WORLD:
		for (int i = 0; i < 3; i++)
		{
			walls[i].set_y = i*32+32;
		}
		break;
	}
}

void drawWalls(block *walls)
{
	for (int i = 0; i < 3; i++)
	{
		if (walls->world == BLACK_WORLD)
			DrawRectGraph(walls[i].bl_x + walls[i].set_x, walls[i].bl_y + walls[i].set_y, 0, 0, 32, 32, walls[i].bl_gh, true);
		else
			DrawRectGraph(walls[i].bl_x + walls[i].set_x, walls[i].bl_y + walls[i].set_y, 32, 0, 32, 32, walls[i].bl_gh, true);
		walls[i].bl_x -= SCROLL_SPEED;
	}
}

void resetWalls(block *walls)
{
	if (walls[0].bl_x < -32) 
	{
		for (int i = 0; i < 3; i++)
		{
			walls[i].bl_x = WINDOW_X;
		}
	}
}

void coin::coinDraw()
{
	if(exist_flg==true)
	DrawGraph(pos_x, pos_y, coin_gh, true);
}

void coin::coinMove()
{
	pos_x -= 5;
	if (pos_x < -32)exist_flg = false;
}

void coin::coinReset()
{
	if (exist_flg == false&&pos_x<0)
	{
		exist_flg = true;
		pos_x = WINDOW_X;
	}
}

void coin::coinHitCheck(player pl)
{
	//当たり判定　プレイヤーの左端の位置はコインの左端ではなくプレイヤーの右端がコインに当たることの差分を考えて書くとコードが少なくて済む
	if ((pos_x - PL_WIDTH<pl.pos_x&&pos_x + PL_WIDTH>pl.pos_x) && (pos_y - PL_HEIGHT<pl.pos_y&&pos_y + height>pl.pos_y)&&exist_flg==true)
	{
		hit_flg = true;
		exist_flg = false;
	}
	else
		hit_flg = false;
}

void coin::coinAll(player pl,Score *sc)
{
	coinHitCheck(pl);
	coinDraw();
	coinMove();
	addScore(sc);
}

void coin::Debug()
{
	DrawFormatString(0, 0, GetColor(100, 100, 100), "hitflg:%d,existflg:%d", hit_flg, exist_flg);
}

void coin::addScore(Score *sc)
{
	if (exist_flg == false && hit_flg == true)
	{
		sc->nowscore += 100;
		PlaySoundMem(coin_se, DX_PLAYTYPE_BACK);
	}
}