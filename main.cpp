#include"DxLib.h"
#include"define.h"
#include"back.h"
#include"player.h"
#include "object.h"
#include"scene.h"
#include"effect.h"
#include"UI.h"
#include "controller.h"
#include <stdlib.h>
#include <time.h>

//TODO
//リセット安定化
//ブロック同時生成
//背景
//コインアセット
//落とし穴
//ジャンプ挙動
//その他変な挙動修正
//音楽 BGM/ぽちゃんみたいな音？

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
	spark sparks2[MAX_SPARK];
	Score *sc = new Score();
	coin *co = new coin();
	player *pl_dummy = new player();
	pl_dummy->pos_x = 0;

	pl->setPlayerPos();
	sc->getScore();
	setParticleSe(sparks);
	int color = GetColor(255, 255, 255);
	int j = 0;
	int cnt = -1, dummycnt = 500000, temp_cnt = 0;
	int reset_rng = 0;
	int pad;//ジョイパッドの入力状態格納用変数
	//階段用******************************************
	block stairs[6];//bl_xが同じでbl_y	だけが変更されるインスタンスが最初にできるので初期値は大きくしておく(-だとループしてくる)
	block stairs1[6];
	block stairs2[6];
	block stairs3[6];

	block walls[3];
	block walls0[3];
	block walls2[3];
	block walls3[3];
	//***********************************************
	while (ProcessMessage() != -1)
	{
		srand((unsigned int)(time(NULL)));
		ClearDrawScreen();
		//タイトル画面
		if (se->nowscene == TITLE)
		{
			bk->drawTitle();
			se->doTitleMode(pad);
			//パーティクル
			if (pl->jflg == true || pl->pos_x < -32) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32用の演出追加するかも
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//妥協案
			pl->banJump(pad);
			pl->Draw();
		}

		if (se->nowscene == TUTORIAL)
		{
			se->tutorial_cnt++;
			bk->drawPlay();
			pl->Move(pl, walls);
			pl->Move(pl, walls0);
			if (pl->pos_x < -31)//復活ディレイ
			{
				if (se->tutorial_cnt_temp == 0)
				{
					se->tutorial_cnt_temp = se->tutorial_cnt;
				}
				if ((se->tutorial_cnt) - (se->tutorial_cnt_temp) > 1) //ジャンプパーティクルと死亡パーティクルは別に分けた
				{
					for (j = 0; j < MAX_SPARK; j++)
					{
						sparks2[j].particle_flg = true;
						if (sparks2[5].particle_flg == true)
						{
							for (j = 0; j < MAX_SPARK; j++)
							{
								sparks2[j].sparkAll(0, WINDOW_X / 2);
								sparks2[j].drawSpark();
							}
						}
					}
				}
				if ((se->tutorial_cnt) - (se->tutorial_cnt_temp) > 100)
				{
					for (j = 0; j < MAX_SPARK; j++)sparks2[j].Valid = 0;
					pl->pos_x = POS_X_INIT;
					se->tutorial_cnt_temp = 0;
				}
			}
			if (pl->jflg == true) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32用の演出追加するかも
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//妥協案
			pl->Jump(pad);
			pl->Draw();

			setWallsAll(100, se->tutorial_cnt, BLACK_WORLD, walls);
			setWallsAll(200, se->tutorial_cnt, WHITE_WORLD, walls0);
		}

		if (se->nowscene == PLAY)
		{
			cnt++;
			//背景描画
			bk->drawPlay();

			//パーティクル
			if (pl->jflg == true) { for (j = 0; j < MAX_SPARK; j++)sparks[j].particle_flg = true; }//pl->pos_x<-32用の演出追加するかも
			if (sparks[5].particle_flg == true) { for (j = 0; j < MAX_SPARK; j++) { sparks[j].jumpSpark(pl); } }//妥協案

			if (pl->pos_x < -32)
			{
				if(pl->pos_x==-35)PlaySoundMem(sparks[0].particle_se, DX_PLAYTYPE_BACK);//-5づつ動いてるから-35
				if (temp_cnt == 0)temp_cnt = cnt;
				if (cnt - temp_cnt > 1)
				{
					for (j = 0; j < MAX_SPARK; j++)
					{
						sparks2[j].particle_flg = true;
						if (sparks2[5].particle_flg == true)
						{
							for (j = 0; j < MAX_SPARK; j++)
							{
								sparks2[j].sparkAll(0, WINDOW_X / 2);
								sparks2[j].drawSpark();
							}
						}
					}
				}
				//ゲームオーバー
				if (cnt - temp_cnt > 100)
				{
					se->endGame(pl, pad);
					temp_cnt = 0;
					for (j = 0; j < MAX_SPARK; j++)sparks2[j].Valid = 0;
				}
			}
			//階段設定
			//********************************************************************
			reset_rng = rand() % 7;

			setStairsAll(100, cnt, BLACK_WORLD, stairs);//オブジェクトセット
			setStairsAll(700, cnt, WHITE_WORLD, stairs1);
			setStairsAll(300, cnt, BLACK_WORLD, stairs2);
			setStairsAll(1300, cnt, WHITE_WORLD, stairs3);

			setWallsAll(150, cnt, BLACK_WORLD, walls2);
			setWallsAll(220, cnt, WHITE_WORLD, walls3);


			//最初の生成とリセットが被るとダメ
			if (stairs[2].bl_x + stairs[2].set_x + 32 < 0 && reset_rng == 5)//ランダムリセット
				resetStairs(stairs);
			if (stairs1[2].bl_x + stairs1[2].set_x + 32 < 0 && reset_rng == 3)//ランダムリセット
				resetStairs(stairs1);
			if (stairs2[2].bl_x + stairs2[2].set_x + 32 < 0 && reset_rng == 1)//ランダムリセット
				resetStairs(stairs2);
			if (stairs3[2].bl_x + stairs3[2].set_x + 32 < 0 && reset_rng == 6)//ランダムリセット
				resetStairs(stairs3);

			resetWalls(walls2);
			resetWalls(walls3);

			//********************************************************************
			//コイン
			co->coinAll(*pl, sc);
			if (reset_rng == 2)co->coinReset();
			co->Debug();

			//プレイヤー描画
			if (pl->worldchange == BLACK_WORLD) {
				pl->Move(pl, stairs);
				pl->Move(pl, stairs2);
				pl->Move(pl, walls2);
			}
			else {
				pl->Move(pl, stairs1);
				pl->Move(pl, stairs3);
				pl->Move(pl, walls3);
			}
			pl->Jump(pad);
			pl->Draw();

			//背景レイヤー
			bk->drawLayerAll(cnt);

			/*SetFontSize(20);
			DrawFormatString(30, 30, color, "cnt:%d,reset_rng:%d", cnt, reset_rng);*/
			sc->viewScore(cnt);
		}

		if (se->nowscene == OVER)
		{
			sc->overCnt++;
			se->doOverMode(&cnt, sc, pl, pad);
			sc->viewEndScore();
			//背景レイヤー
			bk->drawLayerAll(dummycnt);//雪降らせるカウント
		}
		pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		debugController(pad);
		ScreenFlip();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1 || (pad&(1 << 11)))
		{
			delete bk;
			delete pl;
			delete sc;
			delete se;
			delete co;
			delete pl_dummy;
			delete[] sparks;
			delete[] sparks2;

			break;
		}
	}
	DxLib_End();
	return 0;
}