
#define BLOCK_WIDTH  32
#define BLOCK_HEIGHT  32

#define SCROLL_SPEED 5

class block
{
public:
	int bl_x, bl_y;
	int bl_gh;
	int set_x,set_y;
	block()
	{
		set_x = 0;
		set_y = 0;
		bl_x = 400;
		bl_y = WINDOW_Y/2-32;
		bl_gh = LoadGraph("Data/Image/Ps_pl.png",true);
	}
	void Draw();
	void Move();
	void All();
	/*void drawStairs();*/
};

