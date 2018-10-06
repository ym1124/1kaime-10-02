#include"all.h"
#include <stdlib.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	ChangeWindowMode(true);

	SetGraphMode(WINDOW_X, WINDOW_Y, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	back *bk = new back();
	player *pl = new player();
	scene *se = new scene();
	spark sparks[MAX_SPARK];
	Score *sc = new Score();

	pl->setPlayerPos();
	sc->getScore();
	setParticleSe(sparks);
	//背景レイヤー用準備//採用するならちゃんとしたとこに書く
	int cloud_gh;
	int move_x = 0;
	cloud_gh = LoadGraph("Data/Image/BG_cloud.png", true);
	//
	int color = GetColor(150, 155, 155);
	int j = 0;
	int cnt = -1;
	int reset_rng = 0;
	//**************************************
	int snowanim_x=0, snowanim_y=0, animCnt=0;
	int snow_gh = LoadGraph("Data/Image/snow.png");
	//階段用******************************************
	block stairs[6];//bl_xが同じでbl_y	だけが変更されるインスタンスが最初にできるので初期値は大きくしておく(-だとループしてくる)
	block stairs1[6];
	//***********************************************
	while (ProcessMessage() != -1)
	{
		srand((unsigned int)(time(NULL)));

		ClearDrawScreen();
		//タイトル画面
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			se->drawString();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->start_flg = true;
			}
			if (se->start_flg == true)
			{
				se->moveString();
			}
		}

		if (se->nowscene == PLAY)
		{
			cnt++;
			//背景描画
			bk->drawPlay();

			//パーティクル
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32用の演出追加するかも
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); }}//妥協案

			//階段設定
			//********************************************************************
			reset_rng = rand() % 6;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//オブジェクトセット
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);

			//最初の生成とリセットが被るとダメ
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//ランダムリセット
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//ランダムリセット
				resetStairs(stairs1);
			//********************************************************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitleMode();
			}
			if (CheckHitKey(KEY_INPUT_5))
			{
				se->nowscene = OVER;
			}
			//プレイヤー描画
			pl->Jump();
			pl->Draw();
		}

		//背景レイヤー用準備
		if (cnt > 300)
		{
			/*move_x -= 5;
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
				cloud_gh, true);*/

			DrawRectExtendGraph(0, 0, WINDOW_X, WINDOW_Y, snowanim_x * 256, snowanim_y * 256, 256, 256, snow_gh, true);
			animCnt++;
			snowanim_x = animCnt/20% 8;
			snowanim_y = animCnt/20% 3;
			/*if (snowanim_y == 3 && snowanim_x == 5) { snowanim_x = 0; snowanim_y = 0; }*/
		}

		if (se->nowscene == OVER)
		{
			se->doOverMode(&cnt,sc);
			sc->viewScore();
		}

		DrawFormatString(30, 30, color, "cnt:%d,reset_rng:%d", cnt, reset_rng);

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