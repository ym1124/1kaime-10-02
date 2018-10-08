#include "DxLib.h"
#include "myfunc.h"

bool checkHitSideBlock(player *p, block *stairs)
{
	switch (p->worldchange) {

	case BLACK_WORLD:
		for (int k = 0; k < 6; k++) {

			int pl_lx = p->pos_x, pl_ly = p->pos_y, pl_w = PL_WIDTH, pl_h = PL_HEIGHT;
			int bl_lx[6], bl_ly[6], bl_w = BLOCK_WIDTH, bl_h = BLOCK_HEIGHT;

			for (int i = 0; i < 6; i++) {
				bl_lx[i] = stairs[i].bl_x + stairs[i].set_x;
				bl_ly[i] = stairs[i].bl_y + stairs[i].set_y;
			}

			if ((pl_lx + pl_w >= bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly >= bl_ly[k] && pl_ly < bl_ly[k] + bl_h)
				||
				(pl_lx + pl_w >= bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly + pl_h > bl_ly[k] + 1 && pl_ly + pl_h < bl_ly[k] + bl_h))
			{
				DrawFormatString(300, 50, 256, "aaaaaaaaaaaaa");
				DrawFormatString(300, 10, 256, "pl_ry:%d,bl_ly[%d]:%d,bl_lx[%d];%d", pl_ly, k, bl_ly[k],k,bl_lx[k]);
				//p->pos_x = 50;
				p->hitflg = true;
				return true;
			}
			else 
			{
				//DrawFormatString(300, 10, 256, "pl_ry:%d,bl_ly[%d]:%d,bl_lx[%d];%d", pl_ly, k, bl_ly[k], k, bl_lx[k]);

				//return false;
			}
		}
		return false;
		break;

	case WHITE_WORLD:
		for (int k = 0; k < 6; k++) {

			int pl_lx = p->pos_x, pl_ly = p->pos_y, pl_w = PL_WIDTH, pl_h = PL_HEIGHT;
			int bl_lx[6], bl_ly[6], bl_w = BLOCK_WIDTH, bl_h = BLOCK_HEIGHT;

			for (int i = 0; i < 6; i++) {
				bl_lx[i] = stairs[i].bl_x + stairs[i].set_x;
				bl_ly[i] = stairs[i].bl_y + stairs[i].set_y;
			}

			if ((pl_lx + pl_w >= bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly >= bl_ly[k] && pl_ly < bl_ly[k] + bl_h)
				||
				(pl_lx + pl_w >= bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly + pl_h > bl_ly[k] + 1 && pl_ly + pl_h < bl_ly[k] + bl_h))
			{
				DrawFormatString(300, 50, 256, "aaaaaaaaaaaaa");
				DrawFormatString(300, 10, 256, "pl_ry:%d,bl_ly[%d]:%d,bl_lx[%d];%d", pl_ly, k, bl_ly[k], k, bl_lx[k]);
				//p->pos_x = 50;
				//p->hitflg = true;
				return true;
			}
			else
			{
				//DrawFormatString(300, 10, 256, "pl_ry:%d,bl_ly[%d]:%d,bl_lx[%d];%d", pl_ly, k, bl_ly[k], k, bl_lx[k]);

				//return false;
			}
		}
		return false;
		break;
	}
}

bool checkHitTopBlock(player *p, block *stairs)
{
	switch (p->worldchange) {

	case BLACK_WORLD:
		for (int k = 0; k < 6; k++) {

			int pl_lx = p->pos_x, pl_ly = p->pos_y, pl_w = PL_WIDTH, pl_h = PL_HEIGHT;
			int bl_lx[6], bl_ly[6], bl_w = BLOCK_WIDTH, bl_h = BLOCK_HEIGHT;

			for (int i = 0; i < 6; i++) {
				bl_lx[i] = stairs[i].bl_x + stairs[i].set_x;
				bl_ly[i] = stairs[i].bl_y + stairs[i].set_y;
			}

			if ((pl_lx >= bl_lx[k] && pl_lx < bl_lx[k] + bl_w) &&
				(pl_ly + pl_h >= bl_ly[k] && pl_ly + pl_h < bl_ly[k] + bl_h)
				||
				(pl_lx + pl_w > bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly + pl_h >= bl_ly[k] && pl_ly + pl_h < bl_ly[k] + bl_h))
			{
				p->pos_y = bl_ly[k] - 32;
				DrawCircle(pl_lx + pl_w, pl_ly + pl_h, 10, 128, true);
				DrawFormatString(300, 50, 256, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

				return true;
			}
			else
			{

				//DrawFormatString(300, 25, 256, "pl_ry:%d,bl_ly[%d]:%d:", pl_ly, 5, bl_ly[5]);

				//return false;
			}
		}
		return false;
		break;

	case WHITE_WORLD:
		for (int k = 0; k < 6; k++) {

			int pl_lx = p->pos_x, pl_ly = p->pos_y, pl_w = PL_WIDTH, pl_h = PL_HEIGHT;
			int bl_lx[6], bl_ly[6], bl_w = BLOCK_WIDTH, bl_h = BLOCK_HEIGHT;

			for (int i = 0; i < 6; i++) {
				bl_lx[i] = stairs[i].bl_x + stairs[i].set_x;
				bl_ly[i] = stairs[i].bl_y + stairs[i].set_y;
			}

			if ((pl_lx >= bl_lx[k] && pl_lx < bl_lx[k] + bl_w) &&
				(pl_ly >= bl_ly[k] && pl_ly < bl_ly[k] + bl_h)
				||
				(pl_lx + pl_w > bl_lx[k] && pl_lx + pl_w <= bl_lx[k] + bl_w) &&
				(pl_ly >= bl_ly[k] && pl_ly < bl_ly[k] + bl_h))
			{
				p->pos_y = bl_ly[k] + 32;
				DrawFormatString(300, 50, 256, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

				return true;
			}
			else
			{
				//DrawFormatString(300, 25, 256, "pl_ry:%d,bl_ly[%d]:%d:", pl_ly, 5, bl_ly[5]);

				//return false;
			}
		}
		return false;
		break;
	}
}

