#include "all.h"

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
};

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
	if (stairs[2].bl_x+stairs[2].set_x+32 < 0)resetStairs(stairs);
}
