#include "define.h"
#include "DxLib.h"
#include "UI.h"

class player;

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
		bl_gh = LoadGraph("Data/Image/object.png",true);//static‚Å‚â‚è‚½‚¢
	}
	void Draw();
	void Move();
	void All();
};

class coin
{
public:
	int pos_x, pos_y;
	int width, height;
	int generate_rng;
	int coin_gh,coin_se;
	bool hit_flg;
	bool exist_flg;
	coin()
	{
		pos_x = WINDOW_X; pos_y = 50;
		width = 32; height = 32;
		generate_rng = 0;
		coin_gh = LoadGraph("Data/Image/Ps_pl.png");
		coin_se = LoadSoundMem("Data/Music/se/coin05.mp3");
		hit_flg = false;
		exist_flg = true;
	}
	void coinDraw();
	void coinMove();
	void coinReset();
	void coinHitCheck(player pl);
	void coinAll(player pl,Score *sc);
	void Debug();
	void addScore(Score *sc);
};
void setStairs(int cnt,int nowcnt,int world,block *stairs);
void drawStairs(block* stairs);
void resetStairs(block *stairs);
void setStairsAll(int cnt, int nowcnt,int world,block* stairs);
void changeWorld(block* stairs);

void setWallsAll(int cnt, int nowcnt, int world, block* walls);
void setWalls(int cnt, int nowcnt, int world, block* walls);
void drawWalls(block* walls);
void resetWalls(block* walls);