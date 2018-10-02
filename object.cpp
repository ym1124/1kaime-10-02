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