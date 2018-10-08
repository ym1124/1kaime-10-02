#include"DxLib.h"
#include"define.h"
#include"back.h"
#include"player.h"
#include"scene.h"
#include"effect.h"
#include"UI.h"
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
	int color = GetColor(150, 155, 155);
	int j = 0;
	int cnt = -1;
	int reset_rng = 0;
	//階段用******************************************
	block stairs[6];//bl_xが同じでbl_y	だけが変更されるインスタンスが最初にできるので初期値は大きくしておく(-だとループしてくる)
	block stairs1[6];
	block stairs2[6];
	block stairs3[6];
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
			//パーティクル
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32用の演出追加するかも
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//妥協案

			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
			}
			else {
				pl->Move(pl, stairs1);
			}
			if (pl->jumpstartflg == true)//タイトル画面で連続ジャンプさせない処理
			{
				pl->Jump();
				if(pl->worldchange==BLACK_WORLD&&pl->pos_y==POS_Y_INIT)
					pl->jumpstartflg = false;
			}
			pl->Draw();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				se->longpress_cnt++;
				se->start_flg = true;
			}
			if (se->start_flg == true&&se->longpress_cnt>60)
			{
				se->moveString();
			}
			DrawFormatString(300, 300, color, "スペース長押しでスタート");
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
			reset_rng = rand() % 7;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//オブジェクトセット
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);
			setStairsAll(300, cnt, BLACK_WORLD, stairs2);
			setStairsAll(1300, cnt, WHITE_WORLD, stairs3);

			//最初の生成とリセットが被るとダメ
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//ランダムリセット
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//ランダムリセット
				resetStairs(stairs1);
			if (stairs2[2].bl_x + stairs2[2].set_x + 32 < 0 && reset_rng == 1)//ランダムリセット
				resetStairs(stairs2);
			if (stairs3[2].bl_x + stairs3[2].set_x + 32 < 0 && reset_rng == 6)//ランダムリセット
				resetStairs(stairs3);
			//********************************************************************
			if (CheckHitKey(KEY_INPUT_0))
			{
				se->doTitleMode();
			}
			if (pl->pos_x<-32)//プレイヤーが画面外に出たら終了
			{
				se->nowscene = OVER;
			}
			//プレイヤー描画
			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
				pl->Move(pl, stairs2);
			}
			else {
				pl->Move(pl, stairs1);
				pl->Move(pl, stairs3);
			}
			pl->Jump();
			pl->Draw();
		}

		//背景レイヤー
		bk->drawLayerAll(cnt);

		if (se->nowscene == OVER)
		{
			se->doOverMode(&cnt,sc,pl);
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