#include "object.h"
#include "back.h"
#include "define.h"

void back::drawTitle()
{
	DrawGraph(0, 0, titleback_gh, true);
}

void back::drawPlay()
{
	DrawGraph(0, 0, playback_gh, true);
}

void back::drawSnow()
{
	DrawRectExtendGraph(0, 0, WINDOW_X, WINDOW_Y, snowanim_x * 256, snowanim_y * 256, 256, 256, snow_gh, true);
	animCnt++;
	snowanim_x = animCnt / 10 % 8;
	snowanim_y = animCnt / 80 % 3;

	/*DrawRectGraph(0, 0, WINDOW_X, WINDOW_Y, snowanim_x * 960, snowanim_y * 540, WINDOW_X, WINDOW_Y, snow_gh, true);
	animCnt++;
	snowanim_x = animCnt / 60 % 8;
	snowanim_y = animCnt / 480% 3;*/

	if (snowanim_y == 3 && snowanim_x == 5) { snowanim_x = 0; snowanim_y = 0; }
}

void back::drawCloud()
{
	move_x -= 5;
	if (move_x < -WINDOW_X)move_x = 0;
	DrawModiGraph(
		move_x, 0,
		WINDOW_X + move_x, 0,
		WINDOW_X + move_x, WINDOW_Y,
		move_x, WINDOW_Y,
		cloud_gh, true);
	DrawModiGraph(
		move_x + WINDOW_X, 0,
		move_x + WINDOW_X * 2, 0,
		move_x + WINDOW_X * 2, WINDOW_Y,
		move_x + WINDOW_X, WINDOW_Y,
		cloud_gh, true);
}

void back::drawLayerAll(int cnt)
{
	if(cnt>500)drawSnow();//cntの位置でエフェクト追加
	if(cnt>2000)drawCloud();
}