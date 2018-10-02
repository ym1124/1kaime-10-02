

#define PL_WIDTH 28

#define PL_HEIGHT 28

#define BRACK_WORLD 0

#define WHITE_WORLD 1

#define POS_X_INIT WINDOW_X * 0.25 
#define POS_Y_INIT WINDOW_Y * 0.5-32
class player

{
public:
	int pos_x, pos_y;
	int pl_gh;
	player()
	{
		pl_gh = LoadGraph("Data/Image/player1.png");
		pos_x = POS_X_INIT;
		pos_y = POS_Y_INIT;
	}

	void Draw()
	{
		DrawGraph(pos_x, pos_y, pl_gh, true);
	}
};