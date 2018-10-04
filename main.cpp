#include"all.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	player *pl = new player();
	scene *se = new scene();
	pl->setPlayerPos();

	int cnt = -1,color=GetColor(150,155,155);
	//階段用******************************************
	block stairs[6];//bl_xが同じでbl_y	だけが変更されるインスタンスが最初にできるので初期値は大きくしておく(-だとループしてくる)
	block stairs1[6];
	//***********************************************
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		//タイトル画面
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->start_flg = true;
			}
			if (se->start_flg == true)
			{
				se->doPlaymode();
			}
		}

		if (se->nowscene == PLAY)
		{
			cnt++;
			//背景描画
			bk->drawPlay();
			//階段描画
			//******************************
			setStairsAll(100, cnt, stairs, pl);
			setStairsAll(700, cnt, stairs1, pl);
			setStairsAll(400, cnt, stairs, pl);
			drawStairs(stairs,pl);
			drawStairs(stairs1, pl);
			//******************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitlemode();
			}
			//プレイヤー描画
			pl->setPlayerPos();
			pl->Jump();
			pl->Draw();
		}
		DrawFormatString(30, 30, color, "cnt:%d", cnt);

		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			delete bk;

			break;
		}
	}

	DxLib_End();
	return 0;
}