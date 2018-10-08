#include "define.h"
#include "DxLib.h"

class block
{
public:
	int bl_x, bl_y;
	int bl_gh;
	int set_x,set_y;
	int world;
	bool exist;
	block()
	{
		set_x = 0;
		set_y = 0;
		bl_x = 10000;
		bl_y = WINDOW_Y/2-32;
		world=0;
		exist = false;
		bl_gh = LoadGraph("Data/Image/object.png",true);
	}
	void Draw();
	void Move();
	void All();
};

void setStairs(int cnt,int nowcnt,int world,block *stairs);
void drawStairs(block* stairs);
void resetStairs(block *stairs);
void setStairsAll(int cnt, int nowcnt,int world,block* stairs);
void changeWorld(block* stairs);
