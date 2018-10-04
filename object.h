#include "all.h"

#define BLOCK_WIDTH  32
#define BLOCK_HEIGHT  32

#define SCROLL_SPEED 5

class block
{
public:
	int bl_x, bl_y;
	int bl_gh;
	int set_x,set_y;
	bool exist;
	block()
	{
		set_x = 0;
		set_y = 0;
		bl_x = 10000;
		bl_y = WINDOW_Y/2-32;
		exist = false;
		bl_gh = LoadGraph("Data/Image/object.png",true);
	}
	void Draw();
	void Move();
	void All();
};

void setStairs(int cnt,int nowcnt,block *stairs);
void drawStairs(block* stairs,player* pl);
void resetStairs(block *stairs);
void setStairsAll(int cnt, int nowcnt,block* stairs, player* pl);
void changeWorld(block* stairs, player* pl);
