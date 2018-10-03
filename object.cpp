#include "all.h"

void block::All()
{
	Draw();
	Move();
}

void block::Draw()
{
	DrawGraph(bl_x + set_x, bl_y+set_y, bl_gh, true);
}

void block::Move()
{
	bl_x -= SCROLL_SPEED;
}

void setStairs(block* stairs)
{
		for (int i = 0; i < 3; i++)
		{
			stairs[i].set_x = 32 * i;
			stairs[i].set_y = 0;
		}
		stairs[3].set_x = 32;
		stairs[3].set_y = -32;
		stairs[4].set_x = 32 * 2;
		stairs[4].set_y = -32 * 2;
		stairs[5].set_x = 32 * 2;
		stairs[5].set_y = -32;
}

void setStairsMirror(block* stairs)
{
		for (int i = 0; i < 3; i++)
		{
			stairs[i].set_x = 32 * i;
			stairs[i].set_y = 32;
		}
		stairs[3].set_x = 32;
		stairs[3].set_y = 32*2;
		stairs[4].set_x = 32 * 2;
		stairs[4].set_y = 32 * 3;
		stairs[5].set_x = 32 * 2;
		stairs[5].set_y = 32*2;
}


void stairsAll(block* stairs,player* pl)
{
	for (int i = 0; i < 6; i++)
	{
		if (pl->worldchange == 0)//ƒvƒŒƒCƒ„[‚ªã‚Ì¢ŠE‚È‚ç
		DrawRectGraph(stairs[i].bl_x + stairs[i].set_x, stairs[i].bl_y + stairs[i].set_y, 0, 0, 32, 32, stairs[i].bl_gh, true);
		else//‰º‚Ì¢ŠE‚È‚ç
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
